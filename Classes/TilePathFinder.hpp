//
//  TilePathFinder.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/13.
//
//

#ifndef TilePathFinder_hpp
#define TilePathFinder_hpp

#include "Chapter2Tile.h"


// 経路探索.
class CTilePathFinder {
	
public:
	enum eAlgoType {
		eALGO_START = 0,
		eALGO_BRESENHAM = eALGO_START,
		eALGO_NUM,
	};

public:
	
	static CTilePathFinder* pGetInstance();
	int	PathFind(Vec2 vecStart, Vec2 vecGoal, std::list<Vec2> &tileList);
	void SetAlgoType(eAlgoType type){ m_type = type; }

	static int (CTilePathFinder::*pPathFindFunc[eALGO_NUM])(Vec2 start , Vec2 end , std::list<Vec2> &tiles);

private:
	CTilePathFinder(){ m_type = eALGO_BRESENHAM; }
	~CTilePathFinder(){}
	
	int PathFindBresenham(Vec2 vecStart, Vec2 vecGoal, std::list<Vec2> &tileList);
	

	static CTilePathFinder* pInstance;
	eAlgoType m_type;
	
};

#endif /* TilePathFinder_hpp */
