//
//  Chapter2Field.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/15.
//
//
#include <math.h>
#include "Craft.hpp"
USING_NS_CC;

CCraft::CCraft()
: m_sprite( NULL )
, m_bHaveTarget(false)
, m_mode(eMODE_INVALID)
, m_targetCraft( NULL )
{
}

CCraft::~CCraft() {
	
	if ( m_sprite ) {
		m_sprite->release();
	}
	
}

void CCraft::Init( Vec3 pos, sCraftParam param ) {
	
	m_sprite = Sprite::create("spacecraft.png");
	m_sprite->retain();

	Stop();

	m_sprite->setPosition(Vec2(pos.x, pos.y));
	
	Size spriteSize = m_sprite->getContentSize();
	m_sprite->setScale(m_param.m_size.width/spriteSize.width,
					   m_param.m_size.height/spriteSize.height);

	m_pos = pos;
	m_orientation = 0;
	m_param = param;
	
	m_mainThrusterForce = Vec3::UNIT_Y * m_param.m_mainThrustMax;	// とりあえず最大出力.

}

void CCraft::Stop() {
	
	m_velocity = Vec3::ZERO;

}

void CCraft::SetTarget( CCraft *pTarget ) {
	
	m_targetCraft = pTarget;
	if ( pTarget ) {
		SetTarget(pTarget->GetPos());
	}
	else {
		m_bHaveTarget = false;
	}
	
}

void CCraft::SetTarget(Vec3 targetPos) {

	m_targetPos = targetPos;
	m_bHaveTarget = true;
}

void CCraft::Update(float dt) {
	
	Vec3 a, dv, ds;		// 加速度,速度変化,位置変化.
	float aa, dav, da;	// 角加速度, 角速度変化, 角度変化.
	
	
	// 方向の調整
	UpdateForceToTarget();
	
	// キャラクターにかかる力とモーメントの計算.
	UpdateForce();
	
	// 加速度.
	a = m_force/m_param.m_mass;
	// 速度.
	dv = a * dt;
	m_velocity += dv;
	// 位置.
	ds = m_velocity * dt;
	m_pos += ds;
	
	// 角加速度.
	aa = m_moment.z / m_param.m_inertia;
	
	// 角速度.
	dav = aa * dt;
	m_angVelocity.z += dav;
	
	// 角度.
	da = rad_to_deg( m_angVelocity.z * dt );
	m_orientation += da;
	
	if (m_sprite) {
		m_sprite->setPosition(Vec2( m_pos.x, m_pos.y));
		m_sprite->setRotation(m_orientation + 90);
		
		m_velocityBody = Rotate2D(-m_orientation, m_velocity);
	}
}

void CCraft::UpdateForceToTarget() {
	
	if (!m_bHaveTarget) {
		return;
	}
	
	bool bLeft = false, bRight = false;
	Vec3 VecToTargetLocal;
	
	switch (m_mode) {
	case eMODE_CHASING:
		{
			Vec3 VecToTarget = ( m_targetPos - m_pos );
			VecToTargetLocal = Rotate2D(-m_orientation, VecToTarget);
			
		}
		break;
	case eMODE_INTERCEPT:
		{
			if (!m_targetCraft) {
				return;
			}
			Vec3 dV = ( m_targetCraft->m_velocity - m_velocity );
			Vec3 dS = ( m_targetPos - m_pos );
			float tc = dS.length() / dV.length();
			Vec3 dT = m_targetPos + m_targetCraft->m_velocity * tc;
			VecToTargetLocal = Rotate2D(-m_orientation, dT - m_pos);
		}
		break;
	default:
		break;
	}

	if (VecToTargetLocal.x < 0.0f) {
		bRight = true;
	}
	else if ( VecToTargetLocal.x > 0.0f) {
		bLeft = true;
	}

	
	SetThruster(bLeft, bRight);
	
}

void CCraft::UpdateForce() {
	
	Vec3 ForceSum		= Vec3::ZERO;
	Vec3 MomentSum		= Vec3::ZERO;
	Vec3 LocalVelocity	= Vec3::ZERO;
	Vec3 dragVelocity	= Vec3::ZERO;
	
	// 初期化.
	m_force	 = Vec3::ZERO;
	m_moment = Vec3::ZERO;

	
	// メインスラスターからの力.
	Vec3 MainThruster = m_mainThrusterForce;
	// Vec3::UNIT_Y * m_param.m_mainThrustMax;	// とりあえず最大出力.
	ForceSum = MainThruster;
	
	// 速度の更新.
	// 回転要素.
	{
		Vec3 tmp;
		Vec3::cross(m_angVelocity, m_param.m_centerPos, &tmp);
		LocalVelocity = m_velocityBody + tmp;
	}
	

	float localSpeed = LocalVelocity.length();
	// 抗力計算.
	if (localSpeed > 0.0f) {
		LocalVelocity.normalize();
		dragVelocity = -LocalVelocity;
		
		float tmp = m_param.m_mainThrustMax * localSpeed*localSpeed/m_param.m_speedMax/m_param.m_speedMax;
		Vec3 resultForce = dragVelocity * tmp;
		resultForce.x *= 5;
		
		ForceSum += resultForce;
		
		Vec3 momentTmp;
		Vec3::cross(m_param.m_centerPos, resultForce, &momentTmp);
		MomentSum += momentTmp;
	}
	
	// 左サイドスラスターからの力.
	ForceSum += m_sideThrusterForceL;
	Vec3 momentSide;
	Vec3::cross(m_param.m_sideThrustPosL, m_sideThrusterForceL, &momentSide);
	MomentSum += momentSide;
	
	// 右サイドスラスターからの力.
	ForceSum += m_sideThrusterForceR;
	Vec3::cross(m_param.m_sideThrustPosR, m_sideThrusterForceR, &momentSide);
	MomentSum += momentSide;
	
	m_force = Rotate2D(m_orientation, ForceSum);
	m_moment = MomentSum;
	
}

Vec3 CCraft::Rotate2D( float angle, Vec3 u)
{
	float	x,y;
	
	x = u.x * cos(deg_to_rad(angle)) + u.y * sin(deg_to_rad(angle));
	y = -u.x * sin(deg_to_rad(angle)) + u.y * cos(deg_to_rad(angle));
	
	return Vec3( x, y, 0);
}

void CCraft::SetThruster( bool left, bool right ) {
	
	m_sideThrusterForceL = Vec3::ZERO;
	m_sideThrusterForceR = Vec3::ZERO;
	m_angVelocity = Vec3::ZERO;
	
	if (left)	m_sideThrusterForceL.x = -m_param.m_sideThrustMax;
	if (right)	m_sideThrusterForceR.x = m_param.m_sideThrustMax;
}

void CCraft::SetThruster( float forceleft, float forceright ) {
	
	m_angVelocity = Vec3::ZERO;
	
	m_sideThrusterForceL.x = -m_param.m_sideThrustMax*forceleft;
	m_sideThrusterForceR.x = m_param.m_sideThrustMax*forceright;
	
	
}
void CCraft::SetMainThruster( float force ){
	
	m_mainThrusterForce.y = force;
}
