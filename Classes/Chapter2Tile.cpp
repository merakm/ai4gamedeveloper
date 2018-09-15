//
//  Character.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/10.
//
//

USING_NS_CC;
#include "Chapter2Tile.h"
#include "TilePathFinder.hpp"

// ---------------------------------
//	CTileクラス
// ---------------------------------
void CTile::Init(Vec2 pos, eTILE_STATUS status) {
	
	m_status = status;
	m_TileSprite = Sprite::create();
	m_TileSprite->retain();	// 読んで. http://developer.wonderpla.net/entry/blog/engineer/cocos2dx_reference%2Bcounting/
	Rect rect = Rect(0, 0, TILE_WIDTH - 2, TILE_HEIGHT - 2);
	m_TileSprite->setTextureRect(rect);
	m_TileSprite->setPosition(Vec2(pos.x + 1, pos.y + 1));
}

void CTile::Update() {
	
	static const Color3B tilecolor[CTile::eTILE_STATUS_NUM] = {
		Color3B::WHITE, 	// eTILE_STATUS_EMPTY.
		Color3B::RED,		// eTILE_STATUS_CHARACTER,
		Color3B::BLUE,		// eTILE_STATUS_PREDATOR,
		Color3B::ORANGE,	// eTILE_STATUS_ROUTE
		Color3B::BLACK,		// eTILE_STATUS_WALL,
	};
	
	// タイルの色設定.
	m_TileSprite->setColor(tilecolor[m_status]);
	
}


// ---------------------------------
//	CTileFieldクラス
// ---------------------------------
void CTileField::init() {
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size fieldSize = Size(CTile::TILE_WIDTH * FIELD_NUM_WIDTH, CTile::TILE_HEIGHT * FIELD_NUM_HEIGHT);
	
	Vec2 origin( (visibleSize.width - fieldSize.width)/2.0,
				  (visibleSize.height - fieldSize.height)/2.0);
	
	m_FieldRect = Rect(origin, fieldSize);
	m_bPathUpdate = false;
	
	for (int width = 0; width < FIELD_NUM_WIDTH; width++) {
		for (int height = 0; height < FIELD_NUM_HEIGHT; height++) {
			Vec2 pos(origin.x + width * CTile::TILE_WIDTH + CTile::TILE_WIDTH/2.0,  origin.y + height * CTile::TILE_HEIGHT + CTile::TILE_HEIGHT/2.0);
			// 初期化.
			tile[height][width].Init(pos, CTile::eTILE_STATUS_EMPTY);
		}
	}
}

Sprite* CTileField::pGetTileSprite(int width, int height) {
	
	if ( IsValidIndex(width, height) ) {
		return tile[height][width].pGetSprite();
	}
	return NULL;
}

void CTileField::Update() {
	
	// 経路探索.
	PathFind();
	
	// タイルの更新.
	UpdateTiles();
	
}

void CTileField::PathFind() {
	
	if (!m_bPathUpdate) {
		return;
	}
	
	m_bPathUpdate = false;
	Vec2 start, goal;
	bool bstart = false, bgoal = false;
	for (int width = 0; width < FIELD_NUM_WIDTH; width++) {
		for (int height = 0; height < FIELD_NUM_HEIGHT; height++) {
			CTile tmptile = tile[height][width];
			CTile::eTILE_STATUS status = tmptile.GetStatus();
			if ( status == CTile::eTILE_STATUS_PREDETOR ) {
				start = Vec2(width, height);
				bstart = true;
			}
			else if (status == CTile::eTILE_STATUS_TARGET) {
				goal = Vec2(width, height);
				bgoal = true;
			}
		}
		if ( bstart && bgoal) break;
	}
	if (bstart && bgoal) {
		std::list<Vec2> list;
		int nTileNum = CTilePathFinder::pGetInstance()->PathFind(start, goal, list);
		if (nTileNum > 0) {
			for (std::list<Vec2>::iterator it = list.begin(); it != list.end(); ++it) {
				Vec2 vec = (*it);
				int width = (int)vec.x;
				int height = (int)vec.y;
				if (IsValidIndex(width, height)) {
					CTile tmptile = tile[height][width];
					if ( tmptile.GetStatus() == CTile::eTILE_STATUS_EMPTY )
						tile[height][width].SetStatus(CTile::eTILE_STATUS_ROUTE);
				}
			}
		}
	}
	
}
void CTileField::UpdateTiles(){
	
	for (int width = 0; width < FIELD_NUM_WIDTH; ++width) {
		for (int height = 0; height < FIELD_NUM_HEIGHT; ++height) {
			tile[height][width].Update();
		}
	}
}

void	CTileField::SetWall(const Vec2 pos, bool bRight) {

	// 座標はものの中心にあるので幅分だけずらす.
	int width = ((int)pos.x - m_FieldRect.origin.x ) / CTile::TILE_WIDTH;
	int height = ((int)pos.y - m_FieldRect.origin.y ) / CTile::TILE_HEIGHT;

	tile[height][width].SetStatus(bRight ? CTile::eTILE_STATUS_EMPTY : CTile::eTILE_STATUS_WALL);
	
	m_bPathUpdate = true;
	
}

void CTileField::TileClicked( const Vec2 pos
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
							 , bool bPredetor /* = false*/
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
) {

	// 座標はものの中心にあるので幅分だけずらす.
	int width = ((int)pos.x - m_FieldRect.origin.x ) / CTile::TILE_WIDTH;
	int height = ((int)pos.y - m_FieldRect.origin.y ) / CTile::TILE_HEIGHT;

	assert(IsValidIndex(width, height));

	TileClicked(width, height
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
				, bPredetor
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	);
}

void CTileField::TileClicked( int width, int height
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
 , bool bPredetor	/* = false*/
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
 ) {
	
	 if (!IsValidIndex(width, height)) return;
	 
	 
	 if ( tile[height][width].GetStatus() == CTile::eTILE_STATUS_WALL ) {
		 return;
	 }
	 
	 CTile::eTILE_STATUS next =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	 bPredetor ? CTile::eTILE_STATUS_PREDETOR : CTile::eTILE_STATUS_TARGET;
#else
	 CTile::eTILE_STATUS_TARGET;
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	 
	 for (int nWidth = 0; nWidth < FIELD_NUM_WIDTH; nWidth++) {
		 for (int nHeight = 0; nHeight < FIELD_NUM_HEIGHT; nHeight++) {
			 // 初期化.
			 CTile::eTILE_STATUS current = tile[nHeight][nWidth].GetStatus();
			 // 道と次に描画されるタイルは初期化.
			 if ( current == next || current == CTile::eTILE_STATUS_ROUTE ) {
				 tile[nHeight][nWidth].SetStatus(CTile::eTILE_STATUS_EMPTY);
			 }
		 }
	 }
	 
	tile[height][width].SetStatus( next );
	m_bPathUpdate = true;
}

