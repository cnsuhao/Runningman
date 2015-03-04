#ifndef __FULLMAP_SCENE_H__
#define __FULLMAP_SCENE_H__

#include "cocos2d.h"

class WorldMapScene : public cocos2d::Layer
{
public:
	WorldMapScene(void);
	~WorldMapScene(void);

	//
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	void SetCurrentScene(int nS);

	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	//callback
	void callback_OnPressBack(Ref* sender);
	void callback_OnPressStart(Ref* sender);

	//
	CREATE_FUNC(WorldMapScene);

private:
	int currentSelectLevel;
	cocos2d::Vector<cocos2d::Sprite*> m_crossesIcons;
	cocos2d::Vector<cocos2d::Sprite*> m_circleIcons;

	static const float touchRadius;
	cocos2d::Sprite* m_pMap;

	cocos2d::Size winSize;
	//
	int SceneIndex;
	int PassedLevel;
};

#endif //__FULLMAP_SCENE_H__