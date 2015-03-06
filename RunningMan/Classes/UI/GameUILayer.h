#ifndef __GAME_UI_H__
#define __GAME_UI_H__

#include "cocos2d.h"

class Player;
class GameScene;

class GameUILayer : public cocos2d::Layer
{
public:

	bool init();

	void setPlayerA_Power(int power);
	void setPlayerB_Power(int power);
	void OnProgressA(float duringTime);
	void OnProgressB(float duringTime);

	void update(float dt);

	void callback_OnPressReplay(Ref* sender);
	void callback_OnPressGoOn(Ref* sender);

	void PlayLabelFrame();
	void callback_EndPlayedLabelFrame();

	void callback_ProgressFinish_A(Ref* sender);
	void callback_ProgressFinish_B(Ref* sender);

	void callback_OnPressJumpA(Ref* sender);
	void callback_OnPressActionA(Ref* sender);
	void callback_OnPressJumpB(Ref* sender);
	void callback_OnPressActionB(Ref* sender);

	void SetPlayerA(Player* pPlayer);
	Player* GetPlayerA();
	void SetPlayerB(Player* pPlayer);
	Player* GetPlayerB();

	void restart();

	void onEnter();

	void onExit();

	CREATE_FUNC(GameUILayer);

	static int LayerTag;

private:
	void initPlayerAUI();
	void initPlayerBUI();

	void StopProgress_A();
	void StopProgress_B();
	Player* m_PlayerA;
	Player* m_PlayerB;

	int m_numPlayer;
	static const int PowerNumIconsMax;

	GameScene* m_pGameScene;
public:
	static const float DefaultLevelTime;

	//Countdown TimeCounter;
	cocos2d::Size winSize;

	//cocos2d::Sprite* ResetGame_label;
	//cocos2d::Sprite* BackFactory_label;

	//cocos2d::Sprite* ExitGame_lable;
	//cocos2d::MenuItemSprite* quitGameBtn;
	//cocos2d::MenuItemSprite* quitGameCancleBtn;

	float LevelTime;
	//
	cocos2d::Sprite* PowerBarA;
	cocos2d::Sprite* PowerBarB;
	//
	cocos2d::Vector<cocos2d::Sprite*> PowerNumIconsA;
	cocos2d::Vector<cocos2d::Sprite*> PowerNumIconsB;
	//
	cocos2d::ProgressTimer* ProgressMaskA;
	cocos2d::ProgressTimer* ProgressMaskB;
	//
	
	cocos2d::Label* pGameLabelScoreA;
	cocos2d::Label* pGameLabelScoreB;
	cocos2d::Label* pGameLabel;
	//
	cocos2d::Sprite* GameOver_label;
	cocos2d::MenuItemSprite*  replayBtn;
	cocos2d::MenuItemSprite*  gotoSceneMapBtn;
	//
	bool IsShowEndLabel;
	//
	cocos2d::MenuItemSprite* jumpBtn;
	cocos2d::MenuItemSprite* actionBtn;
	cocos2d::MenuItemSprite* jumpBtn2;
	cocos2d::MenuItemSprite* actionBtn2;
	cocos2d::Menu* jump_menu;
	cocos2d::Menu* action_menu;
	cocos2d::Menu* jump_menu2;
	cocos2d::Menu* action_menu2;
	//
	cocos2d::Sprite* jump_text;
	cocos2d::Sprite* action_text;
	cocos2d::Sprite* jump_text2;
	cocos2d::Sprite* action_text2;
};

#endif //__GAME_UI_H__