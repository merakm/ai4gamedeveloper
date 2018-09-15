//
//  Chapter2Field.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/01/15.
//
//

#ifndef Chapter2Field_hpp
#define Chapter2Field_hpp

USING_NS_CC;

#define deg_to_rad(deg) (((deg)/360)*2*M_PI)
#define rad_to_deg(rad) (((rad)/2/M_PI)*360)

class CCraft {
	
	enum {
		VELOCITY = 1,
		SIZE_WIDTH = 50,
		SIZE_HEIGHT = 35,
	};
public:
	
	enum eMODE {
		eMODE_START = 0,
		eMODE_CHASING = eMODE_START,
		eMODE_INTERCEPT,
		eMODE_NUM,
		eMODE_INVALID = -1,
	};
	
public:
	// キャラクターのパラメータ.
	struct sCraftParam {
		
		float	m_mass;				// 質量.
		float	m_mainThrustMax;	// メインスラスターの最大出力.
		float	m_sideThrustMax;	// サイドスタスターの最大出力.
		Vec3	m_sideThrustPosL;	// 左サイドスタスターの位置(m_posからの相対位置).
		Vec3	m_sideThrustPosR;	// 右サイドスタスターの位置(m_posからの相対位置).
		Vec3	m_centerPos;		// 重心位置.
		float	m_speedMax;			// 最高速度.
		float	m_angspeedMax;		// 最高角速度.
		Size	m_size;				// 大きさ.
		float	m_inertia;			// 慣性.

		sCraftParam() {
			m_size = Size( SIZE_WIDTH, SIZE_HEIGHT );
			
			m_mass = 10;
			m_inertia = 10;

			m_centerPos = Vec3(0.0, 0.0,0.0);
			m_speedMax = 30;
			m_mainThrustMax = 80;
			m_sideThrustMax = 10;

			m_sideThrustPosL.x = -(float)m_size.height/2.0;	m_sideThrustPosL.y = m_size.width / 2.0;
			m_sideThrustPosR.x = (float)m_size.height/2.0;	m_sideThrustPosR.y = m_size.width / 2.0;
		}

	};
	
public:
	CCraft();
	~CCraft();
	virtual void Init(Vec3 pos, sCraftParam param);
	void Stop();
	virtual void Update(float dt);


	void SetTarget( Vec3 targetPos );
	void SetTarget( CCraft *pTarget );
	void ResetTarget(){ m_bHaveTarget = false; }
	void SetThruster( bool left, bool right );
	void SetThruster( float forceleft, float forceright );
	void SetMainThruster( float force );
	void SetMode(eMODE mode){ m_mode = mode; }
	
	
	Sprite* pGetSprite(){ return m_sprite; }
	Vec3	GetPos(){ return m_pos; }

	
	Vec3 Rotate2D(float angle, Vec3 u); // ローカル座標系からグローバル座標へ変換.

private:
	void UpdateForce();	// 力の更新.
	void UpdateForceToTarget();	// Targetへ向かう力の調整.
	
public:

	sCraftParam m_param;		// 基本パラメータ.
	
	Vec3	m_pos;				// 位置.
	Vec3	m_velocity;			// 速度.
	Vec3	m_angVelocity;		// 角速度.
	Vec3	m_velocityBody;		// キャラクターからみた速度.
	Vec3	m_angVelocityBody;	// キャラクターからみた角速度.
	float	m_orientation;		// 向き.

	Vec3	m_force;			// かかっている力.
	Vec3	m_moment;			// かかっているモーメント.
	Vec3	m_sideThrusterForceL;	// 左サイドスラスターの出力.
	Vec3	m_sideThrusterForceR;	// 右サイドスラスターの出力.
	Vec3	m_mainThrusterForce;	// メインスラスターの出力.
	
	
	CCraft*	m_targetCraft;		// 目標.
	Vec3	m_targetPos;		// 目標座標.
	bool	m_bHaveTarget;		// 目標があるか.
	eMODE	m_mode;				// 移動モード.
	Sprite* m_sprite;			// モデル.
};

#endif /* Chapter2Field_hpp */
