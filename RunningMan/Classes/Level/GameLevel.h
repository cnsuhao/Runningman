#ifndef __Game_Level_H__
#define __Game_Level_H__

#include "cocos2d.h"


enum LevelRule
{
	RULE_CATCH_RIVALS = 0,
	RULE_OVER_LAPS,
	RULE_CAREFULLY_TRAP,
	RULE_COLLECT_ALLCOIN,
	RULE_COLLECT_COIN,
};

class LevelRuleData
{
public:
	LevelRuleData()
	{
		m_overLaps = 0;
		m_collectNum = 0;
	}

	int m_overLaps;
	int m_collectNum;
	float matchTime;

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

class GameLevel
{
public:
	GameLevel(void);
	~GameLevel(void);

	LevelRule getRule()
	{
		return m_CurRule;
	}

	void MatchRestart()
	{
		switch (m_CurRule)
		{
		case LevelRule::RULE_COLLECT_COIN:
			{
				m_LimitTime = 60.0f;
			}
			break;
		}
	}

	cocos2d::Vec2 levelPoint;
protected:

	LevelRuleData m_LevelRuleData;

	LevelRule m_CurRule;

	bool m_bCreateCoin;
	int m_ReadyCreateCoinNum;

	bool m_bRandomCoin;

	float m_LimitTime;

	int m_MapTexID;

	bool m_bIsBoss;

	int m_EnemyRoleType;
public:
	void Init(LevelRule rule, int overLaps, int collectNum, bool isboss, int roleType, int sceneTexID);

	bool IsMatchOver();

	bool IsCreateCoin()
	{
		return m_bCreateCoin;
	}

	bool IsRandomCreateCoin()
	{
		return m_bRandomCoin;
	}

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

	LevelRule getRuleType()
	{
		return m_CurRule;
	}

	int getReadyCreateCoinNum()
	{
		return m_ReadyCreateCoinNum;
	}

	bool isBoss() { return m_bIsBoss; }

	int getEnemyRoleType() { return m_EnemyRoleType; }
};

#endif //__Game_Level_H__
