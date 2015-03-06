#include "SkillBoard.h"
#include "Player/PlayerStatus.h"
#include "Player/Player.h"

#include "Scene/GameScene.h"
#include "Trap/TrapBase.h"
#include "Scene/Track.h"


SkillBoard::SkillBoard(Player* pPlayer) :
	SkillBase(pPlayer)
{
	m_SkillConsume = 1;
}

void SkillBoard::useSkill()
{
	//if (CircleRunScene.m_Track != null && m_pPlayer != null)
	//{
	//	CircleRunScene.m_Track.CreateTrap(m_pPlayer.rotation, (uint)TrapType.TRAP_BOARD);
	//}
	cocos2d::Scene* pRunningScene = cocos2d::Director::getInstance()->getRunningScene();
	if (pRunningScene != nullptr)
	{
		cocos2d::Node* pLayer = pRunningScene->getChildByTag(GameScene::LayerTag);
		GameScene* pGameLayer = (GameScene*)pLayer;
		if (pGameLayer != nullptr)
		{
			pGameLayer->m_Track->CreateTrap(m_pPlayer->getRotation(), TrapType::TRAP_BOARD);
		}
	}
}