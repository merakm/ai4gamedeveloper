//
//  Chapter4FieldDlg.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/04.
//
//

#include "Chapter4FieldDlg.hpp"

#define BASE_LAYER LayerBase

Chapter4FieldDlg::Chapter4FieldDlg()
{
}


void Chapter4FieldDlg::addinit() {
	
	LayerColor::initWithColor(Color4B(0,0,0,255));
	
	m_UnitManager.init(Vec3(100.f, 700.f, 0.0), 90);
	m_UnitManager.SetMode(CGroupManager::eMODE_WIDE);
	m_UnitManager.SetForDrow(this);

	Vec2 pos( 100, 100 );
	Label* pbtnlabel = Label::createWithTTF("info", "fonts/arial.ttf", 20);
	auto pBtn = MenuItemLabel::create(pbtnlabel, CC_CALLBACK_1(Chapter4FieldDlg::selectchapterbtn, this));
		
	Menu* pMenu = Menu::create(pBtn, NULL);
	pMenu->setPosition(pos);
		this->addChild(pMenu, 1);
	
	m_target = Label::createWithSystemFont("", "arial.ttf", 24);
	m_target->retain();
	m_target->setString("");
	this->addChild(m_target);

}

void Chapter4FieldDlg::update(float delta) {
	
	m_UnitManager.update(delta);
	BASE_LAYER::update(delta);
	
}

bool Chapter4FieldDlg::onMouseClick(Event *pEvent)
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
//	m_Character[eCHARA_TARGET].SetTarget(target);
	
	m_UnitManager.SetTarget(target);
	
	m_target->setPosition(touchPos);
	m_target->setString("+");
	
#endif
	
	
	return true;
}

// 画面遷移ボタン.
void Chapter4FieldDlg::selectchapterbtn(cocos2d::Ref* pSender) {
	
	bool showInfo = m_UnitManager.bShowInfo;
	m_UnitManager.ShowInfo( !showInfo );
	
}