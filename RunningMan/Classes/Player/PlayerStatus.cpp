#include "PlayerStatus.h"
#include "Player\Player.h"

Player_Run* Player_Run::m_instance = nullptr;
Player_Run* Player_Run::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Run();
	}
	return m_instance;
}

void Player_Run::Enter(Player* pplayer)
{
	pplayer->jumpOver();
	pplayer->startRun();
}

void Player_Run::Execute(Player* pplayer, float dt)
{
}

void Player_Run::Exit(Player* pplayer)
{
	;
}
//------------------------------------------------
Player_Jump* Player_Jump::m_instance = nullptr;
Player_Jump* Player_Jump::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Jump();
	}
	return m_instance;
}

void Player_Jump::Enter(Player* pplayer)
{
	pplayer->jump();
}

void Player_Jump::Execute(Player* pplayer, float dt)
{
	pplayer->jumpUpStep();
	if (pplayer->isCurJumpHeightOverMax())
	{
		pplayer->m_FSM->SetPlayerStatus(Player_JumpDown::Instance());
	}
}

void Player_Jump::Exit(Player* pplayer)
{
	;
}
//------------------------------------------------
Player_JumpDown* Player_JumpDown::m_instance = nullptr;
Player_JumpDown* Player_JumpDown::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_JumpDown();
	}
	return m_instance;
}

void Player_JumpDown::Enter(Player* pplayer)
{
}

void Player_JumpDown::Execute(Player* pplayer, float dt)
{
	pplayer->jumpDownStep();
	if (pplayer->isCurJumpHeightOverZero())
	{
		pplayer->m_FSM->SetPlayerStatus(Player_Run::Instance());
	}
}

void Player_JumpDown::Exit(Player* pplayer)
{
	pplayer->jumpOver();
}
//------------------------------------------------
Player_Fall* Player_Fall::m_instance = nullptr;
Player_Fall* Player_Fall::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Fall();
	}
	return m_instance;
}

void Player_Fall::Enter(Player* pplayer)
{
	pplayer->stopRun();
	pplayer->playFallAnimation();

	pplayer->jumpOver();
}

void Player_Fall::Execute(Player* pplayer, float dt)
{
}

void Player_Fall::Exit(Player* pplayer)
{
}
//------------------------------------------------
Player_Retreat* Player_Retreat::m_instance = nullptr;
Player_Retreat* Player_Retreat::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Retreat();
	}
	return m_instance;
}

void Player_Retreat::Enter(Player* pplayer)
{
	pplayer->startRetreatRun();

	pplayer->jumpOver();
}

void Player_Retreat::Execute(Player* pplayer, float dt)
{
	pplayer->retreatStep();
	if (pplayer->isRetreatOver())
	{
		pplayer->m_FSM->SetPlayerStatus(Player_Run::Instance());
	}
}

void Player_Retreat::Exit(Player* pplayer)
{
}
//------------------------------------------------
Player_Electric* Player_Electric::m_instance = nullptr;
Player_Electric* Player_Electric::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Electric();
	}
	return m_instance;
}

void Player_Electric::Enter(Player* pplayer)
{
	//1 Í£Ö¹ÒÆ¶¯
	pplayer->stopRun();
	//2 ²¥·ÅË¤µ¹¶¯»­
	pplayer->playElectricAnimation();

	pplayer->jumpOver();
}

void Player_Electric::Execute(Player* pplayer, float dt)
{
}

void Player_Electric::Exit(Player* pplayer)
{
}
//------------------------------------------------
Player_SpeedMax* Player_SpeedMax::m_instance = nullptr;
Player_SpeedMax* Player_SpeedMax::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_SpeedMax();
	}
	return m_instance;
}

void Player_SpeedMax::Enter(Player* pplayer)
{
	pplayer->speedUpRun();
}

void Player_SpeedMax::Execute(Player* pplayer, float dt)
{
	pplayer->speedUpStep();
	if (pplayer->getSpeedUpCurTime() <=0 )
	{
		pplayer->m_FSM->SetPlayerStatus(Player_Run::Instance());
	}
}

void Player_SpeedMax::Exit(Player* pplayer)
{
}
//------------------------------------------------
Player_Anger* Player_Anger::m_instance = nullptr;
Player_Anger* Player_Anger::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Anger();
	}
	return m_instance;
}

void Player_Anger::Enter(Player* pplayer)
{
	pplayer->angerRun();
}

void Player_Anger::Execute(Player* pplayer, float dt)
{
	pplayer->angerStep();
	if (pplayer->getAngerCurTime() <= 0)
	{
		pplayer->m_FSM->SetPlayerStatus(Player_Run::Instance());
	}
}

void Player_Anger::Exit(Player* pplayer)
{
	pplayer->angerOver();
}
//------------------------------------------------
Player_Rush* Player_Rush::m_instance = nullptr;
Player_Rush* Player_Rush::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Rush();
	}
	return m_instance;
}

void Player_Rush::Enter(Player* pplayer)
{
	pplayer->rushRun();
}

void Player_Rush::Execute(Player* pplayer, float dt)
{
	pplayer->rushStep();
	if (pplayer->getRushCurTime() <= 0)
	{
		pplayer->m_FSM->SetPlayerStatus(Player_Run::Instance());
	}
}

void Player_Rush::Exit(Player* pplayer)
{
	pplayer->rushOver();
}
//------------------------------------------------
Player_Win* Player_Win::m_instance = nullptr;
Player_Win* Player_Win::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Win();
	}
	return m_instance;
}

void Player_Win::Enter(Player* pplayer)
{
	pplayer->jumpOver();
	pplayer->winGame();
}

void Player_Win::Execute(Player* pplayer, float dt)
{
}

void Player_Win::Exit(Player* pplayer)
{	
}
//------------------------------------------------
Player_Lose* Player_Lose::m_instance = nullptr;
Player_Lose* Player_Lose::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Lose();
	}
	return m_instance;
}

void Player_Lose::Enter(Player* pplayer)
{
	pplayer->jumpOver();
	pplayer->loseGame();
}

void Player_Lose::Execute(Player* pplayer, float dt)
{
}

void Player_Lose::Exit(Player* pplayer)
{
}
//------------------------------------------------
Player_Stop* Player_Stop::m_instance = nullptr;
Player_Stop* Player_Stop::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Stop();
	}
	return m_instance;
}

void Player_Stop::Enter(Player* pplayer)
{
	pplayer->stopRun();
}

void Player_Stop::Execute(Player* pplayer, float dt)
{
}

void Player_Stop::Exit(Player* pplayer)
{
}
//------------------------------------------------
Player_Fly* Player_Fly::m_instance = nullptr;
Player_Fly* Player_Fly::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Player_Fly();
	}
	return m_instance;
}

void Player_Fly::Enter(Player* pplayer)
{
	pplayer->flyStart();
}

void Player_Fly::Execute(Player* pplayer, float dt)
{
	pplayer->flyStep();
	if (pplayer->getFlyCurTime() <= 0)
	{
		pplayer->m_FSM->SetPlayerStatus(Player_JumpDown::Instance());
	}
}

void Player_Fly::Exit(Player* pplayer)
{
	pplayer->flyOver();
}
//------------------------------------------------
