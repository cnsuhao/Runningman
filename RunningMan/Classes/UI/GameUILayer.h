#ifndef __GAME_UI_H__
#define __GAME_UI_H__

#include "cocos2d.h"

class GameUILayer : public cocos2d::Layer
{
public:

	bool init();

	void setPlayerA_Power(int power);
	void setPlayerB_Power(int power);
	void OnProgressA(float duringTime);
	void OnProgressB(float duringTime);

	void update(float dt);

	void callback_OnPressReplay();
	void callback_OnPressGoOn();

	void PlayLabelFrame();
	void callback_EndPlayedLabelFrame();

	void callback_ProgressFinish_A();
	void callback_ProgressFinish_B();

	void callback_OnPressJumpA();
	void callback_OnPressActionA();
	void callback_OnPressJumpB();
	void callback_OnPressActionB();

	void restart();

	void onEnter();

	void onExit();

	CREATE_FUNC(GameUILayer);

	static int LayerTag;
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