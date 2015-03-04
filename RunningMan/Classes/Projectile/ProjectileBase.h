#ifndef __Projectile_Base_H__
#define __Projectile_Base_H__

#include "cocos2d.h"

enum ProjectileType
{
	PROJECTILE_WAND = 0,
};

class Player;

class ProjectileBase : public cocos2d::Sprite
{
	enum ProjectileAnimType
	{
		PROJECTILE_FLY = 0,
	};
public:

	ProjectileBase(void);
	~ProjectileBase(void);

	virtual void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);

	void update(float dt);

	bool isAlive();

	void setRunAngularVelocity(float v);

	float getTotalRunAngle();
	
	bool checkProjectileAttactPlayer(Player* pplayer);
	

	void setWidth(float va){width = va;}
	void setHeight(float va){height = va;}
	float getWidth(){return width;}
	float getHeight(){return height;}

	bool m_bUsingTrap;

protected:
	ProjectileType m_ProjectileType;

	float width;
	float height;

	float m_RunAV;
	float m_CurRunAV;
	float m_TotalRunAngle;

	float m_OffsetHeight;

	cocos2d::Vec2 m_SavedOldAncho;
	cocos2d::Vec2 m_SavedRotateBy;
	cocos2d::Vec2 m_OldSavedPos;

	float m_OriginalRotation;

	int m_LifeTime;
	bool m_IsAlive;

	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::string* ActionsName;
};

#endif //__Projectile_Base_H__

