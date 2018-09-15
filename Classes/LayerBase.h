//
//  SceneBase.h
//  test
//
//  Created by Kohei Kumazaki on 2017/01/09.
//
//

#ifndef SceneBase_hpp
#define SceneBase_hpp


// createScene定義マクロ.
#define CREATESCENE_FUNC(__TYPE__) \
static cocos2d::Scene* createScene() \
{ \
auto scene = cocos2d::Scene::create(); \
auto layer = __TYPE__::create(); \
\
scene->addChild(layer, 0, "mainLayer"); \
\
return scene; \
}

// createSceneとcreateを両方定義するマクロ.
#define DECLEAR_H( __TYPE__ ) \
CREATESCENE_FUNC(__TYPE__) \
CREATE_FUNC(__TYPE__)


#include "cocos2d.h"
USING_NS_CC;

class LayerBase : public cocos2d::LayerColor
{

public:
	LayerBase();
	~LayerBase();
	
	bool init();
	virtual void addinit();
	virtual void update(float delta);
	
	// クリック時の挙動.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	virtual bool onMouseClick(Event* pEvent);	// クリック.
	virtual void onMouseMoved(Event *pEvent);	// マウス移動.
	virtual void onMouseScroll(Event* pEvent);	// スクロール.
	virtual void onMouseUp(Event* pEvent);		// クリック終了.
#else
	virtual bool onClickBegan(Touch* pTouch, Event* pEvent);	// クリック開始.
	virtual void onClickMoved(Touch *pTouch, Event *pEvent);	// クリック中
	virtual void onClickCancelled(Touch *pTouch, Event *pEvent);// クリックキャンセル
	virtual void onClickEnded(Touch* pTouch, Event* pEvent);	// クリック終了
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	
	// a selector callback
	virtual void menuCloseCallback(cocos2d::Ref* pSender);
	
private:
	cocos2d::MenuItemImage* pcloseBtn;	// 閉じるボタン.
	
};

#endif /* SceneBase_hpp */
