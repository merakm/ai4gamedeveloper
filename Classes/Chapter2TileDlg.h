//
//  Chapter2TileDlg.h
//  test
//
//  Created by Kohei Kumazaki on 2017/01/09.
//
//

#ifndef Chapter2TileDlg_h
#define Chapter2TileDlg_h

USING_NS_CC;

#include "LayerBase.h"
#include "Chapter2Tile.h"
class Chapter2TileDlg : public LayerBase {
	
public:
	Chapter2TileDlg();
	~Chapter2TileDlg();
	DECLEAR_H(Chapter2TileDlg);

	void addinit();
	void update(float delta);

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
};

#endif /* Chapter2TileDlg_h */
