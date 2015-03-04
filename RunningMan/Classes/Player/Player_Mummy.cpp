#include "Player_Mummy.h"
#include "Skill/SkillManager.h"

#include "Player/PlayerStatus.h"
#include "Sound/SoundManager.h"
#include "Scene/GameScene.h"

#include "Effect/EffectManager.h"

#include "ResDef.h"

Player_Mummy::Player_Mummy(int id) :
		Player(id)
{
	m_RoleType = "Role_Protagonist";
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