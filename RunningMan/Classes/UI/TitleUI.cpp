#include "TitleUI.h"
#include "ResDef.h"
#include "Sound/SoundManager.h"
#include "Scene/GameScene.h"

USING_NS_CC;

int TitleUI::LayerTag = 10;

Scene* TitleUI::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleUI::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool TitleUI::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	this->setTag(LayerTag);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	pLogo = Sprite::create("images/logo.png");
	pLogo->setPosition(Vec2(405, visibleSize.height - 111));
	addChild(pLogo,1);
	pLogo_BG = Sprite::create("images/logo_bg.jpg");
    pLogo_BG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(pLogo_BG, 0);

	//Button StartGame
	{
		//new game btn
		{
			//SpriteFrame* normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("story_normal.png");
			//SpriteFrame* select = SpriteFrameCache::getInstance()->getSpriteFrameByName("story_hover.png");
			
			Sprite* normal = Sprite::create("images//story_normal.png");
			Sprite* select = Sprite::create("images//story_hover.png");

			//Story_Btn = MenuItemSprite::create(Sprite::createWithSpriteFrame(normal), Sprite::createWithSpriteFrame(select), CC_CALLBACK_1(TitleUI::StartStory_Game,this));
			Story_Btn = MenuItemSprite::create(normal, select, CC_CALLBACK_1(TitleUI::StartStory_Game,this));
			Story_Btn->setPosition(0.0f, 50.0f);	
		}
		//quit btn
		{
			SpriteFrame* normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_normal.png");
			SpriteFrame* select = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_hover.png");
			;
			PVP_Btn = MenuItemSprite::create(Sprite::createWithSpriteFrame(normal), Sprite::createWithSpriteFrame(select), CC_CALLBACK_1(TitleUI::StartPVP_Game,this));
			PVP_Btn->setPosition(0.0f, 0.0f);	
		}
		//quit btn
		{
			SpriteFrame* normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvc_normal.png");
			SpriteFrame* select = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvc_hover.png");
			;
			PVC_Btn = MenuItemSprite::create(Sprite::createWithSpriteFrame(normal), Sprite::createWithSpriteFrame(select), CC_CALLBACK_1(TitleUI::StartPVC_Game,this));
			PVC_Btn->setPosition(0.0f, -50.0f);	
		}


		m_pStartMenu = Menu::create(Story_Btn,PVP_Btn,PVC_Btn, nullptr);

		m_pStartMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 50));
		m_pStartMenu->setVisible(true);
		addChild(m_pStartMenu, 2);
	}

	
	{
		//Button LeaveGame or not
		QuitGame_label = Sprite::create("Images//QuitGame_label.png");
		QuitGame_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		QuitGame_label->setScale(0.01f);
		QuitGame_label->setVisible(false);
		//QuitGame_label->setUserData(0);
		addChild(QuitGame_label, 109);

		quitGameBtn = MenuItemImage::create("Images//QuitYes.png","Images//QuitYes_hover.png",CC_CALLBACK_1(TitleUI::callback_OnPressQuitGame, this));
		auto pmenu = Menu::create(quitGameBtn, NULL);
        pmenu->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 40));
        addChild(pmenu, 110);

		quitGameCancleBtn = MenuItemImage::create("Images//QuitCancel","Images//QuitCancel_hover",CC_CALLBACK_1(TitleUI::callback_OnPressCancleQuit, this));
		auto pmenu2 = Menu::create(quitGameCancleBtn,NULL);
        pmenu2->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 40));
        addChild(pmenu2, 110);

		rateMeToUnlockBtn = MenuItemImage::create("Images//RateUnlock","Images//RateUnlock_hover",CC_CALLBACK_1(TitleUI::callback_OnPressRateMeToUnlock, this));
		auto pmenu3 = Menu::create(rateMeToUnlockBtn,NULL);
        pmenu3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));
        addChild(pmenu3, 110);
        //
		quitGameBtn->setVisible(false);
		quitGameBtn->setEnabled(false);
        quitGameCancleBtn->setVisible(false);
        quitGameCancleBtn->setEnabled(false);
        rateMeToUnlockBtn->setVisible(false);
        rateMeToUnlockBtn->setEnabled(false);
    }

	//
    pLogoProgressBar = new ProgressBar(100, 0, "images\\LesStep.png");
    addChild(pLogoProgressBar, 1);
	pLogoProgressBar->setPosition(Vec2((visibleSize.width - pLogoProgressBar->width) / 2,
                                                visibleSize.height  - 200));

    pLogoProgressBar->setVisible(true);

    //
	this->setTouchEnabled(true);
    //    
    return true;
}

void TitleUI::callback_OnPressQuitGame(Ref* sender)
{
	ResDef::getInstance()->SaveConfig();
	CCDirector::getInstance()->end();
	//CCApplication::sharedApplication()->getInstance()->Game.Exit();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TitleUI::callback_OnPressCancleQuit(Ref* sender)
{
    CloseQuitGameLayer();
}

void TitleUI::callback_OnPressRateMeToUnlock(Ref* sender)
{
    //rateMeToUnlockBtn.visible = false;
    //rateMeToUnlockBtn.Enabled = false;

    //MarketplaceReviewTask marketplaceReviewTask = new MarketplaceReviewTask();
    //marketplaceReviewTask.Show();

    //if (ResDef.IsRoleLocked((int)GamePlayerRole.GamePlayerRole_MATCHMAN) == true)
    //{
    //    ResDef.UnlockRoleID((int)GamePlayerRole.GamePlayerRole_MATCHMAN);
    //    ResDef.SaveConfig();
    //}
}

void TitleUI::CloseQuitGameLayer()
{
	QuitGame_label->stopAllActions();
	QuitGame_label->setScale(0.01f);
	QuitGame_label->setVisible(false);
	QuitGame_label->setUserData(0);

    quitGameBtn->setVisible(false);
	quitGameBtn->setEnabled(false);

    quitGameCancleBtn->setVisible(false);
    quitGameCancleBtn->setEnabled(false);

    rateMeToUnlockBtn->setVisible(false);
    rateMeToUnlockBtn->setEnabled(false);

    if (PVP_Btn != NULL)
    {
        PVP_Btn->setEnabled(true);
    }
    if (PVC_Btn != NULL)
    {
        PVC_Btn->setEnabled(true);
    }
    if (Story_Btn != NULL)
    {
        Story_Btn->setEnabled(true);
    }

    if (help_Btn != NULL)
    {
        help_Btn->setEnabled(true);
    }
    if (rateme_Btn != NULL)
    {
        rateme_Btn->setEnabled(true);
    }
    if (developer_Btn != NULL)
    {
        developer_Btn->setEnabled(true);
    }
    if (monster_Btn != NULL)
    {
        monster_Btn->setEnabled(true);
    }
}

void TitleUI::QuitGame()
{
    QuitGame_label->setScale(0.01f);
    QuitGame_label->setVisible(true);
	//QuitGame_label->setUserData((void)1);

    //unable start game button
	if (PVP_Btn != NULL)
    {
        PVP_Btn->setEnabled(false);
    }
    if (PVC_Btn != NULL)
    {
        PVC_Btn->setEnabled(false);
    }
    if (Story_Btn != NULL)
    {
        Story_Btn->setEnabled(false);
    }

    if (help_Btn != NULL)
    {
        help_Btn->setEnabled(false);
    }
    if (rateme_Btn != NULL)
    {
        rateme_Btn->setEnabled(false);
    }
    if (developer_Btn != NULL)
    {
        developer_Btn->setEnabled(false);
    }
    if (monster_Btn != NULL)
    {
        monster_Btn->setEnabled(false);
    }
    //end

	auto actionTo = ScaleTo::create(2.0f, 0.5f);
    auto actionBy = ScaleBy::create(2.0f, 1.0f, 10.0f);
    auto actionBy2 = ScaleBy::create(2.0f, 5.0f, 1.0f);

	auto scaleTo = ScaleTo::create(0.2f, 1.0f);

	auto callbackaction = Sequence::create(
        MoveBy::create(2.0f, Vec2(150,0)),
        CallFuncN::create( CC_CALLBACK_1(TitleUI::callback_QuitGameLable, this)),
        nullptr);

	QuitGame_label->runAction(Sequence::create(scaleTo, callbackaction, nullptr));
}

void TitleUI::callback_QuitGameLable(Ref* sender)
{
	quitGameBtn->setVisible(true);
	quitGameBtn->setEnabled(true);

    quitGameCancleBtn->setVisible(true);
    quitGameCancleBtn->setEnabled(true);

	//if (ResDef::getInstance()->IsRoleLocked((int)GamePlayerRole.GamePlayerRole_MATCHMAN) == true)
 //   {
 //       rateMeToUnlockBtn.visible = true;
 //       rateMeToUnlockBtn.Enabled = true;
 //   }
}

void TitleUI::StartStory_Game(Ref* sender)
{
    //CircleRunScene.UseAI = true;

    //CircleRunScene.g_GameMode = RunGameMode.MODE_STORY;

	GameScene::g_GameMode = RunGameMode::MODE_STORY;
	GameScene::UseAI = true;

	SoundManager::Instance()->PlayEffect(ResDef::g_SelectSound);
    SoundManager::Instance()->StopMusic();

	Director::getInstance()->replaceScene(GameScene::createScene(ResDef::getInstance()->g_ConfigStruct.CurrentArea));
	//Director::getInstance()->replaceScene(SceneMap.scene(ResDef.g_ConfigStruct.CurrentScene));
}

void TitleUI::StartPVP_Game(Ref* sender)
{
    //CircleRunScene.g_GameMode = RunGameMode.MODE_PVP;

    //CircleRunScene.UseAI = false;

    //if (ResDef.g_ConfigStruct.EnableAudio != 0)
    //{
    //    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_SelectSound);
    //    //SimpleAudioEngine.sharedEngine().stopBackgroundMusic();
    //}
    //MusicManager.Instance().PlayEffect(ResDef.g_SelectSound);
    //MusicManager.Instance().StopMusic();

	//Director::getInstance()->replaceScene(SelectRoleUI.scene());

}

void TitleUI::StartPVC_Game(Ref* sender)
{

    //CircleRunScene.UseAI = true;

    //CircleRunScene.g_GameMode = RunGameMode.MODE_PVC;

    //if (ResDef.g_ConfigStruct.EnableAudio != 0)
    //{
    //    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_SelectSound);
    //    //SimpleAudioEngine.sharedEngine().stopBackgroundMusic();
    //}
    //MusicManager.Instance().PlayEffect(ResDef.g_SelectSound);
    //MusicManager.Instance().StopMusic();

	//Director::getInstance()->replaceScene(SelectRoleUI.scene());
            
    //
}