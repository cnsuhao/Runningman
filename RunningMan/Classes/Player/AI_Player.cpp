#include "AI_Player.h"

#include "ResDef.h"
#include "Scene/GameScene.h"
#include "Scene/Track.h"

#include "Player/PlayerStatus.h"
#include "Player/PlayerManager.h"
#include "Level/LevelManager.h"


AI_Player::AI_Player(Player* pPlayerA,Player* pPlayerB, Track* pTrack)
{
	body = pPlayerA;
	enemy = pPlayerB;
	road = pTrack;
}


AI_Player::~AI_Player(void)
{
}

void AI_Player::update(float dt)
{
	if (Enabled == false) return;
	//
	int tempinttype = (int)(body->getUserData());
	GameRoleType BodyType =  (GameRoleType)tempinttype;
	bool HasCoffin = false;
	if (BodyType == GameRoleType::GameRoleType_MUMMY)
	{
		HasCoffin = ((Player_Mummy*)body)->m_bUseCoffin;
	}
	//
	timeCounter+=dt;
	//首先，是特殊状态的处理                     
	if (body->m_FSM->GetCurPlayerStatus() == Player_Fall::Instance() ||
		body->m_FSM->GetCurPlayerStatus() == Player_Electric::Instance())
	{
		if (body->GetPower() >= 3)
		{
			//无论什么样子的电脑 都得去尝试触发技能！          
			if (GameRoleType::GameRoleType_PHARAOH == BodyType)
			{
				body->useSkill();
			}
			return;
		}

	}
	//
	float AtotalAngle = body->getTotalRunAngle();
	float BtotalAngle = enemy->getTotalRunAngle();
	float offsetAngle = AtotalAngle - BtotalAngle;
	//int value = AnalyseValue(timeCounter, body.GetPower(), offsetAngle);
	//首先判断前方道路
	//这个不区分，AI代理的Player类别
	int dist = (int)(CCRANDOM_0_1() * 10) + 2;

	int jumpRate = 2;

	LevelRule currule = LevelRule::RULE_CAREFULLY_TRAP;

	if (GameScene::g_GameMode == RunGameMode::MODE_PVC ||
		GameScene::g_GameMode == RunGameMode::MODE_PVP)
	{
		GameLevel* ldata = LevelManager::Instance()->VsAreaData->GetGameLevel(0);
		if (ldata != nullptr)
		{
			currule = ldata->getRule();
		}
	}
	else if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->GetGameLevel(curlevel);
		if (ldata != nullptr)
		{
			currule = ldata->getRule();
		}
	}

	if (currule == LevelRule::RULE_COLLECT_COIN)
	{
		jumpRate = 40;
	}
	else if (currule == LevelRule::RULE_COLLECT_ALLCOIN)
	{
		jumpRate = 50;
	}

	float angle = body->getRotation() - dist;//前面的距离
	if (angle > 360.0f)
	{
		angle = angle - 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle = angle + 360.0f;
	}

	int rndNum = (int)(CCRANDOM_0_1()*200);
	//projectile
	if (road->checkProjectile(angle) == true)
	{
		if (m_AILevel == 0)
		{
			if (rndNum > 80)
			{
				body->useJump();
			}
		}
		else if (m_AILevel == 1)
		{
			if (rndNum > 50)
			{
				body->useJump();
			}
		}
		else if (m_AILevel == 2)
		{
			if (rndNum > 30)
			{
				body->useJump();
			}
		}
	}
	//trap
	TrapBase* TT = road->getTrap(angle);
	if (TT != nullptr)
	{
		switch (TT->getTrapType())
		{
		case TRAP_BANANA:
			{
				if (m_AILevel == 0)
				{
					if (rndNum > 80)
					{
						body->useJump();
					}
				}
				else if (m_AILevel == 1)
				{
					if (rndNum > 50)
					{
						body->useJump();
					}
				}
				else if (m_AILevel == 2)
				{
					if (rndNum > 30)
					{
						body->useJump();
					}
				}

			}
			break;
		case TRAP_REDCACTUS:
			{
				if (m_AILevel == 0)
				{
					if (rndNum > 80)
					{
						body->useJump();
					}
				}
				else if (m_AILevel == 1)
				{
					if (rndNum > 50)
					{
						body->useJump();
					}
				}
				else if (m_AILevel == 2)
				{
					if (rndNum > 30)
					{
						body->useJump();
					}
				}

			}
			break;
		case TRAP_BOARD:
			{
				jumpRate = 1;
			}
			break;
		case TRAP_STORM:
			{
				jumpRate = 1;
			}
			break;
		}
	}
	else 
	{   //没事儿 也瞎胡跳            
		if (rndNum < jumpRate)
		{
			body->useJump();
		}
	}
	//
	switch(body->GetPower())
	{
	case 0:
		break;
	case 1:
		if (BodyType == GameRoleType::GameRoleType_ARSEHOLE)
		{
			//board
			float bananaAngel = body->getRotation() + dist;//后面的距离
			if (bananaAngel > 360.0f)
			{
				bananaAngel = bananaAngel - 360.0f;
			}
			else if (angle < -360.0f)
			{
				bananaAngel = bananaAngel + 360.0f;
			}
			TrapBase* afterArseHole = road->getTrap(angle);
			int putbanana = 2;
			int putboard = 198;
			if (afterArseHole != nullptr)
			{
				switch (afterArseHole->getTrapType())
				{
				case TRAP_BANANA:
					{
						putbanana = 170;
						break;
					}
				case TRAP_REDCACTUS:
					{
						putbanana = 170;
						break;
					}
				case TRAP_BOARD:
					{
						putbanana = 30;
						break;
					}
				case TRAP_STORM:
					{
						putbanana = 30;
						break;
					}
				}
			}

			if (rndNum < putbanana)
			{
				body->useSkill();
			}
			else if (rndNum > putboard)
			{
				body->useJump();
				body->useSkill();
			}
		}
		else if (BodyType == GameRoleType::GameRoleType_MUMMY)
		{
			if (HasCoffin && road->numActiveTrap() < 10 && currule != LevelRule::RULE_CAREFULLY_TRAP)
			{
				if (rndNum < 2)
				{
					body->useJump();
					body->useSkill();
					break;
				}
			}
		}
		break;
	case 2:
		//特殊处理
		if (BodyType == GameRoleType::GameRoleType_ARSEHOLE)
		{
			//board
			float bananaAngel = body->getRotation() + dist;//后面的距离
			if (bananaAngel > 360.0f)
			{
				bananaAngel = bananaAngel - 360.0f;
			}
			else if (angle < -360.0f)
			{
				bananaAngel = bananaAngel + 360.0f;
			}
			TrapBase* afterArseHole = road->getTrap(angle);
			int putbanana = 1;
			int putboard = 199;
			if (afterArseHole != nullptr)
			{
				switch (afterArseHole->getTrapType())
				{
				case TRAP_BANANA:
					{
						putbanana = 190;
						break;
					}
				case TRAP_REDCACTUS:
					{
						putbanana = 190;
						break;
					}
				case TRAP_BOARD:
					{
						putbanana = 10;
						break;
					}
				case TRAP_STORM:
					{
						putbanana = 10;
						break;
					}
				}
			}

			if (rndNum < putbanana)
			{
				body->useSkill();
			}
			else if (rndNum > putboard)
			{
				body->useJump();
				body->useSkill();
			}
		}
		if (BodyType == GameRoleType::GameRoleType_MUMMY)
		{
			if (HasCoffin == false)
			{
				body->useSkill();
			}
			else
			{
				if (m_AILevel == 0) 
				{   
					if ( rndNum < 5)
					{
						body->useSkill();
					}
					else
						if (rndNum < 10 && currule != LevelRule::RULE_CAREFULLY_TRAP)
						{
							body->useJump();
							body->useSkill();
						}
				}
				else
				{
					if (rndNum < 10)
					{
						body->useSkill();
					}
					else
						if (rndNum < 11 && currule != LevelRule::RULE_CAREFULLY_TRAP)
						{
							body->useJump();
							body->useSkill();
						}
				}
			}

			break;
		}
		if (BodyType == GameRoleType::GameRoleType_MATCHMAN)
		{
			if (currule == LevelRule::RULE_COLLECT_ALLCOIN ||
				currule == LevelRule::RULE_COLLECT_COIN)
			{
				if (rndNum < 100)
				{
					body->useJump();
					body->useSkill();
					break;
				}
			}
			else
			{
				if (m_AILevel == 0)
				{
					if (rndNum > 50)
					{
						body->useSkill();
					}
				}
				else
				{
					if (rndNum > 30)
					{
						body->useSkill();
					}
				}
			}
		}
		//
		if (BodyType == GameRoleType::GameRoleType_PHARAOH)
		{
			if (currule == LevelRule::RULE_COLLECT_ALLCOIN ||
				currule == LevelRule::RULE_COLLECT_COIN)
			{
				if (m_AILevel == 0)
				{
					if (rndNum > 100)
					{
						body->useSkill();
					}
				}
				else
				{
					if (rndNum > 198)
					{
						body->useSkill();
					}
				}
			}
			else
			{
				if (m_AILevel == 0)
				{
					if (rndNum > 150)
					{
						body->useSkill();
					}
				}
				else
				{
					if (rndNum > 100)
					{
						body->useSkill();
					}
				}
			}

		}
		break;
	case 3:
		if (BodyType == GameRoleType::GameRoleType_ARSEHOLE)
		{
			//board
			float bananaAngel = body->getRotation() + dist;//后面的距离
			if (bananaAngel > 360.0f)
			{
				bananaAngel = bananaAngel - 360.0f;
			}
			else if (angle < -360.0f)
			{
				bananaAngel = bananaAngel + 360.0f;
			}
			TrapBase* afterArseHole = road->getTrap(angle);
			int putbanana = 1;
			int putboard = 199;
			if (afterArseHole != nullptr)
			{
				switch (afterArseHole->getTrapType())
				{
				case TRAP_BANANA:
					{
						putbanana = 190;
						break;
					}
				case TRAP_REDCACTUS:
					{
						putbanana = 190;
						break;
					}
				case TRAP_BOARD:
					{
						putbanana = 10;
						break;
					}
				case TRAP_STORM:
					{
						putbanana = 10;
						break;
					}
				}
			}

			if (rndNum < putbanana)
			{
				body->useSkill();
			}
			else if (rndNum > putboard)
			{
				body->useJump();
				body->useSkill();
			}
		}
		if (BodyType == GameRoleType::GameRoleType_MUMMY)
		{
			if (rndNum < 100)
			{
				body->useSkill();
				break;
			}
		}
		if (BodyType == GameRoleType::GameRoleType_PHARAOH)
		{
			if (currule == LevelRule::RULE_COLLECT_ALLCOIN ||
				currule == LevelRule::RULE_COLLECT_COIN)
			{
				if (rndNum < 100)
				{
					body->useJump();
					body->useSkill();
					break;
				}
			}
			else
			{
				if (m_AILevel == 0)
				{
					if (rndNum > 100)
					{
						body->useSkill();
					}
				}
				else
				{
					if (rndNum > 30)
					{
						body->useSkill();
					}
				}
			}

		}
		if (BodyType == GameRoleType::GameRoleType_MATCHMAN)
		{
			if (body->m_FSM->GetCurPlayerStatus() == Player_Fall::Instance())
			{
				body->useSkill();
			}
		}
		break;
	}

}

void AI_Player::restart()
{
	m_AILevel = (int)(CCRANDOM_0_1()*m_AIMaxLevel);
}

void AI_Player::clear()
{
	body = nullptr;
	enemy = nullptr;
	road = nullptr;
}