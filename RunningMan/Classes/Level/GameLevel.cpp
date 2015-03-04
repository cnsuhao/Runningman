#include "GameLevel.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Scene/GameScene.h"
#include "Player/PlayerStatus.h"
#include "Scene/Track.h"

GameLevel::GameLevel(void)
{
}


GameLevel::~GameLevel(void)
{
}

void GameLevel::Init(LevelRule rule, int overLaps, int collectNum, bool isboss, int roleType, int sceneTexID)
{
	m_CurRule = rule;
	m_LevelRuleData.SetOverLaps(overLaps);
	m_LevelRuleData.SetCollectNum(collectNum);
	m_bCreateCoin = false;
	m_bRandomCoin = false;
	m_ReadyCreateCoinNum = 0;
	m_MapTexID = 1;
	m_LimitTime = 0.0f;
	m_EnemyRoleType = roleType;
	m_bIsBoss = isboss;

	m_MapTexID = sceneTexID;

	switch(m_CurRule)
	{
	case LevelRule::RULE_COLLECT_ALLCOIN:
		{
			m_bCreateCoin = true;
			m_ReadyCreateCoinNum = 100;

		}
		break;
	case LevelRule::RULE_COLLECT_COIN:
		{
			m_bCreateCoin = true;
			m_bRandomCoin = true;
			m_ReadyCreateCoinNum = 10;
			m_LimitTime = 60.0f;

		}
		break;
	}
}

bool GameLevel::IsMatchOver()
{
	Player* pPlayA = PlayerManager::Instance()->GetPlayerA();
	Player* pPlayB = PlayerManager::Instance()->GetPlayerB();

	switch (m_CurRule)
	{
	case LevelRule::RULE_CATCH_RIVALS:
		{
			float AtotalAngle = pPlayA->getTotalRunAngle();
			float BtotalAngle = pPlayB->getTotalRunAngle();
			if ((AtotalAngle - BtotalAngle) > 180.0f)
			{
				//A追上了B
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((BtotalAngle - AtotalAngle) > 180.0f)
			{
				//B追上了A
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
		}
		break;
	case LevelRule::RULE_OVER_LAPS:
		{
			float lap = (float)m_LevelRuleData.GetOverLaps();
			float AtotalAngle = pPlayA->getTotalRunAngle();
			float BtotalAngle = pPlayB->getTotalRunAngle();

			if ((AtotalAngle - BtotalAngle) > 180.0f + 360.0f * lap)
			{
				//A追上了B
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((BtotalAngle - AtotalAngle) > 180.0f + 360.0f * lap)
			{
				//B追上了A
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
		}
		break;
	case LevelRule::RULE_CAREFULLY_TRAP:
		{
			float AtotalAngle = pPlayA->getTotalRunAngle();
			float BtotalAngle = pPlayB->getTotalRunAngle();

			if (pPlayA->m_FSM->GetCurPlayerStatus() == Player_Fall::Instance() ||
				pPlayA->m_FSM->GetCurPlayerStatus() == Player_Electric::Instance() )
			{
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
			else if (pPlayB->m_FSM->GetCurPlayerStatus() == Player_Fall::Instance() ||
				pPlayB->m_FSM->GetCurPlayerStatus() == Player_Electric::Instance())
			{
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((AtotalAngle - BtotalAngle) > 180.0f)
			{
				//A追上了B
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((BtotalAngle - AtotalAngle) > 180.0f)
			{
				//B追上了A
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
		}
		break;
	case LevelRule::RULE_COLLECT_COIN:
		{
			if (m_LimitTime <= 0.0f)
			{
				if (pPlayA->GetCollectCoin() > pPlayB->GetCollectCoin())
				{
					pPlayA->win();
					pPlayB->lose();
					return true;
				}
				else if (pPlayB->GetCollectCoin() > pPlayA->GetCollectCoin())
				{
					pPlayA->lose();
					pPlayB->win();
					return true;
				}
				else
				{
					pPlayA->lose();
					pPlayB->lose();
					return true;
				}
			}                        
		}
		break;
	case LevelRule::RULE_COLLECT_ALLCOIN:
		{
			cocos2d::Scene* pRunningScene = cocos2d::Director::getInstance()->getRunningScene();
			if (pRunningScene != nullptr)
			{
				cocos2d::Node* pLayer = pRunningScene->getChildByTag(GameScene::LayerTag);
				GameScene* pGameLayer = (GameScene*)pLayer;
				if (pGameLayer != nullptr)
				{
					if (pGameLayer->m_Track->getAppearCoin() == 0)
					{
						if (pPlayA->GetCollectCoin() > pPlayB->GetCollectCoin())
						{
							pPlayA->win();
							pPlayB->lose();
							return true;
						}
						else if (pPlayB->GetCollectCoin() > pPlayA->GetCollectCoin())
						{
							pPlayA->lose();
							pPlayB->win();
							return true;
						}
						else
						{
							pPlayA->lose();
							pPlayB->lose();
							return true;
						}
					}
				}
			}
		}
		break;
	}
	return false;
}