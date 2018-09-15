//
//  Chapter3FieldDlg.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/01.
//
//

#include "Chapter3FieldDlg.hpp"
#define BASE_LAYER LayerBase

Chapter3FieldDlg::Chapter3FieldDlg()
{
	
	
}

void Chapter3FieldDlg::addinit() {

	LayerColor::initWithColor(Color4B(0,0,0,255));

	// キャラクター.
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Vec3 origin = Vec3( 30.0, visibleSize.height/2, 0.0);
	CCraft::sCraftParam param;
	m_Character.Init(origin, param);
	m_Character.m_orientation = 90.f;
	addChild(m_Character.pGetSprite());
	
	Vec2 basepos( 10.0f, 10.0f );
	for (int i = 0; i < eTEXT_NUM; ++i) {
		m_text[i] = Label::create();
		Vec2 pos = basepos + Vec2(0.0f, i * 20);
		m_text[i]->ignoreAnchorPointForPosition(true);
		m_text[i]->setPosition(pos);
		m_text[i]->retain();
		this->addChild(m_text[i]);
	}
}

void Chapter3FieldDlg::update(float delta) {
	
	BASE_LAYER::update(delta);
	
	m_Character.Update(delta);
	
	char buff[256];
	int id = 9;
	for (int i = eTEXT_PATTERN_START; i < eTEST_PATTERN_END; ++i, --id) {
		float distance = m_Character.m_PatternParam[id].distanceLimit;
		float angle = m_Character.m_PatternParam[id].orientationLimit;
		bool loop = m_Character.m_PatternParam[id].loop;
		int nCurrent = m_Character.m_ChangeParam.CurrentID;
		snprintf(buff, sizeof(buff), " %s Pattern %d: d:%f, ang:%f, %s"
				 , ( nCurrent == id ) ? ">" : ""
				 , id
				 , distance
				 , angle
				 , loop ? "true" : "false"
				 );
		m_text[i]->setString(buff);
	}
}