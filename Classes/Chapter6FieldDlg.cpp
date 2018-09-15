//
//  Chapter6Field.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/10.
//
//

#include "Chapter6FieldDlg.hpp"


#define BASE_LAYER LayerBase

Chapter6TileDlg::Chapter6TileDlg()
: m_pfield(nullptr)
, pModeChangeButton(nullptr)
, m_mode(eMODE_PATHFIND)
{
	
}

Chapter6TileDlg::~Chapter6TileDlg() {
	if (m_pfield) {
		free(m_pfield);
		m_pfield = NULL;
	}
}

void Chapter6TileDlg::addinit()
{
	// 背景色を白に.
	LayerColor::initWithColor(Color4B(0,0,0,255));
	
	// フィールド初期化.
	// CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create();
	// this->addChild(batchNode);
	m_pfield = new CTileField();
	if (m_pfield) {
		m_pfield->init();
		for (int width = 0; width < CTileField::FIELD_NUM_WIDTH; ++width) {
			for (int height = 0; height < CTileField::FIELD_NUM_HEIGHT; ++height) {
				Sprite* ps = m_pfield->pGetTileSprite(width, height);
				if (ps) {
					this->addChild(ps);
				}
			}
		}
	}
#if 1
	pModeChangeButton = Label::createWithTTF("Map Edit Mode", "fonts/arial.ttf", 20);
	auto pBtn = MenuItemLabel::create(pModeChangeButton, CC_CALLBACK_1(Chapter6TileDlg::pushModeChangeBtn, this));
	Vec2 pos(100.0, 100.0);
	Menu* pMenu = Menu::create(pBtn, NULL);
	pMenu->setPosition(pos);
	this->addChild(pMenu, 1);
#endif
	
	BASE_LAYER::addinit();
}

void Chapter6TileDlg::update(float delta)
{
	if ( m_pfield ) {
		m_pfield->Update();
	}
	BASE_LAYER::update(delta);
}

bool Chapter6TileDlg::IsInField( Vec2 pos ){
	
	Rect rect = m_pfield->GetFieldRect();
	return rect.containsPoint(pos);
}

void Chapter6TileDlg::pushModeChangeBtn( cocos2d::Ref* pSender ) {
	
	switch (m_mode) {
	case eMODE_PATHFIND:
		{
			m_mode = eMODE_EDIT;
			pModeChangeButton->setString("Pathfind Mode");
		}
			break;
	case eMODE_EDIT:
		{
			m_mode = eMODE_PATHFIND;
			pModeChangeButton->setString("Map Edit Mode");
		}
			break;
	default:
			break;
	}
	
}

// クリック開始イベント
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
bool Chapter6TileDlg::onMouseClick(Event *pEvent)
{
	auto mouse = (EventMouse*)pEvent;
	Vec2 touchPos = mouse->getStartLocationInView();
	bool bRight = ( mouse->getMouseButton() == MOUSE_BUTTON_RIGHT );
	if (IsInField(touchPos)) {
		// タイルクリック.
		switch (m_mode) {
		case eMODE_EDIT:
			{
				m_pfield->SetWall(touchPos, bRight);
			}
		break;
		case eMODE_PATHFIND:
			{
				m_pfield->TileClicked(touchPos, bRight);
			}
		break;
		default:
		break;
		}
	}
	return true;
}
#else
bool Chapter6TileDlg::onClickBegin(Touch *pTouch, Event *pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	if (IsInField(touchPos)) {
		// タイルクリック.
		m_pfield->TileClicked(touchPos);
	}
	return true;
}
#endif

