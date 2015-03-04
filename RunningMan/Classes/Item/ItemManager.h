#ifndef __Item_Manager_H__
#define __Item_Manager_H__

#include "cocos2d.h"

#include "Item/ItemBase.h"

class ItemManager
{
private:
	static ItemManager* m_Instance;

	//cocos2d::Vector<ItemBase*> m_ItemList;
	cocos2d::Map<int , ItemBase*> m_ItemList;

	ItemManager(void);

	int m_AppearCoin;

	const static int NumItemPlace;
public:
	
	~ItemManager(void);

	static ItemManager* Instance();

	void update(float dt);

	//item
	ItemBase* CreateItem(int index, ItemType type);

	ItemBase* GetItem(int index);

	bool CheckItem(int index);

	void DelItem(int index);

	void CleanItems();
};

#endif //__Item_Manager_H__