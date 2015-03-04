#ifndef __Item_Base_H__
#define __Item_Base_H__

#include "cocos2d.h"

class Track;

enum ItemType
{
	Item_Coin = 0,
};

class ItemBase : public cocos2d::Sprite
{
protected:
	ItemType m_ItemType;
	Track* m_Track;

	float width;
	float height;
public:
	ItemBase(void);
	~ItemBase(void);

	bool m_bUsingItem;
	bool m_bItemAlive;

	void setWidth(float va){ width = va; }
	void setHeight(float va){ height = va; }
	float setWidth(){return width;}
	float setHeight(){return height;}

	void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);

	void update(float dt);

	bool checkCollision();

	ItemType getItemType();

	void readydead();
};

#endif //__Item_Base_H__