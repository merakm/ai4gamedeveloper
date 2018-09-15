#include "HelloWorldScene.h"
#include "Chapter2TileDlg.h"
#include "Chapter2FieldDlg.h"
#include "Chapter3FieldDlg.hpp"
#include "Chapter4FieldDlg.hpp"
#include "Chapter6FieldDlg.hpp"
#include "Chapter15FieldDlg.hpp"
USING_NS_CC;

static const std::string btntext[HelloWorld::eBUTTON_NUM] = {
	"Tile Path Finding",
	"Free Space Chasing",
	"Free Space Intercept",
	"Pattern movement",
	"Flocks, Herds and Schools",
	"Basic Pathfind",
	"A star Pathfind",
	"Genetic Algorithm",
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto titlelabel = Label::createWithTTF("AI for Game Developer", "fonts/arial.ttf", 24);
    
    // position the label on the center of the screen
	Vec2 titlePos(Vec2(origin.x + visibleSize.width/2,
					   origin.y + visibleSize.height - titlelabel->getContentSize().height));
    titlelabel->setPosition(titlePos);

    // add the label as a child to this layer
    this->addChild(titlelabel, 1);
	
	// ボタン.
	for (int i = eBUTTON_START; i < eBUTTON_NUM; ++i) {
		Vec2 pos( titlePos.x, titlePos.y - 20 - 25*(i+1) );
		Label* pbtnlabel = Label::createWithTTF(btntext[i], "fonts/arial.ttf", 20);
		pbtnlabel->setTag(i);
		auto pBtn = MenuItemLabel::create(pbtnlabel, CC_CALLBACK_1(HelloWorld::selectchapterbtn, this, i));
		
		Menu* pMenu = Menu::create(pBtn, NULL);
		pMenu->setPosition(pos);
		this->addChild(pMenu, 1);
	}

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("identicon.png");
	sprite->setOpacity(128);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::update(float delta)
{
	// sprite->setOpacity(64);
	
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


// 画面遷移ボタン.
void HelloWorld::selectchapterbtn(cocos2d::Ref* pSender, int btnid)
{

	log(btntext[btnid].c_str());
	switch (btnid) {
		case eBUTTON_TILE_PATHFIND:
		{
			auto scene = Chapter2TileDlg::createScene();
			Director::getInstance()->pushScene(scene);
		}
			break;
		case eBUTTON_FREE_CHASING:
		{
			auto scene = Chapter2FieldDlg::createScene();
			Chapter2FieldDlg* layer = (Chapter2FieldDlg*)scene->getChildByName("mainLayer");
			layer->SetMode(Chapter2FieldDlg::eMODE_CHASING);
			Director::getInstance()->pushScene(scene);
		}
			break;
		case eBUTTON_FREE_INTERCEPT:
		{
			auto scene = Chapter2FieldDlg::createScene();
			Chapter2FieldDlg* layer = (Chapter2FieldDlg*)scene->getChildByName("mainLayer");
			layer->SetMode(Chapter2FieldDlg::eMODE_INTERCEPT);
			Director::getInstance()->pushScene(scene);
		}
			break;
		case eBUTTON_FREE_PATTERN:
		{
			auto scene = Chapter3FieldDlg::createScene();
			Director::getInstance()->pushScene(scene);
		}
			break;
		case eBUTTON_FREE_GROUP:
		{
			auto scene = Chapter4FieldDlg::createScene();
			Director::getInstance()->pushScene(scene);
		}
			break;
		case eBUTTON_GENETIC_ALGORITHM:
		{
			auto scene = Chapter15FieldDlg::createScene();
			Director::getInstance()->pushScene(scene);
		}
		case eBUTTON_BASIC_PATHFIND:
		{
			auto scene = Chapter6TileDlg::createScene();
			Director::getInstance()->pushScene(scene);
		}
			break;
		default:
			break;
	}
}