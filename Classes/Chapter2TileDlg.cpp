//
//  Chapter2TileDlg.cpp
//  test
//
//  Created by Kohei Kumazaki on 2017/01/09.
//
//

#include "Chapter2TileDlg.h"
USING_NS_CC;

#define BASE_LAYER LayerBase

Chapter2TileDlg::Chapter2TileDlg()
: m_pfield(NULL) {
	
}

Chapter2TileDlg::~Chapter2TileDlg() {
	if (m_pfield) {
		free(m_pfield);
		m_pfield = NULL;
	}
}

void Chapter2TileDlg::addinit()
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
	
	BASE_LAYER::addinit();
}

void Chapter2TileDlg::update(float delta)
{
	if ( m_pfield ) {
		m_pfield->Update();
	}
	BASE_LAYER::update(delta);
}

bool Chapter2TileDlg::IsInField( Vec2 pos ){
	
	Rect rect = m_pfield->GetFieldRect();
	return rect.containsPoint(pos);
}

// クリック開始イベント
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
bool Chapter2TileDlg::onMouseClick(Event *pEvent)
{
	auto mouse = (EventMouse*)pEvent;
	Vec2 touchPos = mouse->getStartLocationInView();
	bool bRight = ( mouse->getMouseButton() == MOUSE_BUTTON_RIGHT );
	if (IsInField(touchPos)) {
		// タイルクリック.
		m_pfield->TileClicked(touchPos, bRight);
	}
	return true;
}
#else
bool Chapter2TileDlg::onClickBegin(Touch *pTouch, Event *pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	if (IsInField(touchPos)) {
		// タイルクリック.
		m_pfield->TileClicked(touchPos);
	}
	return true;
}
#endif

