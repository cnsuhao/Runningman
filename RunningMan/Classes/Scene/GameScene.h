#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player/PlayerManager.h"

class Player;
class Track;
class AI_Player;
class GameLevel;

enum RunGameMode
{
	MODE_STORY = 0,
	MODE_PVP,
	MODE_PVC,
};

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int useSceneID);
	static cocos2d::Node*  GetNode();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void SceneInit();
	//----------------------------------------------------------------
	void SetPlayersType(GameRoleType TypeA, GameRoleType TypeB);

	void SetAIEnable(bool b);

	void InitPlayers();

	void restart();

	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	void QuitGame(Ref* pSender);

	static int LayerTag;

	//static double DegreeToRadians(double fdegree);
	

	int GetPlayerNum();

	void setSceneID(int index)
	{
		m_SceneIndex = index;
	}

	GameLevel* GetCurrentLevelData();

	//----------------------------------------------------------------
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

public:
	Track* m_Track;
    Player* m_PlayerA;
    Player* m_PlayerB;
    GameRoleType PlayerAType;
    GameRoleType PlayerBType;

    static AI_Player* m_AI;
    static bool UseAI;

	static RunGameMode g_GameMode;

	cocos2d::Sprite* m_TrackPic;
	cocos2d::Sprite* m_BG;
	bool ShowLabel;

protected:
    int m_NumProjectiles; 

    bool m_bGameOver;
    std::string m_strWinerIs;

    int m_LevelUpCountdown;
    int m_EveryLevelUpMax;
    int m_GameLevel;
    int m_SceneIndex;
        //
	float cradius;

    //static CircleRunScene* m_instance = null;

	void callbackShowLabel();

	void callbackShowEndStoryUI();

	void menuCloseCallback(Ref* sender);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	void randomCreateCloud();

	void randomCreateRedCactus();

	void randomCreateStorm();

	void randomCreateCoin();

	void createAllCoinEdge();

	void createAllCoin();

    int GetSceneIndex();

	void ShowLabelAnimation();
};

#endif // __GAME_SCENE_H__
