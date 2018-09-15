//
//  SceneBase.cpp
//  test
//
//  Created by Kohei Kumazaki on 2017/01/09.
//
//
USING_NS_CC;
#include "LayerBase.h"


LayerBase::LayerBase() : pcloseBtn(NULL)
{
}

LayerBase::~LayerBase()
{
}

bool LayerBase::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	
	// スケジューラーへ登録.
	this->scheduleUpdate();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	
	// add a "close" icon to exit the progress. it's an autorelease object
	pcloseBtn = MenuItemImage::create("CloseNormal.png",
									  "CloseSelected.png",
									  CC_CALLBACK_1(LayerBase::menuCloseCallback, this));
	
	pcloseBtn->setPosition(Vec2(origin.x + visibleSize.width - pcloseBtn->getContentSize().width/2 ,
								origin.y + pcloseBtn->getContentSize().height/2));
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(pcloseBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	// クリック挙動登録.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	// http://korcs.info/blog/archives/1423
	auto listener = EventListenerMouse::create();
	listener->onMouseDown	= CC_CALLBACK_1(LayerBase::onMouseClick, this);
	listener->onMouseMove	= CC_CALLBACK_1(LayerBase::onMouseMoved, this);
	listener->onMouseUp		= CC_CALLBACK_1(LayerBase::onMouseUp, this);
	listener->onMouseScroll = CC_CALLBACK_1(LayerBase::onMouseScroll, this);
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
#else
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan		= CC_CALLBACK_2(LayerBase::onClickBegan, this);
	listener->onTouchMoved		= CC_CALLBACK_2(LayerBase::onClickMoved, this);
	listener->onTouchCancelled  = CC_CALLBACK_2(LayerBase::onClickCancelled, this);
	listener->onTouchEnded		= CC_CALLBACK_2(LayerBase::onClickEnded, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	
	addinit();
	
	return true;
}

void LayerBase::addinit()
{
}

void LayerBase::update(float delta)
{
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
bool LayerBase::onMouseClick(Event *pEvent)
{
	return true;
}

// マウススクロール.
void LayerBase::onMouseScroll(Event *pEvent)
{
}
// マウス移動イベント
void LayerBase::onMouseMoved(Event *pEvent)
{
}
// クリック終了イベント
void LayerBase::onMouseUp(Event *pEvent)
{
}
#else
// クリック開始イベント
bool LayerBase::onClickBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

// クリック移動イベント
void LayerBase::onClickMoved(Touch *pTouch, Event *pEvent)
{
}

// クリックキャンセルイベント
void LayerBase::onClickCancelled(Touch *pTouch, Event *pEvent)
{
}

// クリック終了イベント
void LayerBase::onClickEnded(Touch *pTouch, Event *pEvent)
{
}
#endif

void LayerBase::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
