#ifndef __STORY_END_UI_H__
#define __STORY_END_UI_H__

#include "cocos2d.h"
#include "Classes\BaseUI\ProgressBar.h"

NS_CC_BEGIN

class StoryEndUI : public cocos2d::Layer
{
private:		
	Sprite* BG;
	Size winSize;
	Menu* pMenu;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  

	//virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(StoryEndUI);

private:
	void callback_BackToLogoUI(Ref* sender);
};

NS_CC_END

#endif //__STORY_END_UI_H__

