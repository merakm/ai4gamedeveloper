//
//  Character.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/10.
//
//

#ifndef Character_h
#define Character_h

USING_NS_CC;

class CTile {
	
public:
	enum {
		TILE_WIDTH = 30,			// タイルの幅
		TILE_HEIGHT = TILE_WIDTH,	// タイルの高さ
	};
	enum eTILE_STATUS {
		eTILE_STATUS_START = 0,
		eTILE_STATUS_EMPTY = eTILE_STATUS_START,
		eTILE_STATUS_TARGET,
		eTILE_STATUS_PREDETOR,
		eTILE_STATUS_ROUTE,
		eTILE_STATUS_WALL,
		eTILE_STATUS_NUM,
	};

public:
	CTile()
	: m_status ( eTILE_STATUS_EMPTY )
	, m_TileSprite( NULL ) {
	};
	~CTile(){};
	
	void			Init( Vec2 pos, eTILE_STATUS status );
	void			Update();
	
	eTILE_STATUS	GetStatus(){ return m_status; }
	Sprite*			pGetSprite(){ return m_TileSprite; }
	
	void			SetStatus( eTILE_STATUS status ){ m_status = status; }
	
private:
	eTILE_STATUS	m_status;
	Sprite*			m_TileSprite;

};

class CTileField {
public:
	enum {
		FIELD_NUM_WIDTH = 30,	// タイルの横個数.
		FIELD_NUM_HEIGHT = 20,	// タイルの縦個数.
	};
	
public:
	CTileField(){};
	~CTileField(){};
	
	void	init();
	void	Update();
	Sprite* pGetTileSprite(int width, int height);
	Rect	GetFieldRect(){ return m_FieldRect; }
	
	void	SetWall(const Vec2 pos, bool bRight );
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	void	TileClicked( const Vec2 pos, bool bPredetor = false );
	void	TileClicked( int width, int height, bool bPredetor = false );
#else
	void	TileClicked( const Vec2 pos );
	void	TileClicked( int width, int height );
#endif //  (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

	
private:
	void	UpdateTiles();
	void	PathFind();
	bool	IsValidIndex( int width, int height) { return (0 <= width && width < FIELD_NUM_WIDTH && 0 <= height && height < FIELD_NUM_HEIGHT); }
	
private:
	CTile	tile[FIELD_NUM_HEIGHT][FIELD_NUM_WIDTH];
	Rect	m_FieldRect;
	bool	m_bPathUpdate;
};

#endif /* Character_h */
