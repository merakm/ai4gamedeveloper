//
//  GroupManager.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/04.
//
//

#include "GroupManager.hpp"

float radiusFactor[CGroupManager::eMODE_NUM] = {
	200.0,	// eMODE_ALL
	200.0,	// eMODE_WIDE
	30.0,	// eMODE_LIMITED
	50.0,	// eMODE_NARROW
};

void drawSector(cocos2d::DrawNode* node, cocos2d::Vec2 origin, float radius, float angle_degree,
				cocos2d::Color4F fillColor, float borderWidth, cocos2d::Color4F bordercolor,
				unsigned int num_of_points = 100)
{
	if (!node)
	{
		return;
	}
	
	const cocos2d::Vec2 start = origin + cocos2d::Vec2{radius, 0};
	const auto angle_step = 2 * M_PI * angle_degree / 360.f / num_of_points;
	std::vector<cocos2d::Point> circle;
	
	circle.emplace_back(origin);
	for (int i = 0; i <= num_of_points; i++)
	{
		auto rads = angle_step * i;
		auto x = origin.x + radius * cosf(rads - deg_to_rad(angle_degree/2.0));
		auto y = origin.y + radius * sinf(rads - deg_to_rad(angle_degree/2.0));
		circle.emplace_back(x, y);
	}
	
	node->drawPolygon(circle.data(), circle.size(), fillColor, borderWidth, bordercolor);
}

CGroupCraft::CGroupCraft()
: CCraft::CCraft()
, parent(NULL)
, SepArea(NULL)
, VisibleArea(NULL)
, bShowInfo(false)
{
	for (int i = 0; i < eVEC_NUM; ++i) {
		pDrowNode[i] = NULL;
	}
}

void CGroupCraft::Init(cocos2d::Vec3 pos, CCraft::sCraftParam param) {
	
	CCraft::Init(pos, param);
	
	SepForce = Vec3::ZERO;
	CohForce = Vec3::ZERO;
	AlgForce = Vec3::ZERO;
	
	AvePos = Vec3::ZERO;
	AveVel = Vec3::ZERO;
	
	for (int i = 0; i < eVEC_NUM; ++i) {
		pDrowNode[i] = DrawNode::create();
	}
	SepArea = DrawNode::create();
	VisibleArea = DrawNode::create();
	// m_sprite->setSpriteFrame("model.png");
	
}

void CGroupCraft::Update(float dt) {
	
	CCraft::Update(dt);
	
	// かかっている力の描画
	if (bShowInfo) {
		DrowInfo();
	}
	
}

void CGroupCraft::ClearInfo() {
	SepArea->clear();
	VisibleArea->clear();
	for (int i = 0; i < eVEC_NUM; ++i) {
		pDrowNode[i]->clear();
	}
}

void CGroupCraft::DrowInfo() {
	
	ClearInfo();
	drawSector(SepArea, Vec2(m_pos.x, m_pos.y),
			   radiusFactor[CGroupManager::eMODE_WIDE],
			   270, Color4F(0.0, 0.0,0.0,0.0), 0.5, Color4F::WHITE);
	drawSector(VisibleArea, Vec2(m_pos.x, m_pos.y),
			   CGroupManager::_SEPARATION_FACTOR * m_param.m_size.height,
			   270, Color4F(0.0, 0.0,0.0,0.0), 0.5, Color4F::WHITE);

	
	Color4F color[ eVEC_NUM ] = {
		Color4F::YELLOW,	// eVEC_SEP_FORCE
		Color4F::RED,		// eVEC_COH_FORCE
		Color4F::BLUE,		// eVEC_ALG_FORCE
		Color4F::ORANGE,		// eVEC_AVEVEL
		Color4F::WHITE,		// eVEC_VELOCITY
	};
	
	for (int i = 0; i < eVEC_NUM; ++i) {
		Vec2 vec_from = Vec2::ZERO;
		Vec2 vec_to = Vec2::ZERO;
		
		switch (i) {
			case eVEC_AVEVEL:
			{
				vec_from = Vec2( AvePos.x, AvePos.y );
				vec_to = vec_from + Vec2( AveVel.x, AveVel.y );
			}
				break;
			case eVEC_VELOCITY:
			{
				vec_from = Vec2( m_pos.x, m_pos.y );
				vec_to = vec_from + Vec2( m_velocity.x, m_velocity.y );
			}
				break;
			case eVEC_SEP_FORCE:
			{
				Vec3 posThruster = Rotate2D(m_orientation,
											Vec3(0.0, m_param.m_sideThrustPosL.y, 0.0));
				Vec3 VecForce = Rotate2D(m_orientation, SepForce);
				vec_from = Vec2( m_pos.x + posThruster.x, m_pos.y + posThruster.y);
				vec_to = vec_from + 30.0*Vec2(VecForce.x, VecForce.y);
			}
				break;
			case eVEC_COH_FORCE:
			{
				Vec3 posThruster = Rotate2D(m_orientation,
										Vec3(0.0, m_param.m_sideThrustPosL.y + 1.0, 0.0));
				Vec3 VecForce = Rotate2D(m_orientation, CohForce);

				vec_from = Vec2( m_pos.x + posThruster.x, m_pos.y + posThruster.y);
				vec_to = vec_from + 30.0*Vec2(VecForce.x, VecForce.y);
			}
				break;
			case eVEC_ALG_FORCE:
			{
				Vec3 posThruster = Rotate2D(m_orientation,
										Vec3(0.0, m_param.m_sideThrustPosL.y + 2.0, 0.0));
				Vec3 VecForce = Rotate2D(m_orientation, AlgForce);
				vec_from = Vec2( m_pos.x + posThruster.x, m_pos.y + posThruster.y );
				vec_to = vec_from + 30.0*Vec2(VecForce.x, VecForce.y);
			}
				break;
				
			default:
				break;
		}


		pDrowNode[i]->drawSegment( vec_from, vec_to, 1, color[i]);
	}

}

void CGroupCraft::ShowInfo( bool flag ) {

	ClearInfo();
	bShowInfo = flag;
	if (bShowInfo) {
		m_sprite->setSpriteFrame(Sprite::create("model.png")->getSpriteFrame());
	}
	else {
		m_sprite->setSpriteFrame(Sprite::create("spacecraft.png")->getSpriteFrame());
	}
}



CGroupManager::CGroupManager()
: m_mode(eMODE_INVALID)
, bShowInfo(false)
, m_bsettarget(false)
{
	
}

CGroupManager::~CGroupManager() {
	
}

void CGroupManager::init(cocos2d::Vec3 pos, float orientation){
	
	m_Unit[UNIT_LEADER].SetMode(CCraft::eMODE_CHASING);
	float width  = m_Unit[0].m_param.m_size.width + 5;
	float length = m_Unit[0].m_param.m_size.height + 5;
	
	for (int i = 0; i < UNIT_NUM; ++i) {
		srand((unsigned int)time(NULL) + i);
		int randNum = rand()%20 - 10;
		Vec3 unitpos;
		if ( i == UNIT_LEADER) {
			unitpos = pos;
		}
		else {
			int row = i / UNIT_ROW_NUM, colmun = i % UNIT_ROW_NUM;
			unitpos.x = pos.x -  row * width + randNum;
			unitpos.y = pos.y - colmun * length + randNum;
		}

		CCraft::sCraftParam param;
		param.m_speedMax *= 0.3;
		m_Unit[i].Init(unitpos, param);
		m_Unit[i].m_orientation = orientation;
		m_Unit[i].SetMode(CCraft::eMODE_CHASING);
	}
	
}

void CGroupManager::update(float delta) {
	
	DoAllUnitAI();
	// 全部力を与えてから更新
	UpdateAllUnit(delta);
}

void CGroupManager::DoUnitAI(int index) {
	
	if ( m_mode == eMODE_INVALID) {
		return;
	}
	
	int neighberNum = 0;
	int id = 0;
	Vec3 aveVel = Vec3::ZERO;
	Vec3 avePos = Vec3::ZERO;
	Vec3 Force = Vec3::ZERO;
	
	Vec3 SepForce = Vec3::ZERO;
	Vec3 CohForce = Vec3::ZERO;
	Vec3 AlgForce = Vec3::ZERO;
	
	int m = 0;
	bool InView;
	bool bLeader = true;
	float RadiusFactor = radiusFactor[m_mode];
	Vec3 dist, u, v, w;
	
	CGroupCraft* currentUnit = &m_Unit[index];
	
	for (id = 0; id < UNIT_NUM; ++id) {
		if (id == index) continue;
		
		InView = false;
		dist = m_Unit[id].m_pos - currentUnit->m_pos;
		w = currentUnit->Rotate2D( -currentUnit->m_orientation, dist);
		
		
		bool bIsInView = IsInView(w);
		float fLength = currentUnit->m_param.m_size.height;

		// リーダーかどうかの判定.
		if((w.y > 0) && ( dist.length() <= (fLength * radiusFactor[eMODE_LIMITED]) ))
		{
			bLeader = false;
		}
		
		
		if ( bIsInView &&
			dist.length() <= fLength * RadiusFactor ) {
			avePos += m_Unit[id].m_pos;
			aveVel += m_Unit[id].m_velocity;
			neighberNum++;
		}
		
		// 分離.
		if ( bIsInView && dist.length() <= fLength * _SEPARATION_FACTOR ) {
			if (w.x < 0) m = -1;
			if (w.x > 0) m = 1;
			
			SepForce.x += m * fLength * _SEPARATION_FACTOR / dist.length();
		}
		
	}

	// 結合.
	m = 0;
	if (neighberNum > 0) {
		avePos = avePos / neighberNum;
		
		v = currentUnit->m_velocity;
		v.normalize();
		
		u = avePos - currentUnit->m_pos;
		u.normalize();
		w = currentUnit->Rotate2D(-currentUnit->m_orientation, u);
		
		if ( w.x < 0 ) m = 1;
		if ( w.x > 0 ) m = -1;
		float dot = fabs(v.dot(u));
		if ( dot < 1) {
			CohForce.x += m * acos(dot)/M_PI;
		}
	}
	
	// 整列.
	m = 0;
	if (neighberNum > 0) {
		aveVel = aveVel / neighberNum;
		u = aveVel;
		u.normalize();
		v = currentUnit->m_velocity;
		v.normalize();
		w = currentUnit->Rotate2D(-currentUnit->m_orientation, u);
		if ( w.x < 0 ) m = 1;
		if ( w.x > 0 ) m = -1;
		float dot = fabs(v.dot(u));
		if ( dot < 1) {
			AlgForce.x += m * acos(dot)/M_PI;
		}
	}

	Force = AlgForce + SepForce + CohForce;
	currentUnit->SepForce = SepForce;
	currentUnit->CohForce = CohForce;
	currentUnit->AlgForce = AlgForce;
	currentUnit->AveVel = aveVel;
	currentUnit->AvePos = avePos;
	

	if ( m_bsettarget && bLeader ) {
		currentUnit->SetTarget(m_targetPos);
		currentUnit->pGetSprite()->setColor(Color3B::YELLOW);
	}
	else {
		currentUnit->ResetTarget();
		//currentUnit->SetMainThruster(Force.y);
		if ( Force.x > 0 ) currentUnit->SetThruster( 0.0f, fabs(Force.x) );
		if ( Force.x < 0 ) currentUnit->SetThruster( fabs(Force.x), 0.0f );
		currentUnit->pGetSprite()->setColor(Color3B::WHITE);
	}
}

void CGroupManager::DoAllUnitAI() {
	
	for (int i = 0; i < UNIT_NUM; ++i) {
		if (i == UNIT_LEADER) continue;
		DoUnitAI(i);
	}
}

void CGroupManager::UpdateAllUnit(float delta) {
	
	for (int i = 0; i < UNIT_NUM; ++i) {
		m_Unit[i].Update(delta);
	}
	
}


void CGroupManager::SetTarget(Vec3 pos) {
	
	m_targetPos = pos;
	m_bsettarget = true;
}

bool CGroupManager::IsInView( Vec3 pos ) {
	
	bool bRet = false;
	switch (m_mode) {
		case eMODE_ALL:
		{
			bRet = true;
		}
			break;
		case eMODE_WIDE:
		{
			bRet = ( (pos.y > 0 ) ||
				   ( (pos.y < 0 ) &&
				   ( fabs(pos.x) > fabs(pos.y) * _FRONT_VIEW_ANGLE_FACTOR )) );
		}
			break;
		case eMODE_LIMITED:
		{
			bRet = (pos.y > 0);
		}
			break;
		case eMODE_NARROW:
		{
			bRet = ( (pos.y > 0 ) ||
				   ( (pos.y < 0 ) &&
				   ( fabs(pos.x) < fabs(pos.y) * _BACK_VIEW_ANGLE_FACTOR )) );
		}
			break;
		default:
			break;
	}
	return bRet;
}


void CGroupManager::SetForDrow( cocos2d::LayerColor* parent ) {
	
	for (int i = 0; i < UNIT_NUM; ++i) {
		parent->addChild(m_Unit[i].pGetSprite());
		m_Unit[i].parent = parent;
		for (int j = 0; j < CGroupCraft::eVEC_NUM; ++j ) {
			parent->addChild(m_Unit[i].pDrowNode[j]);
		}
		parent->addChild(m_Unit[i].SepArea);
		parent->addChild(m_Unit[i].VisibleArea);

	}
}

void CGroupManager::ShowInfo( bool flag ) {
	
	bShowInfo = flag;
	for (int i = 0; i < UNIT_NUM; ++i) {
		m_Unit[i].ShowInfo( flag );
	}
}