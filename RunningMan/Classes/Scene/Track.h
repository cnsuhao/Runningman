#ifndef __TRACK_H__
#define __TRACK_H__

#include "cocos2d.h"
#include "Trap/TrapManager.h"
#include "Item/ItemManager.h"

enum ProjectileType;

class ProjectileBase;

class Track : public cocos2d::Layer
{
private:
	static const int NumTrapPoint;
	float MaxDegree;


	cocos2d::Vec2 m_TrackCenter;
	float m_radius;

	cocos2d::ValueVector m_TrapPointList;

	//cocos2d::Vector<Item*> m_ItemList;
	//cocos2d::Vector<CoinEdge*> m_CoinEdgeList;

	//cocos2d::Vector<Projectile*> m_Projectiles;
	//cocos2d::Vector<Projectile*> m_ProjectileDelList;

	float m_OffsetTrapAngle;

	int m_AppearCoin;
public:
	Track(void);
	~Track(void);

	void restart();

	void destoryAllTrackObject();

	void InitTrackData(cocos2d::Vec2 center, float r);

	void update(float dt);

	float getTrapAngle(int index);

	TrapBase* getTrap(float angle);

	void CreateTrap(float angle, TrapType type);

	bool checkTrap(float angle);

	int numActiveTrap();

	void delTrap(float angle);

	ItemBase* getItem(float angle);

	void CreateItem(float angle, ItemType type);

	bool checkItem(float angle);

	void delItem(float angle);

	////Projectile
	ProjectileBase* CreateProjectile(ProjectileType type, float angle);

	bool checkProjectile(float angle);

	//Coin
	void deleteDeadCoin();

	void collectedCoin();

	int getAppearCoin();

	void CreateCoinEdge();

	void CreateAllCoin();

	//
	void gamePause();

	void gameResume();
};

#endif //__TRACK_H__