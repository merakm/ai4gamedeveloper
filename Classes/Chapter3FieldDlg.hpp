//
//  Chapter3FieldDlg.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/01.
//
//

#ifndef Chapter3FieldDlg_hpp
#define Chapter3FieldDlg_hpp

USING_NS_CC;

#include "LayerBase.h"
#include "PatternCraft.hpp"

class Chapter3FieldDlg : public LayerBase {
	
	
	enum eTEXT {
		eTEXT_START = 0,
		eTEXT_PATTERN_START = eTEXT_START,
		eTEST_PATTERN_END = CPatternCraft::PATTERN_MAX + eTEXT_PATTERN_START,
		eTEXT_NUM,
	};
	
public:
	
public:
	Chapter3FieldDlg();
	~Chapter3FieldDlg(){};
	DECLEAR_H(Chapter3FieldDlg);
	
	void addinit();
	void update(float delta);
	
	// クリックの取得.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	//virtual bool onMouseClick(Event* pEvent);	// クリック開始.
	//virtual void onMouseUp(Event* pEvent);		// クリック終了.
#else
	//virtual bool onClickBegin(Touch* pTouch, Event* pEvent);	// クリック開始.
#endif
	
private:
	void UpdateCharacter(float delta);
	void UpdateCharacterInfo();
	
private:
	CPatternCraft	m_Character;
	Label*			m_text[eTEXT_NUM];

};

#endif /* Chapter3FieldDlg_hpp */
