#include "Player_Mummy.h"
#include "Skill/SkillManager.h"

#include "Player/PlayerStatus.h"
#include "Sound/SoundManager.h"
#include "Scene/GameScene.h"

#include "Effect/EffectManager.h"
#include "Skill/SkillBase.h"
#include "ResDef.h"

Player_Mummy::Player_Mummy(int id) :
		Player(id)
{
	m_RoleType = "Role_Mummy";
	//Skill
	m_PlayerSkill_Run = SkillManager::Instance()->CreateSkill(SkillType::SKILL_USECOFFIN, this);

	m_PlayerSkill_Jump = SkillManager::Instance()->CreateSkill(SkillType::SKILL_USECOFFIN, this);

	m_PlayerSkill_Fall = SkillManager::Instance()->CreateSkill(SkillType::SKILL_POWERUPTURBO, this);

	m_matchManTextureName = "Mummy";


	int frameanim[8] = { 6, 4, 4, 1, 4, 8, 4, 1 };
	m_ActionsFrameCount.clear();
	for (int i=0; i<8; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}

	CoffinHP = 0;

	m_bUseCoffin = false;
}


Player_Mummy::~Player_Mummy(void)
{
}

void Player_Mummy::checkCoffinHP()
{
	CoffinHP--;
	if (CoffinHP <= 0)
	{
		m_bUseCoffin = false;

		//±³×Å¹×²ÄµÄ¶¯»­»»³ÉÂãÌåµÄ
		if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
		{
			playRunAnimation();
		}
		else if (   m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() ||
			m_FSM->GetCurPlayerStatus() == Player_JumpDown::Instance()  )
		{
			playJumpAnimation();
		}
		else if (m_FSM->GetCurPlayerStatus() == Player_Rush::Instance())
		{
			m_FSM->SetPlayerStatus(Player_Run::Instance());
		}
		//²¥·Å¹×²ÄÆÆËéµÄÉùÒô
		//if (ResDef.g_ConfigStruct.EnableAudio != 0)
		//{
		//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_BrokenSound);
		//}
		SoundManager::Instance()->PlayEffect(ResDef::g_BrokenSound);
		//
		ParticleEffect* effect = EffectManager::Instance()->AddParticle(ResDef::g_ParticleEffectExplode, cocos2d::Vec2(10, 20), 1, this);
		if (effect != nullptr)
		{
			effect->setBlendAdditive(false);

			cocos2d::Scene* pRunningScene = cocos2d::Director::getInstance()->getRunningScene();
			if (pRunningScene != nullptr)
			{
				Node* pLayer = pRunningScene->getChildByTag(GameScene::LayerTag);
				GameScene* pGameLayer = (GameScene*)pLayer;
				if (pGameLayer != nullptr)
				{
					pGameLayer->addChild(effect, 100);
				}
			}
		}
	}
	else
	{
		//²¥·Å¹×²Ä×èµ²ÏÝÚå£¬·ÉÐÐµÀ¾ßµÄÉùÒô
		//if (ResDef.g_ConfigStruct.EnableAudio != 0)
		//{
		//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_InvalidSound);
		//}
		SoundManager::Instance()->PlayEffect(ResDef::g_InvalidSound);
	}
}

void Player_Mummy::useCoffin()
{
	CoffinHP = 3;

	m_bUseCoffin = true;
	//

	ParticleEffect* effect = EffectManager::Instance()->AddParticle(ResDef::g_ParticleEffect, cocos2d::Vec2(15, 20), 2, this);
	auto node = GameScene::GetNode();
	if (effect != nullptr && node != nullptr)
	{
		effect->setBlendAdditive(false);

		cocos2d::ccColor4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
		effect->setStartColor(startColor);

		cocos2d::ccColor4F startColorVar(0.0f, 0.0f, 0.0f, 1.0f);
		effect->setStartColorVar(startColorVar);

		cocos2d::ccColor4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
		effect->setEndColor(endColor);

		cocos2d::ccColor4F endColorVar(0.0f, 0.0f, 0.0f, 0.2f);
		effect->setEndColorVar(endColorVar);

		node->addChild(effect, 100);
		
		effect->resetSystem();
	}
}

void Player_Mummy::removeCoffin()
{
	m_bUseCoffin = false;

	//±³×Å¹×²ÄµÄ¶¯»­»»³ÉÂãÌåµÄ
	if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
	{
		playRunAnimation();
	}
	else if (m_FSM->GetCurPlayerStatus() == Player_Jump::Instance() ||
		m_FSM->GetCurPlayerStatus() == Player_JumpDown::Instance())
	{
		playJumpAnimation();
	}
}

void Player_Mummy::useSkill()
{
	if (m_bUseCoffin == false)
	{
		if (m_FSM->GetCurPlayerStatus() == Player_Run::Instance())
		{
			if (m_PlayerSkill_Run != NULL)
			{
				int consume = m_PlayerSkill_Run->getConsume();
				if (consume <= m_CurPower)
				{
					m_PlayerSkill_Run->useSkill();
					int beforeusePower = m_CurPower;
					m_CurPower -= consume;

//					GameScene* gamescene = GameScene::GetNode();
// 					FirstUI MyUI = FirstUI.node(CircleRunScene.GetPlayerNum());
// 					if (gamescene != nullptr && MyUI != nullptr)
// 					{
// 						if (m_PlayerID == 1)
// 						{
// 							if (beforeusePower == m_MaxPower)
// 							{
// 								MyUI.OnProgressA(m_PowerUpTime);
// 							}
// 							MyUI.setPlayerA_Power(m_CurPower);
// 						}
// 						else if (m_PlayerID == 2)
// 						{
// 							if (beforeusePower == m_MaxPower)
// 							{
// 								MyUI.OnProgressB(m_PowerUpTime);
// 							}
// 							MyUI.setPlayerB_Power(m_CurPower);
// 						}

						//if (ResDef.g_ConfigStruct.EnableAudio != 0)
						//{
						//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_CounterSound);
						//}
						//MusicManager.Instance().PlayEffect(ResDef.g_CounterSound);

						m_bUseCoffin = true;

						useCoffin();

						playRunAnimation();                          
					}
				}
			}
				
		return;

		}

	Player::useSkill();
}
