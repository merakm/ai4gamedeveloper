//
//  Chapter2FieldDlg.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/15.
//
//

#include "Chapter2FieldDlg.h"

#define BASE_LAYER LayerBase

Chapter2FieldDlg::Chapter2FieldDlg(){
	m_target = NULL;
}

void Chapter2FieldDlg::addinit(){
	// 背景色を黒に.
	LayerColor::initWithColor(Color4B(0,0,0,255));
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Vec3 origin[eCHARA_NUM] = {
		Vec3( visibleSize.width/2,	0.0 /*visibleSize.height/2*/, 0.0),
		Vec3( 0.0, visibleSize.height/2, 0.0),
	};
	
	for (int i = 0; i < eCHARA_NUM; ++i) {
		CCraft::sCraftParam param;
		if (i == eCHARA_PREDETOR) {
			param.m_speedMax *=1.5;
		}
		m_Character[i].Init(origin[i], param);
		m_Character[i].SetMode(CCraft::eMODE_CHASING);
		this->addChild(m_Character[i].pGetSprite());
	}
	
	Vec2 basepos( 10.0f, 10.0f );
	for (int i = 0; i < eTEXT_NUM; ++i) {
		m_text[i] = Label::create();
		Vec2 pos = basepos + Vec2(0.0f, i * 20);
		m_text[i]->ignoreAnchorPointForPosition(true);
		m_text[i]->setPosition(pos);
		this->addChild(m_text[i]);
	}
	
	m_target = Label::createWithSystemFont("", "arial.ttf", 24);
	m_target->retain();
	m_target->setString("");
	this->addChild(m_target);
	
	BASE_LAYER::addinit();
}

void Chapter2FieldDlg::SetMode(eMODE mode) {
	
	m_mode = mode;
	// for (int i = eCHARA_START; i < eCHARA_NUM; ++i) {
		m_Character[eCHARA_PREDETOR].SetMode( (CCraft::eMODE)mode );
	// }
}


void Chapter2FieldDlg::update(float delta) {
	
	UpdateCharacter(delta);
	UpdateCharacterInfo();
	BASE_LAYER::update(delta);
}

void Chapter2FieldDlg::UpdateCharacter( float delta){

	if (m_mode == eMODE_CHASING) {
		Vec3 targetPos = m_Character[eCHARA_TARGET].GetPos();
		m_Character[eCHARA_PREDETOR].SetTarget(targetPos);
	}
	else if ( m_mode == eMODE_INTERCEPT ) {
		m_Character[eCHARA_PREDETOR].SetTarget(&m_Character[eCHARA_TARGET]);
	}
	
	for (int i = 0; i < eCHARA_NUM; ++i) {
		m_Character[i].Update(delta);
	}
	
}

void Chapter2FieldDlg::UpdateCharacterInfo() {
	
	char buff[100];
	snprintf(buff, sizeof(buff), "Force : %f, %f, %f",
			 m_Character[eCHARA_TARGET].m_force.x, m_Character[eCHARA_TARGET].m_force.y, m_Character[eCHARA_TARGET].m_force.z);
	std::string strForce = buff;
	m_text[eTEXT_FORCE]->setString(strForce);
	
	snprintf(buff, sizeof(buff), "Speed : %f, %f, %f",
			 m_Character[eCHARA_TARGET].m_velocity.x, m_Character[eCHARA_TARGET].m_velocity.y, m_Character[eCHARA_TARGET].m_velocity.z);
	std::string strVelocity = buff;
	m_text[eTEXT_SPEED]->setString(strVelocity);
	
	snprintf(buff, sizeof(buff), "AngSpeed : %f", m_Character[eCHARA_TARGET].m_angVelocity.z );
	std::string strAngVelocity = buff;
	m_text[eTEXT_ANG_SPEED]->setString(strAngVelocity);
	
	snprintf(buff, sizeof(buff), "Moment : %f", m_Character[eCHARA_TARGET].m_moment.z );
	std::string strMoment = buff;
	m_text[eTEXT_MOMENT]->setString(strMoment);
	

	
	// eTEXT_SIDE_THRUSTER,
	// eTEXT_MOMENT,
}

// クリック開始イベント
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
bool Chapter2FieldDlg::onMouseClick(Event *pEvent)
{
	auto mouse = (EventMouse*)pEvent;
	Vec2 touchPos = mouse->getStartLocationInView();

#if 0
	auto mouse = (EventMouse*)pEvent;
	Vec2 touchPos = mouse->getStartLocationInView();
	
	if (mouse->getMouseButton() == MOUSE_BUTTON_RIGHT) {
		m_Character[0].SetThruster(false, true);
	}
	else {
		m_Character[0].SetThruster(true, false);
	}
	//m_Character[0].SetTarget(Vec3(touchPos.x, touchPos.y, 0.0));
#else
	Vec3 target( touchPos.x, touchPos.y, 0.0f );
	m_Character[eCHARA_TARGET].SetTarget(target);
	
	m_target->setPosition(touchPos);
	m_target->setString("+");
#endif


	return true;
}

void Chapter2FieldDlg::onMouseUp(Event *pEvent){
	// m_Character[0].SetThruster(false, false);
}

#else
bool Chapter2FieldDlg::onClickBegin(Touch *pTouch, Event *pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	return true;
}
#endif