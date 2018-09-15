//
//  PatternCraft.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/03.
//
//

#include "PatternCraft.hpp"

CPatternCraft::CPatternCraft() : CCraft() {
	
}

void CPatternCraft::Init(Vec3 pos, sCraftParam param) {
	
	CCraft::Init(pos, param);
	m_ChangeParam.InitialPos = m_pos;
	m_ChangeParam.InitialOrientation = m_orientation;
	m_ChangeParam.CurrentID = 0;
	m_ChangeParam.Loop = false;
	
	m_PatternParam[0].distanceLimit = 100.f;
	m_PatternParam[0].orientationLimit = (0.f);
	m_PatternParam[0].loop = false;
	
	m_PatternParam[1].distanceLimit = 100.f;
	m_PatternParam[1].orientationLimit = (45.f);
	m_PatternParam[1].loop = false;

	m_PatternParam[2].distanceLimit = 200.f;
	m_PatternParam[2].orientationLimit = (-90.f);
	m_PatternParam[2].loop = true;

	m_PatternParam[3].distanceLimit = 200.f;
	m_PatternParam[3].orientationLimit = (90.f);
	m_PatternParam[3].loop = true;
	
}

void CPatternCraft::Update(float delta){
	
	bool bNext = UpdatePattern();
	CCraft::Update(delta);
	
	if (!bNext) {
		m_ChangeParam.CurrentOrientation = m_orientation - m_ChangeParam.InitialOrientation;
		m_ChangeParam.CurrentDistance = m_pos.distance(m_ChangeParam.InitialPos);
	}
	else {
		m_ChangeParam.InitialOrientation = m_orientation;
		m_ChangeParam.InitialPos = m_pos;
		m_ChangeParam.CurrentDistance = 0.f;
		m_ChangeParam.CurrentOrientation = 0.f;
	}

}

bool CPatternCraft::UpdatePattern() {

	int id = m_ChangeParam.CurrentID;
	if ( id < 0 || PATTERN_MAX <= id ) {
		m_ChangeParam.CurrentID = id = 0;
		m_ChangeParam.Loop = true;
	}
	
	if ( m_ChangeParam.Loop ) {
		while ( !m_PatternParam[id].loop && id <= PATTERN_MAX ) {
			id++;
		}
		m_ChangeParam.CurrentID = id;
		if (id >= PATTERN_MAX ) return true;
	}
	
	bool bUpdateAngle = ( fabs(m_ChangeParam.CurrentOrientation) <= fabs(m_PatternParam[id].orientationLimit) );
	bool bUpdateDist  = ( m_ChangeParam.CurrentDistance <= m_PatternParam[id].distanceLimit );
	
	if (bUpdateAngle) {
		float angle = m_PatternParam[id].orientationLimit;
		SetThruster(angle > 0, angle < 0 );
	}
	else {
		SetThruster(false, false );
	}
	
	if (!bUpdateDist) {
		m_ChangeParam.CurrentID++;
		return true;
	}
	return false;
}