#include "StoryEndUI.h"
#include "Scene/GameScene.h"
#include "UI/LogoUI.h"

#include "Manager/GameStatusManager.h"

USING_NS_CC;

Scene* StoryEndUI::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StoryEndUI::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool StoryEndUI::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	winSize = Director::getInstance()->getVisibleSize();
	BG = Sprite::create("images\\StoryEndUI");
	BG->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(BG, 0);

    //    
    return true;
}

void StoryEndUI::onEnter()
{
	GameStatusManager::Instance()->SetStatus(GameStatus::GAMESTATUS_STORYEND);
	//
	Sprite* spr_Next_normal = Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
	Sprite* spr_Next_hover = Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");


	MenuItemSprite* button_Next = MenuItemSprite::create(
		spr_Next_normal,
		spr_Next_hover,
		this,
		CC_CALLBACK_1(StoryEndUI::callback_BackToLogoUI,this));
	pMenu = Menu::createWithItem(button_Next);
	pMenu->setPosition(Vec2(726, winSize.height - 405));
	this->addChild(pMenu, 1);
	//
	Sprite* spNext = Sprite::create("images\\next_text");
	spNext->setPosition(Vec2(726, winSize.height - 405));
	//
	this->addChild(spNext, 5);

	Layer::onEnter();
	
}
//
void StoryEndUI::onExit()
{
	Layer::onExit();
}

void StoryEndUI::callback_BackToLogoUI(Ref* sender)
{
	Director::sharedDirector()->replaceScene(LogoUI::createScene());
	GameStatusManager::Instance()->SetStatus(GameStatus::GAMESTATUS_TITLE);
}