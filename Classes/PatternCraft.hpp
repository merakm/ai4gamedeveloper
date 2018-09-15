//
//  PatternCraft.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/03.
//
//

#ifndef PatternCraft_hpp
#define PatternCraft_hpp

#include "Craft.hpp"

struct sPatternParam {
	float distanceLimit;	// どれだけ進むか.
	float orientationLimit;	// どれだけ回るか.
	bool  loop;	// 2回目以降も呼ばれるか.
	
	sPatternParam (){
		distanceLimit = 0;
		orientationLimit = 0;
		loop = false;
	}
};

struct sChangeParam {
	Vec3	InitialPos;
	float	InitialOrientation;
	float	CurrentDistance;
	float	CurrentOrientation;
	int		CurrentID;
	bool	Loop;
};

class CPatternCraft : public CCraft {
	
public:
	enum {
		PATTERN_MAX = 10,
	};
	
public:
	CPatternCraft();
	~CPatternCraft(){}
	
	virtual void Init(Vec3 pos, sCraftParam param);
	virtual void Update( float delta );
	bool UpdatePattern();
	
	sPatternParam	m_PatternParam[PATTERN_MAX];
	sChangeParam	m_ChangeParam;
};

#endif /* PatternCraft_hpp */
