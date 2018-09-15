//
//  TilePathFinder.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/13.
//
//

#include "TilePathFinder.hpp"

CTilePathFinder* CTilePathFinder::pInstance = nullptr;

CTilePathFinder* CTilePathFinder::pGetInstance(){
	
	if (!pInstance) {
		pInstance = new CTilePathFinder;
	}
	return pInstance;
	
}

int CTilePathFinder::PathFindBresenham(Vec2 vecStart, Vec2 vecGoal, std::list<Vec2> &tileList) {
	
	tileList.clear();
	
	Vec2 vecNext = vecStart;
	Vec2 vecDelta = vecGoal - vecStart;
	Vec2 vecStep = Vec2();
	int currentStep = 0;
	int fraction;
	
	// 方向決定.
	vecStep.x = (vecDelta.x < 0 ) ? -1.0 : 1.0;
	vecStep.y = (vecDelta.y < 0 ) ? -1.0 : 1.0;
	vecDelta.x = fabs(vecDelta.x * 2);
	vecDelta.y = fabs(vecDelta.y * 2);
	
	// 一歩目はスタート地点.
	tileList.push_back(vecStart);
	currentStep++;

	if (vecDelta.x > vecDelta.y) {
		fraction = vecDelta.y * 2 - vecDelta.x;
		while (vecNext.x != vecGoal.x) {
			if (fraction >= 0) {
				vecNext.y = vecNext.y + vecStep.y;
				fraction -= vecDelta.x;
			}
			vecNext.x += vecStep.x;
			fraction += vecDelta.y;
			tileList.push_back(vecNext);
			currentStep++;
		}
	}
	else {
		fraction = vecDelta.x * 2 - vecDelta.y;
		while (vecNext.y != vecGoal.y) {
			if (fraction >= 0) {
				vecNext.x = vecNext.x + vecStep.x;
				fraction -= vecDelta.y;
			}
			vecNext.y += vecStep.y;
			fraction += vecDelta.x;
			tileList.push_back(vecNext);
			currentStep++;
		}
	}
	
	return currentStep;
}


int (CTilePathFinder::*CTilePathFinder::pPathFindFunc[])(Vec2 start , Vec2 end , std::list<Vec2> &tiles) = {
	&CTilePathFinder::PathFindBresenham,
};

int	CTilePathFinder::PathFind(Vec2 vecStart, Vec2 vecGoal, std::list<Vec2> &tileList) {
	
	return (this->*CTilePathFinder::pPathFindFunc[m_type])(vecStart, vecGoal, tileList);
}

