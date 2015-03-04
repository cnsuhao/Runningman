#ifndef __MAPS_INFO_H__
#define __MAPS_INFO_H__

#include "cocos2d.h"

enum LevelRuleType
{
	RULE_CATCH_RIVALS = 0,
	RULE_OVER_LAPS,
	RULE_CAREFULLY_TRAP,
	RULE_COLLECT_ALLCOIN,
	RULE_COLLECT_COIN,
};

class LevelRule
{
private:
	int m_overLaps;
	int m_collectNum;
	float matchTime;

public:
	void Clear()
	{
		m_overLaps = 0;
		m_collectNum = 0;
		matchTime = 0.0f;
	}

	void SetOverLaps(int laps)
	{
		m_overLaps = laps;
	}

	void SetCollectNum(int coins)
	{
		m_collectNum = coins;
	}

	void SetMatchTime(float time)
	{
		matchTime = time;
	}

	int GetOverLaps()
	{
		return m_overLaps;
	}

	int GetCollectNum()
	{
		return m_collectNum;
	}

	float GetMatchTime()
	{
		return matchTime;
	}
};


struct LevelData
{
	cocos2d::Vec2 levelPoint;

	LevelRule m_LevelRule;

	LevelRuleType m_RuleType;

	bool m_bCreateCoin;

	int m_ReadyCreateCoinNum;

	bool m_bRandomCoin;

	float m_LimitTime;

	int m_MapTexID;

	bool m_bIsBoss;

	int m_EnemyRoleType;

	void Init(LevelRuleType rule, int overLaps, int collectNum, bool isboss, int roleType, int sceneTexID);

	bool IsMatchOver();

	float GetLimitTime()
	{
		return m_LimitTime;
	}

	void LimitTimePassed(float dt)
	{
		m_LimitTime -= dt;
	}

	int getSceneMapTexID()
	{
		return m_MapTexID;
	}

	LevelRuleType getRuleType()
	{
		return m_RuleType;
	}

	int getReadyCreateCoinNum()
	{
		return m_ReadyCreateCoinNum;
	}

	bool isBoss() { return m_bIsBoss; }

	int getEnemyRoleType() { return m_EnemyRoleType; }
};

struct MapData
{
public:
	int LevelNum;;
	std::vector<LevelData*> LevelDatas;
};

class MapsInfo
{
public:
	~MapsInfo(void);

	static MapsInfo* GetInstance();

	void FillInfo();

	std::vector<MapData*> SceneDataPool;
	MapData* VsSceneData;

private:
	MapsInfo(void);

	static const int SceneNum = 1;	

	static MapsInfo* m_Instance;
};

#endif //__MAPS_INFO_H__