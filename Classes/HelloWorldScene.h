#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	enum eBUTTON {
		eBUTTON_START = 0,
		eBUTTON_TILE_PATHFIND = eBUTTON_START,
		eBUTTON_FREE_CHASING,
		eBUTTON_FREE_INTERCEPT,
		eBUTTON_FREE_PATTERN,
		eBUTTON_FREE_GROUP,
		eBUTTON_BASIC_PATHFIND,
		eBUTTON_ASTER_PATHFIND,
		eBUTTON_GENETIC_ALGORITHM,
		eBUTTON_NUM,
	};
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float delta);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	// 画面遷移ボタン.
	void selectchapterbtn(cocos2d::Ref* pSender, int btnid);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
};

#endif // __HELLOWORLD_SCENE_H__
