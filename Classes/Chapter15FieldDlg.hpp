//
//  Chapter15FieldDlg.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/06.
//
//

#ifndef Chapter15FieldDlg_hpp
#define Chapter15FieldDlg_hpp

#include "LayerBase.h"
#include "GeneticEvolution.hpp"

class Chapter15FieldDlg : public LayerBase {
	
public:
	enum eBUTTON {
		
		eBUTTON_START = 0,
		eBUTTON_EVOLVE_START = eBUTTON_START,
		eBUTTON_NEXT,
		eBUTTON_NUM,
		
	};
	
	
	enum eTEXT {
		eTEXT_START = 0,
		eTEXT_SCORE,
		eTEXT_GEN_INFO_START,
		eTEXT_GEN_INTO_END = eTEXT_GEN_INFO_START + 10,
		eTEXT_GENERATION = eTEXT_GEN_INTO_END,
		eTEXT_MAX_SCORE,
		eTEXT_NUM,
	};
public:
	Chapter15FieldDlg();
	~Chapter15FieldDlg(){};
	DECLEAR_H(Chapter15FieldDlg);
	
	void addinit();
	void update(float delta);
private:
	void DoEvolution();
	
	// クリックの取得.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	// virtual bool onMouseClick(Event* pEvent);	// クリック開始.
	//virtual void onMouseUp(Event* pEvent);		// クリック終了.
#else
	//virtual bool onClickBegin(Touch* pTouch, Event* pEvent);	// クリック開始.
#endif
	
	// ボタン.
	void selectchapterbtn(cocos2d::Ref* pSender, int btnid);
	
private:
	// Label* pBtnLabel[eBUTTON_NUM];
	FlowerEvolution flowerEvolution;
	bool	m_bDoEvolution;
	bool	m_bGenerateFirstGen;
	Label*	pText[eTEXT_NUM];
	double	m_maxScore;
	
};

#endif /* Chapter15FieldDlg_hpp */
