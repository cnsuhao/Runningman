#ifndef __HELP_UI_H__
#define __HELP_UI_H__

#include "cocos2d.h"
#include "Classes\BaseUI\ProgressBar.h"
#include <thread>

NS_CC_BEGIN

class HelpUI : public cocos2d::Layer
{
public:
	HelpUI(void);
	~HelpUI(void);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();  

	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;


	void callback_NextPage(Ref* sender);
	void callback_OnSkip(Ref* sender);

	CREATE_FUNC(HelpUI);

protected:
	Vector<Sprite*> m_HelpPics;
	static const int HelpPicsNum;
	//
	int currentHelpPage;
	MenuItemSprite* pNextItem;
	MenuItemSprite* pSkipItem;
	Menu* next_menu;
	Menu* skip_menu;
};

NS_CC_END

#endif //__HELP_UI_H__