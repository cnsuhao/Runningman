#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include <string.h>

#include "Manager\PlayerStatusMgr.h"

class SkillBase;

enum TrapType;
enum ItemType;

enum GameRoleType
{
	GameRoleType_ARSEHOLE = 0,
	GameRoleType_PHARAOH,
	GameRoleType_MUMMY,
	GameRoleType_MATCHMAN,
};

class Player : public cocos2d::Sprite
{
	enum ManAnimType
        {
            MAN_RUN = 0,
            MAN_JUMP,
            MAN_FALL,
            MAN_LOSE,
            MAN_WIN,
            MAN_ELECTRIC,
            MAN_ANGER,
            MAN_FLY,
            MAN_SPECIALRUN,
            MAN_SPECIALJUMP,
        };

protected:
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	//std::string* ActionsName;
	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;

	float m_Width;
	float m_Height;

public:
	void setWidth(float wd){ m_Width = wd; }
	void setHeight(float hg){ m_Height = hg; }

	float getWidth(){ return m_Width; }
	float getHeight(){ return m_Height; }

	void SetResource();
	//----------------------------------------------------------------------
public:
	Player(int id);
	~Player(void);

	int GetPlayerID()
	{
		return m_PlayerID;
	}

protected:
	int m_PlayerID;

	std::string m_RoleType;

    float m_RunAV;

    float m_RunAV_Power1;

    float m_RunAV_Power2;

    float m_RunAV_Power3;

    float m_SpeedUpAV;

    float m_CurRunAV;

    float m_TotalRunAngle;//判断游戏胜利的关键

    int m_SpeedUpCurTime;
    int m_SpeedUpMaxTime;

    int m_RetreatCurTime;
    int m_RetreatMaxTime;

    int m_AngerCurTime;
    int m_AngerMaxTime;

    int m_RushCurTime;
    int m_RushMaxTime;

    int m_FlyCurTime;
    int m_FlyMaxTime;

    float m_MaxJumpHeight;
    float m_MinJumpHeight;
    float m_StepJumpHeight;
    float m_CurJumpHeight;

	cocos2d::Vec2 m_SavedOldAncho;
    cocos2d::Vec2 m_SavedRotateBy;
    cocos2d::Vec2 m_OldSavedPos;

	 //Skill
	int m_CurPower;
        
    bool m_bTurboPowerUp;
    float m_CurTurboPowerUpTime;
    float m_MaxTurboPowerUpTime;

	SkillBase* m_PlayerSkill_Run;
	SkillBase* m_PlayerSkill_Jump;
	SkillBase* m_PlayerSkill_Fall;

	std::string m_matchManTextureName;

	int m_CollectCoin;

	int m_VictoryViews;

public:
	PlayerStatusMgr* m_FSM;

	int m_MaxPower;

	float m_PowerUpTime;
	float m_StandardPowerUpTime;

	//int m_iCurPlayJumpEffect = -1;
 //   int m_iCurPlayEleEffect = -1;
 //   int m_iCurPlayFallEffect = -1;
 //   int m_iCurPlaySpeedUpEffect = -1;
 //   int m_iCurHurrayEffect = -1;
 //   int m_iCurCounterEffect = -1;

    //protected int m_VictoryViews = 0;

    float m_OriginalRotation;

public:
	std::string Player::getRoleType();
	void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);
	void setRunAngularVelocity(float v);
	void setSpeedUpRunAngularVelocity(float v);
	void checkSpeed();
	void setJumpHeight(float maxheight, float stepheight);
	float getTotalRunAngle();
	void update(float dt);
	void startRun();
	void stopRun();

	void startRetreatRun();
	void retreatStep();

	bool isRetreatOver();
	void speedUpRun();
	void speedUpStep();
	void speedUpOver();
	int getSpeedUpCurTime();
	void setSpeedUpMaxTime(int maxtime);
	void rushRun();
	void rushStep();
	void rushOver();
	void angerRun();
	void angerStep();
	void angerOver();
	int getAngerCurTime();
	int getRushCurTime();
	void setAngerMaxTime(int maxtime);
	void flyStart();
	void flyStep();
	void flyOver();
	int getFlyCurTime();
	void setFlyMaxTime(int maxtime);

	void loseGame();
	void winGame();

	void jump();
	void jumpUpStep();
	void jumpDownStep();
	void jumpOver();
	bool isCurJumpHeightOverZero();

	bool isCurJumpHeightOverMax();

	void useJump();
	virtual void useSkill();
	bool catchTrap(TrapType pTrapType);
	bool catchItem(ItemType pItemType);

	void win();
	void lose();
	bool iswin();
	bool islose();
	virtual void restart();
	void PowerUp();
	void PowerDown();
	void TurboPowerUp();
	int GetPower();
	int GetVictoryViews();
	void CollectCoin();
	void CollectCoinToHome();
	int GetCollectCoin()
	{
		return m_CollectCoin;
	}
	//----------------
	void playRunAnimation();

	void playSpeedUpRunAnimation();

	void playAngerRunAnimation();

	void playFlyAnimation();

	void playLoseGameAnimation();

	void playWinGameAnimation();

	void playFallAnimation();
	void callback_playFallAnimation();

	void playElectricAnimation();
	void callback_playElectric();

	void playJumpAnimation();
};

#endif //__Player_H__