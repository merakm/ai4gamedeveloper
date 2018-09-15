//
//  Chapter2FieldDlg.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/15.
//
//

#ifndef Chapter2FieldDlg_hpp
#define Chapter2FieldDlg_hpp

USING_NS_CC;

#include "LayerBase.h"
#include "Craft.hpp"

class Chapter2FieldDlg : public LayerBase {
	
	enum eCHARA {
		eCHARA_START = 0,
		eCHARA_TARGET = eCHARA_START,
		eCHARA_PREDETOR,
		eCHARA_NUM,
	};
	
	enum eTEXT {
		eTEXT_START = 0,
		eTEXT_SPEED = eTEXT_START,
		eTEXT_ANG_SPEED,
		eTEXT_SIDE_THRUSTER,
		eTEXT_FORCE,
		eTEXT_MOMENT,
		eTEXT_NUM,
	};
	
public:
	enum eMODE {
		eMODE_START = 0,
		eMODE_CHASING = eMODE_START,
		eMODE_INTERCEPT,
		eMODE_NUM,
		eMODE_INVALID = -1,
	};
	
public:
	Chapter2FieldDlg();
	~Chapter2FieldDlg(){};
	DECLEAR_H(Chapter2FieldDlg);
	
	void addinit();
	void update(float delta);
	void SetMode(eMODE mode);
	
	// クリックの取得.	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	virtual bool onMouseClick(Event* pEvent);	// クリック開始.
	virtual void onMouseUp(Event* pEvent);		// クリック終了.
#else
	virtual bool onClickBegin(Touch* pTouch, Event* pEvent);	// クリック開始.
#endif
	
private:
	void UpdateCharacter(float delta);
	void UpdateCharacterInfo();
	
private:
	Label*		m_text[eTEXT_NUM];
	Label*		m_target;
	CCraft		m_Character[eCHARA_NUM];
	eMODE		m_mode;
};
#endif /* Chapter2FieldDlg_hpp */
