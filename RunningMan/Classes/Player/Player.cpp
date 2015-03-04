#include "Player.h"
#include "Player/PlayerStatus.h"
#include "UI/GameUILayer.h"

#include "Player/Player_MatchMan.h"
#include "Player/Player_Mummy.h"
#include "Player/Player_Pharaoh.h"
#include "Player/Player_Protagonist.h"

#include "Scene/GameScene.h"

#include "Effect/EffectManager.h"

#include "Sound/SoundManager.h"

#include "Level/LevelManager.h"

#include "Trap/TrapManager.h"
#include "Item/ItemManager.h"

#include "Skill/SkillBase.h"

#include "ResDef.h"
USING_NS_CC;

Player::Player(int id)
{
	std::string test[10] = {"run", "jump", "falldown", "lose", "win", "ele", "anger", "fly", "sperun", "spejump"};
	//ActionsName = test; 
	for (int i=0; i<10; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	m_PlayerID = id;

    m_FSM = new PlayerStatusMgr(this);

    m_CurRunAV = 0.0f;

    m_RunAV = 0.0f;

    m_SpeedUpAV = 0.0f;

    m_TotalRunAngle = 0.0f;

    m_CurJumpHeight = 0.0f;

    m_MinJumpHeight = 20.0f;
    m_MaxJumpHeight = 50.0f;
    m_StepJumpHeight = 1.0f;

    m_CurPower = 0;
    m_MaxPower = 3;

    m_StandardPowerUpTime = 8.0f;
    m_PowerUpTime = m_StandardPowerUpTime;

    m_bTurboPowerUp = false;
    m_CurTurboPowerUpTime = 0.0f;
    m_MaxTurboPowerUpTime = 20.0f;

    m_CollectCoin = 0;

    //m_CurPowerNeedAngle = 0.0f;
    //m_AddPowerNeedAngle = 90.0f;

    m_SpeedUpCurTime = 0;
    m_SpeedUpMaxTime = 80;

    m_RetreatCurTime = 0;
    m_RetreatMaxTime = 20;

    m_AngerCurTime = 0;
    m_AngerMaxTime = 40;

    m_RushCurTime = 0;
    m_RushMaxTime = 50;

    m_FlyCurTime = 0;
    m_FlyMaxTime = 50;
            

    m_FSM->SetPlayerStatus(Player_Stop::Instance());

	Scene* pRunningScene = Director::getInstance()->getRunningScene();
	if (pRunningScene != nullptr)
	{
		Node* pLayer = pRunningScene->getChildByTag(GameUILayer::LayerTag);
		GameUILayer* pGameUILayer = (GameUILayer*)pLayer;
		if (pGameUILayer != nullptr)
		{
			if (m_PlayerID == 1)
			{
				pGameUILayer->setPlayerA_Power(0);
			}
			else if (m_PlayerID == 2)
			{
				pGameUILayer->setPlayerB_Power(0);
			}
		}

	}
}


Player::~Player(void)
{
}

//---------------------------------------------------------------------
void Player::SetResource()
{
	//Texture
	//init animation
	

	if (m_framesDict.size() == 0)
	{
		int numAnim = m_ActionsFrameCount.size();
		//m_framesDict = new cocos2d::Map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>*>();
		m_framesDict.clear();
		for (int i = 0; i < numAnim; ++i)
		{
			cocos2d::Vector<cocos2d::SpriteFrame*> temp; //= new cocos2d::Vector<cocos2d::SpriteFrame*>();

			int numAction = m_ActionsFrameCount.at(i).asInt();
			for (int k = 0; k < numAction; ++k)
			{
				std::string frameName = ActionsName[i];

				std::stringstream ss;
				ss<<k; 
				std::string kStr = ss.str();
				frameName = m_matchManTextureName + "_" + frameName + "_" + kStr + ".png";

				cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

				if (spriteframe != nullptr)
				{
					temp.pushBack(spriteframe);
				}
				//
				if (k == numAction - 1)
				{
					if (temp.size() != 0)
					{
						m_framesDict.insert(std::pair<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>>(ActionsName[i],temp));
					}
					break;
				}
			}
		}
	}

	std::string initName = m_matchManTextureName + "_" + ActionsName[0] + "_0.png";
	initWithSpriteFrameName(initName);
	cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(initName);
	this->m_Width = frame->getRect().size.width;
	this->m_Height = frame->getRect().size.height;
}
//---------------------------------------------------------------------

std::string Player::getRoleType()
{
	return m_RoleType;
}
void Player::setRotateByPoint(Vec2 playerpos, Vec2 anchopos, float rot, Vec2 rotateBy)
{
	this->setPosition(playerpos);
            
	if (m_Width > 0.0f && m_Height > 0.0f)
    {
        float ax = 0.5f - (rotateBy.x - anchopos.x) / m_Width;
        float ay = 0.5f - (rotateBy.y - anchopos.y) / m_Height;
		this->setAnchorPoint(Vec2(ax, ay));
		m_SavedOldAncho = this->getAnchorPoint();
        m_OldSavedPos = anchopos;
        m_SavedRotateBy = rotateBy;
    }
    else
    {
        //有问题;
    }

	this->setRotation(rot);
    m_OriginalRotation = rot;

    m_FSM->SetPlayerStatus(Player_Run::Instance());
}
void Player::setRunAngularVelocity(float v)
{
	m_RunAV = v;

    if (m_RunAV > 0.0f)
    {
        m_RunAV_Power1 = m_RunAV + 0.02f;

        m_RunAV_Power2 = m_RunAV_Power1 + 0.05f;

        m_RunAV_Power3 = m_RunAV_Power2 + 0.1f;
    }
    else
    {
        m_RunAV_Power1 = m_RunAV - 0.02f;

        m_RunAV_Power2 = m_RunAV_Power1 - 0.05f;

        m_RunAV_Power3 = m_RunAV_Power2 - 0.1f;
    }
}
void Player::setSpeedUpRunAngularVelocity(float v)
{
	m_SpeedUpAV = v;
}
void Player::checkSpeed()
{
	if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance() ||
                m_FSM->GetCurPlayerStatus() == Player_Jump::Instance())
    {
        switch (m_CurPower)
        {
            case 0:
                m_CurRunAV = m_RunAV;
                break;
            case 1:
                m_CurRunAV = m_RunAV_Power1;
                break;
            case 2:
                m_CurRunAV = m_RunAV_Power2;
                break;
            case 3:
                m_CurRunAV = m_RunAV_Power3;
                break;
        }
    }
}
void Player::setJumpHeight(float maxheight, float stepheight)
{
	m_MaxJumpHeight = maxheight;
	m_StepJumpHeight = stepheight;
}
float Player::getTotalRunAngle()
{
	return m_TotalRunAngle;
}
void Player::update(float dt)
{
	CCSprite::update(dt);

	if (m_FSM != NULL)
    {
        m_FSM->update(dt);
    }

	float currot = this->getRotation();
	currot += m_CurRunAV;
	this->setRotation(currot);

    if (currot > 360.0f)
    {
		this->setRotation(currot - 360.0f);
    }
    else if (currot < -360.0f)
    {
		this->setRotation(currot + 360.0f);
    }

    m_TotalRunAngle -= m_CurRunAV;
            
    if (m_bTurboPowerUp)
    {
        m_CurTurboPowerUpTime-=dt;
        if (m_CurTurboPowerUpTime <= 0.0f)
        {
            m_CurTurboPowerUpTime = 0.0f;
            m_PowerUpTime = m_StandardPowerUpTime;
            m_bTurboPowerUp = false;
        }
    }

    checkSpeed();
}
void Player::startRun()
{
	switch (m_CurPower)
    {
        case 0:
            m_CurRunAV = m_RunAV;
            break;
        case 1:
            m_CurRunAV = m_RunAV_Power1;
            break;
        case 2:
            m_CurRunAV = m_RunAV_Power2;
            break;
        case 3:
            m_CurRunAV = m_RunAV_Power3;
            break;
    }
    stopAllActions();
    playRunAnimation();
}

void Player::stopRun()
{
	m_CurRunAV = 0.0f;
	stopAllActions();
}

void Player::startRetreatRun()
{
	m_CurRunAV = -m_RunAV;
    stopAllActions();
    playRunAnimation();

    m_RetreatCurTime = m_RetreatMaxTime;
}

void Player::retreatStep()
{
	m_RetreatCurTime--;
}

bool Player::isRetreatOver()
{
	if (m_RetreatCurTime<=0)
    {
        m_RetreatCurTime = 0;
        return true;
    }
    return false;
}

void Player::speedUpRun()
{
	switch (m_CurPower)
    {
        case 0:
            m_CurRunAV = m_RunAV + m_SpeedUpAV;
            break;
        case 1:
            m_CurRunAV = m_RunAV_Power1 + m_SpeedUpAV;
            break;
        case 2:
            m_CurRunAV = m_RunAV_Power2 + m_SpeedUpAV;
            break;
        case 3:
            m_CurRunAV = m_RunAV_Power3 + m_SpeedUpAV;
            break;
    }
    stopAllActions();
    playSpeedUpRunAnimation();

    m_SpeedUpCurTime = m_SpeedUpMaxTime;
}

void Player::speedUpStep()
{
	m_SpeedUpCurTime--;
}

void Player::speedUpOver()
{
	m_SpeedUpCurTime = 0;
}

int Player::getSpeedUpCurTime()
{
	return m_SpeedUpCurTime;
}

void Player::setSpeedUpMaxTime(int maxtime)
{
	m_SpeedUpMaxTime = maxtime;
}

void Player::rushRun()
{
	switch (m_CurPower)
    {
        case 0:
            m_CurRunAV = m_RunAV + m_SpeedUpAV;
            break;
        case 1:
            m_CurRunAV = m_RunAV_Power1 + m_SpeedUpAV;
            break;
        case 2:
            m_CurRunAV = m_RunAV_Power2 + m_SpeedUpAV;
            break;
        case 3:
            m_CurRunAV = m_RunAV_Power3 + m_SpeedUpAV;
            break;
    }
    stopAllActions();
    playAngerRunAnimation();

    m_RushCurTime = m_RushMaxTime;
}

void Player::rushStep()
{
	m_RushCurTime--;
}

void Player::rushOver()
{
	m_RushCurTime = 0;
}

void Player::angerRun()
{
	switch (m_CurPower)
    {
        case 0:
            m_CurRunAV = m_RunAV + m_SpeedUpAV;
            break;
        case 1:
            m_CurRunAV = m_RunAV_Power1 + m_SpeedUpAV;
            break;
        case 2:
            m_CurRunAV = m_RunAV_Power2 + m_SpeedUpAV;
            break;
        case 3:
            m_CurRunAV = m_RunAV_Power3 + m_SpeedUpAV;
            break;
    }
    stopAllActions();
    playAngerRunAnimation();
    //this.Color = new cocos2d.ccColor3B(255, 0, 0);

    m_AngerCurTime = m_AngerMaxTime;
}

void Player::angerStep()
{
	m_AngerCurTime--;
}

void Player::angerOver()
{
	m_AngerCurTime = 0;
}

int Player::getAngerCurTime()
{
	return m_AngerCurTime;
}

int Player::getRushCurTime()
{
	return m_RushCurTime;
}

void Player::setAngerMaxTime(int maxtime)
{
	m_AngerMaxTime = maxtime;
}

void Player::flyStart()
{
	m_CurRunAV = m_RunAV + m_SpeedUpAV;
    stopAllActions();
    playFlyAnimation();

    m_FlyCurTime = m_FlyMaxTime;

    m_CurJumpHeight = m_MaxJumpHeight;
	float ax = 0.5f - (m_SavedRotateBy.x - m_OldSavedPos.x) / m_Width;
	float ay = 0.5f - (m_SavedRotateBy.y - m_OldSavedPos.y + m_CurJumpHeight) / m_Height;
	this->setAnchorPoint(Vec2(ax, ay));
}

void Player::flyStep()
{
	m_FlyCurTime--;
}

void Player::flyOver()
{
	m_FlyCurTime = 0;
}

int Player::getFlyCurTime()
{
	return m_FlyCurTime;
}

void Player::setFlyMaxTime(int maxtime)
{
	m_FlyMaxTime = maxtime;
}

void Player::loseGame()
{
	m_CurRunAV = 0.0f;
	stopAllActions();
	playLoseGameAnimation();
}

void Player::winGame()
{
	m_CurRunAV = m_RunAV;
	stopAllActions();
	playWinGameAnimation();
}

void Player::jump()
{
	m_SavedOldAncho = this->getAnchorPoint();
	playJumpAnimation();
}

void Player::jumpUpStep()
{
	m_CurJumpHeight+=m_StepJumpHeight;

	float ax = 0.5f - (m_SavedRotateBy.x - m_OldSavedPos.x) / m_Width;
	float ay = 0.5f - (m_SavedRotateBy.y - m_OldSavedPos.y + m_CurJumpHeight) / m_Height;
	this->setAnchorPoint(Vec2(ax, ay));
}

void Player::jumpDownStep()
{
	m_CurJumpHeight -= m_StepJumpHeight;

	float ax = 0.5f - (m_SavedRotateBy.x - m_OldSavedPos.x) / m_Width;
	float ay = 0.5f - (m_SavedRotateBy.y - m_OldSavedPos.y + m_CurJumpHeight) / m_Height;
	this->setAnchorPoint(Vec2(ax, ay));
}

void Player::jumpOver()
{
	m_CurJumpHeight = m_MinJumpHeight;
	this->setAnchorPoint(m_SavedOldAncho);
}

bool Player::isCurJumpHeightOverZero()
{
	if (m_CurJumpHeight < m_MinJumpHeight)
    {
        return true;
    }
    return false;
}

bool Player::isCurJumpHeightOverMax()
{
	if (m_CurJumpHeight > m_MaxJumpHeight)
	{
		return true;
	}
	return false;
}

void Player::playRunAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_RUN];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,0.1f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(0.4f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);

	this->runAction(pRepeat);
}

void Player::playSpeedUpRunAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_RUN];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,0.05f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(0.25f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);

	this->runAction(pRepeat);
}

void Player::playAngerRunAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_ANGER];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,0.5f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(1.0f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);

	this->runAction(pRepeat);
}

void Player::playFlyAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_FLY];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,1.0f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(1.0f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);

	this->runAction(pRepeat);
}

void Player::playLoseGameAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_LOSE];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,0.2f,0);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(0.25f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);
}

void Player::playWinGameAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_WIN];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,0.2f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(1.0f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);
}

void Player::playFallAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_FALL];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);

	cocos2d::Vector<FiniteTimeAction*> pAcs;

	Animation* ani = Animation::createWithSpriteFrames(temp,0.3f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(1.0f);
	pAcs.pushBack(animaction);

	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(Player::callback_playFallAnimation,this));
	pAcs.pushBack(pCallFunc);

	Sequence* pSec = Sequence::create(pAcs);

	this->runAction(pSec);
}

void Player::callback_playFallAnimation()
{
	m_FSM->SetPlayerStatus(Player_Run::Instance());
}

void Player::playElectricAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_ELECTRIC];
	cocos2d::Vector<cocos2d::SpriteFrame*> temp = m_framesDict.at(name);

	cocos2d::Vector<FiniteTimeAction*> pAcs;

	Animation* ani = Animation::createWithSpriteFrames(temp,0.4f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(1.0f);
	pAcs.pushBack(animaction);

	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(Player::callback_playElectric,this));
	pAcs.pushBack(pCallFunc);

	Sequence* pSec = Sequence::create(pAcs);

	this->runAction(pSec);
}

void Player::callback_playElectric()
{
	m_FSM->SetPlayerStatus(Player_Run::Instance());
}

void Player::playJumpAnimation()
{
	std::string name = ActionsName[(int)ManAnimType::MAN_JUMP];
	cocos2d::Vector<SpriteFrame*> temp = m_framesDict.at(name);
	Animation* ani = Animation::createWithSpriteFrames(temp,0.2f);
	Animate* animaction = Animate::create(ani);
	//animaction->setDuration(1.0f);

	RepeatForever* pRepeat = RepeatForever::create(animaction);
}

//skill
void Player::useJump()
{
	if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
	{
		m_FSM->SetPlayerStatus(Player_Jump::Instance());
	}
}
void Player::useSkill()
{
	bool usingskill = false;
	int beforeusePower = m_CurPower;
	if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
	{
		if (m_PlayerSkill_Run != nullptr)
		{
			int consume = m_PlayerSkill_Run->getConsume();
			if ( consume <= m_CurPower )
			{
				m_PlayerSkill_Run->useSkill();
				m_CurPower -= consume;

				usingskill = true;
			}
		}
	}

	if (m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() ||
		m_FSM->GetCurPlayerStatus() == Player_JumpDown::Instance())
	{
		if (m_PlayerSkill_Jump != nullptr)
		{
			int consume = m_PlayerSkill_Jump->getConsume();
			if (consume <= m_CurPower)
			{
				m_PlayerSkill_Jump->useSkill();
				m_CurPower -= consume;

				usingskill = true;
			}
		}
	}

	if (m_FSM->GetCurPlayerStatus() == Player_Fall::Instance() ||
		m_FSM->GetCurPlayerStatus() == Player_Electric::Instance())
	{
		if (m_PlayerSkill_Fall != nullptr)
		{
			int consume = m_PlayerSkill_Fall->getConsume();
			if (consume <= m_CurPower)
			{
				m_PlayerSkill_Fall->useSkill();
				m_CurPower -= consume;

				usingskill = true;
			}
		}
	}

	cocos2d::Scene* pRunningScene = cocos2d::Director::getInstance()->getRunningScene();
	if (pRunningScene != nullptr)
	{
		cocos2d::Node* pLayer = pRunningScene->getChildByTag(GameUILayer::LayerTag);
		GameUILayer* pGameUILayer = (GameUILayer*)pLayer;
		if (pGameUILayer != nullptr)
		{
			if (m_PlayerID == 1)
			{
				if (beforeusePower == m_MaxPower)
				{
					pGameUILayer->OnProgressA(m_PowerUpTime);
				}
				pGameUILayer->setPlayerA_Power(m_CurPower);
			}
			else if (m_PlayerID == 2)
			{
				if (beforeusePower == m_MaxPower)
				{
					pGameUILayer->OnProgressB(m_PowerUpTime);
				}
				pGameUILayer->setPlayerB_Power(m_CurPower);
			}
		}
	}
}

bool Player::catchTrap(TrapType pTrapType)
{
	if (m_FSM->GetCurPlayerStatus() == Player_Anger::Instance())
	{
		return false;
	}

	//穿棺材的木乃伊的特殊处理,牌子和暴风会被拦住
	if (m_RoleType == "Role_Mummy")
	{
		Player_Mummy* pMummyPlayer = (Player_Mummy*)this;
		if (pMummyPlayer != nullptr)
		{
			if (pTrapType == TrapType::TRAP_BOARD || pTrapType == TrapType::TRAP_STORM || pTrapType == TrapType::TRAP_CLOUD)
			{
				if (pMummyPlayer->m_bUseCoffin == true)
				{
					pMummyPlayer->checkCoffinHP();
					return true;
				}
			}
			else if (pTrapType == TrapType::TRAP_BANANA || pTrapType == TrapType::TRAP_REDCACTUS)
			{
				if (pMummyPlayer->m_bUseCoffin == true)
				{
					if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
					{
						pMummyPlayer->checkCoffinHP();
						return true;
					}
				}
			}
		}
	}

	//不无敌，处理是否中了陷阱
	if (pTrapType == TrapType::TRAP_BANANA || TrapType::TRAP_REDCACTUS)
	{
		//if (m_RoleType == "Role_Protagonist" && typestr == "Trap_Banana")
		//{
		//    return false;
		//}
		if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
		{
			m_FSM->SetPlayerStatus(Player_Fall::Instance());
			return true;
		}
		else if (m_FSM->GetCurPlayerStatus() == Player_Retreat::Instance())
		{
			m_FSM->SetPlayerStatus(Player_Fall::Instance());
			return true;
		}
	}
	else if (pTrapType == TrapType::TRAP_BOARD || pTrapType == TrapType::TRAP_STORM)
	{
		if (m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() ||
			m_FSM->GetCurPlayerStatus() == Player_JumpDown::Instance() ||
			m_FSM->GetCurPlayerStatus() == Player_Fly::Instance())
		{
			m_FSM->SetPlayerStatus(Player_Fall::Instance());
			return true;
		}
	}
	else if (pTrapType == TrapType::TRAP_COFFIN)
	{
		if (m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() ||
			m_FSM->GetCurPlayerStatus() == Player_JumpDown::Instance() ||
			m_FSM->GetCurPlayerStatus() == Player_Run::Instance() ||
			m_FSM->GetCurPlayerStatus() == Player_Fly::Instance())
		{
			m_FSM->SetPlayerStatus(Player_Retreat::Instance());
			return true;
		}
	}
	else if (pTrapType == TrapType::TRAP_CLOUD)
	{
		if (m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() || 
			m_FSM->GetCurPlayerStatus() == Player_JumpDown::Instance() || 
			m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
		{
			m_FSM->SetPlayerStatus(Player_Electric::Instance());
			return true;
		}
	}

	return false;
}
bool Player::catchItem(ItemType pItemType)
{
	if (pItemType == ItemType::Item_Coin)
	{
		if ( (m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() || m_FSM->GetCurPlayerStatus() == Player_Fly::Instance() )
			&& (m_CurJumpHeight>m_MaxJumpHeight-10.0f) )
		{
			//加一个金币收集
			CollectCoin();

			return true;
		}
	}

	return false;
}
void Player::win()
{
	m_FSM->SetPlayerStatus(Player_Win::Instance());
	m_VictoryViews++;
}
void Player::lose()
{
	m_FSM->SetPlayerStatus(Player_Lose::Instance());
}
bool Player::iswin()
{
	if (m_FSM->GetCurPlayerStatus() == Player_Win::Instance())
	{
		return true;
	}
	return false;
}
bool Player::islose()
{
	if (m_FSM->GetCurPlayerStatus() == Player_Lose::Instance())
	{
		return true;
	}
	return false;
}
void Player::restart()
{
	m_CurRunAV = 0.0f;
	m_TotalRunAngle = 0.0f;
	m_CurPower = 0;
	m_SpeedUpCurTime = 0;
	this->setRotation(m_OriginalRotation);

	m_bTurboPowerUp = false;

	if (GameScene::g_GameMode == RunGameMode::MODE_PVC ||
		GameScene::g_GameMode == RunGameMode::MODE_PVP)
	{
		GameLevel* pLevel = LevelManager::Instance()->VsAreaData->GetGameLevel(0);
		if (pLevel != nullptr)
		{
			if (pLevel->getRule() == LevelRule::RULE_CAREFULLY_TRAP)
			{
				m_CurPower = 3;
			}
		}
	}
	else if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->GetGameLevel(curlevel);
		if (ldata != nullptr)
		{
			if (ldata->getRule() == LevelRule::RULE_CAREFULLY_TRAP)
			{
				m_CurPower = 3;
			}
		}
	}
	//if (m_PlayerID == 1)
	//{
	//    this.Color = new cocos2d.ccColor3B(0, 255, 0);
	//}
	//else if (m_PlayerID == 2)
	//{
	//    this.Color = new cocos2d.ccColor3B(255, 255, 0);
	//}

	m_CurJumpHeight = 0.0f;

	m_PowerUpTime = m_StandardPowerUpTime;
	m_bTurboPowerUp = false;
	m_CurTurboPowerUpTime = 0.0f;

	m_CollectCoin = 0;

	m_AngerCurTime = 0;

	m_RushCurTime = 0;

	m_FlyCurTime = 0;

	m_FSM->SetPlayerStatus(Player_Run::Instance());
}
void Player::PowerUp()
{
	if (m_CurPower != m_MaxPower)
	{
		m_CurPower++;
		//if (ResDef.g_ConfigStruct.EnableAudio != 0)
		//{
		//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_PowerUpSound);
		//}
		SoundManager::Instance()->PlayEffect(ResDef::g_JumpSound);
	}
}
void Player::PowerDown()
{
	if (m_CurPower > 0)
	{
		m_CurPower--;
		//if (ResDef.g_ConfigStruct.EnableAudio != 0)
		//{
		//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_PowerDownSound);
		//}
		SoundManager::Instance()->PlayEffect(ResDef::g_PowerDownSound);

		Scene* pRunningScene = Director::getInstance()->getRunningScene();
		if (pRunningScene != nullptr)
		{
			Node* pLayer = pRunningScene->getChildByTag(GameUILayer::LayerTag);
			GameUILayer* pGameUILayer = (GameUILayer*)pLayer;
			if (pGameUILayer != nullptr)
			{
				if (m_PlayerID == 1)
				{
					pGameUILayer->setPlayerA_Power(m_CurPower);
				}
				else if (m_PlayerID == 2)
				{
					pGameUILayer->setPlayerB_Power(m_CurPower);
				} 
			}
		}              
	}
	else if (m_CurPower == 0)
	{
		//if (ResDef.g_ConfigStruct.EnableAudio != 0)
		//{
		//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_PowerDownSound);
		//}
		SoundManager::Instance()->PlayEffect(ResDef::g_PowerDownSound);
		Scene* pRunningScene = Director::getInstance()->getRunningScene();
		if (pRunningScene != nullptr)
		{
			Node* pLayer = pRunningScene->getChildByTag(GameUILayer::LayerTag);
			GameUILayer* pGameUILayer = (GameUILayer*)pLayer;
			if (pGameUILayer != nullptr)
			{
				if (m_PlayerID == 1)
				{
					pGameUILayer->OnProgressA(m_PowerUpTime);
				}
				else if (m_PlayerID == 2)
				{
					pGameUILayer->OnProgressB(m_PowerUpTime);
				} 
			}
		}
	}
}
void Player::TurboPowerUp()
{
	m_bTurboPowerUp = true;
	m_CurTurboPowerUpTime = m_MaxTurboPowerUpTime;

	m_PowerUpTime = m_StandardPowerUpTime/2.0f;

	Scene* pRunningScene = Director::getInstance()->getRunningScene();
	if (pRunningScene != nullptr)
	{
		Node* pLayer = pRunningScene->getChildByTag(GameUILayer::LayerTag);
		GameUILayer* pGameUILayer = (GameUILayer*)pLayer;

		if (pGameUILayer != nullptr)
		{
			Vec2 newBarPos;
			if (m_PlayerID == 1)
			{
				Vec2 barPos = pGameUILayer->PowerBarA->getPosition();
				newBarPos = barPos + Vec2(70.0f,-30.0f);
			}
			else
			{
				Vec2 barPos = pGameUILayer->PowerBarB->getPosition();
				newBarPos = barPos + Vec2(70.0f,-30.0f);
			}
			

			ParticleEffect* effect = EffectManager::Instance()->AddParticle(
				ResDef::g_ParticleEffectLavaFlow,
				newBarPos, 
				m_CurTurboPowerUpTime, 
				nullptr);
			if (effect != nullptr)
			{
				effect->setPositionType(cocos2d::ParticleSystem::PositionType::FREE);

				effect->setBlendAdditive(false);

				pLayer->addChild(effect,100);

				effect->resetSystem();
			}
		}
	}
	//
	
}
int Player::GetPower()
{
	return m_CurPower;
}
int Player::GetVictoryViews()
{
	return m_VictoryViews;
}
void Player::CollectCoin()
{
	;
}
void Player::CollectCoinToHome()
{
	;
}





