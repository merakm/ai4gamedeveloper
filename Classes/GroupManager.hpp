//
//  GroupManager.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/04.
//
//

#ifndef GroupManager_hpp
#define GroupManager_hpp

USING_NS_CC;
#include "Craft.hpp"

class CGroupCraft : public CCraft {
	
public:
	enum eVEC {
		eVEC_SEP_FORCE = 0,
		eVEC_COH_FORCE,
		eVEC_ALG_FORCE,
		eVEC_AVEVEL,
		eVEC_VELOCITY,
		
		eVEC_NUM,
	};
	
public:
	CGroupCraft();
	~CGroupCraft(){}
	
	virtual void Init(Vec3 pos, sCraftParam param);
	virtual void Update(float dt);
	
	Vec3 SepForce;
	Vec3 CohForce;
	Vec3 AlgForce;
	Vec3 AvePos;
	Vec3 AveVel;
	
	cocos2d::LayerColor* parent;

	DrawNode* pDrowNode[eVEC_NUM];
	
	DrawNode *SepArea;
	DrawNode *VisibleArea;
	
	bool bShowInfo;
public:
	void ShowInfo( bool flag = true );
	
private:
	void DrowInfo();
	void ClearInfo();
};

class CGroupManager {
	
public:
	enum eMODE {
		eMODE_ALL,
		eMODE_WIDE,
		eMODE_LIMITED,
		eMODE_NARROW,
		eMODE_NUM,
		
		eMODE_INVALID = -1,
	};
	
	enum {
		_SEPARATION_FACTOR = 1,
		_BACK_VIEW_ANGLE_FACTOR = 1,
		_FRONT_VIEW_ANGLE_FACTOR = 1,
	};
	
public:
	enum {
		UNIT_NUM = 10,
		UNIT_ROW_NUM = 3,
		UNIT_LEADER = -1, // リーダーのID,
	};
	
public:
	CGroupManager();
	~CGroupManager();
	
	void init(Vec3 pos, float orientation);
	void update( float delta );
	void SetTarget(Vec3 pos);
	void SetMode( eMODE	mode){ m_mode = mode; }
	void SetForDrow( cocos2d::LayerColor* parent );
	Sprite* pGetSprite(int i) { return m_Unit[i].pGetSprite(); }
	void ShowInfo( bool flag = true	);
	
private:
	void DoUnitAI(int index);
	void DoAllUnitAI();
	void UpdateAllUnit(float delta);
	bool IsInView(Vec3 pos);
private:
	
	CGroupCraft m_Unit[UNIT_NUM];
	eMODE	m_mode;
	Vec3	m_targetPos;
	bool	m_bsettarget;

public:
	bool bShowInfo;
};

#endif /* GroupManager_hpp */
