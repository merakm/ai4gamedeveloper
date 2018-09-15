//
//  Chapter6Field.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/10.
//
//

#ifndef Chapter6Field_hpp
#define Chapter6Field_hpp


#include "LayerBase.h"
#include "Chapter2Tile.h"
class Chapter6TileDlg : public LayerBase {
	
	enum eMODE {
		
		eMODE_START = 0,
		eMODE_PATHFIND = eMODE_START,
		eMODE_EDIT,
		eMODE_NUM,
	};
	
public:
	Chapter6TileDlg();
	~Chapter6TileDlg();
	DECLEAR_H(Chapter6TileDlg);
	
	void addinit();
	void update(float delta);
	
	void pushModeChangeBtn( cocos2d::Ref* pSender );
	
	// クリックの取得.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	virtual bool onMouseClick(Event* pEvent);	// クリック開始.
#else
	virtual bool onClickBegin(Touch* pTouch, Event* pEvent);	// クリック開始.
#endif
private:
	bool IsInField( Vec2 pos );
	
private:
	CTileField* m_pfield;
	Label *pModeChangeButton;
	eMODE m_mode;
};


#endif /* Chapter6Field_hpp */
