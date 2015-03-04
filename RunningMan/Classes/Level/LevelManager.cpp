#include "LevelManager.h"

#include "Player/Player.h"

const int LevelManager::SceneNum = 1;

LevelManager* LevelManager::m_Instance = nullptr;

LevelManager* LevelManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new LevelManager();
	}

	return m_Instance;
}

LevelManager::LevelManager(void)
{
}


LevelManager::~LevelManager(void)
{
}

void LevelManager::FillInfo()
{
	Area*   Scene_1 = new Area();
	{
		cocos2d::Vec2 pos;
		Scene_1->LevelNum = 6;
		//Scene_1.LevelDatas = new List<LevelData>(Scene_1.LevelNum);
		//
		GameLevel* data;
		pos = cocos2d::Vec2(564,480 - 287);
		data = new GameLevel();
		data->levelPoint = pos;
		data->Init(LevelRule::RULE_CATCH_RIVALS, 0, 0, false, GameRoleType::GameRoleType_MUMMY, 1);
		Scene_1->m_GameLevels.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(493,480 - 272);
		//-------------------------------
		data = new GameLevel();
		data->levelPoint = pos;
		data->Init(LevelRule::RULE_OVER_LAPS, 2, 0, false, GameRoleType::GameRoleType_MUMMY, 1);
		Scene_1->m_GameLevels.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(455,480 - 195);
		//-------------------------------
		data = new GameLevel();		
		data->levelPoint = pos;
		data->Init(LevelRule::RULE_CAREFULLY_TRAP, 0, 0, true, GameRoleType::GameRoleType_MUMMY, 1);
		Scene_1->m_GameLevels.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(475,480 - 138);
		data = new GameLevel();
		data->levelPoint = pos;
		data->Init(LevelRule::RULE_CATCH_RIVALS, 0, 0, false, GameRoleType::GameRoleType_PHARAOH, 2);
		Scene_1->m_GameLevels.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(492, 480 - 145);
		data = new GameLevel();
		data->levelPoint = pos;
		data->Init(LevelRule::RULE_COLLECT_ALLCOIN, 0, 0, false, GameRoleType::GameRoleType_PHARAOH, 2);
		Scene_1->m_GameLevels.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(492, 480 - 125);
		data = new GameLevel();
		data->levelPoint = pos;
		data->Init(LevelRule::RULE_COLLECT_COIN, 0, 0, true, GameRoleType::GameRoleType_PHARAOH, 2);
		Scene_1->m_GameLevels.push_back(data);
		//
	}
	//
	this->m_Areas.push_back(Scene_1);

	//-------------------------------------------------
	//vs
	VsAreaData = new Area(); 
	cocos2d::Vec2 vspos;
	VsAreaData->LevelNum = 1;
	GameLevel* vsdata;
	vspos = cocos2d::Vec2(564, 480 - 287);
	vsdata = new GameLevel();
	vsdata->levelPoint = vspos;
	vsdata->Init(LevelRule::RULE_COLLECT_COIN, 1, 0, false, GameRoleType::GameRoleType_ARSEHOLE, 1);
	VsAreaData->m_GameLevels.push_back(vsdata);
}
