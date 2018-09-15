//
//  Chapter4FieldDlg.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/04.
//
//

#ifndef Chapter4FieldDlg_hpp
#define Chapter4FieldDlg_hpp


#include "LayerBase.h"
#include "GroupManager.hpp"

class Chapter4FieldDlg : public LayerBase {
	
	enum eTEXT {
		eTEXT_START = 0,
		eTEXT_NUM = eTEXT_START,
	};
	
public:
	
public:
	Chapter4FieldDlg();
	~Chapter4FieldDlg(){};
	DECLEAR_H(Chapter4FieldDlg);
	
	void addinit();
	void update(float delta);
	
	void selectchapterbtn(cocos2d::Ref* pSender);
	
	// クリックの取得.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	virtual bool onMouseClick(Event* pEvent);	// クリック開始.
	//virtual void onMouseUp(Event* pEvent);		// クリック終了.
#else
	//virtual bool onClickBegin(Touch* pTouch, Event* pEvent);	// クリック開始.
#endif
	
private:
	
private:
	CGroupManager m_UnitManager;
	Label*		m_target;

};
#endif /* Chapter4FieldDlg_hpp */
