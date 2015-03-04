#include "ItemManager.h"

ItemManager* ItemManager::m_Instance = nullptr;

const int ItemManager::NumItemPlace = 360;

ItemManager* ItemManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new ItemManager();
	}

	return m_Instance;
}

ItemManager::ItemManager(void)
{
	//m_ItemList.reserve(NumItemPlace);
	//for (int i=0; i<NumItemPlace; ++i)
	//{
	//	m_ItemList.pushBack(nullptr);
	//}
}


ItemManager::~ItemManager(void)
{
}

void ItemManager::update(float dt)
{
	for (int i = 0; i < m_ItemList.size(); ++i)
	{
		ItemBase* pItem = m_ItemList.at(i);
		if (pItem != nullptr)
		{
			pItem->update(dt);
		}
	}

	for (cocos2d::Map<int,ItemBase*>::iterator it = m_ItemList.begin(); it!=m_ItemList.end(); ++it)
	{
		ItemBase* pItem = it->second;
		if (pItem != nullptr)
		{
			pItem->update(dt);
		}
	}
}

//item
ItemBase* ItemManager::CreateItem(int index, ItemType type)
{
	if (index > m_ItemList.size() || m_ItemList.at(index) != nullptr)
	{
		return nullptr;
	}
	ItemType theitemtype = (ItemType)type;
	ItemBase* pitem = nullptr;
	switch (theitemtype)
	{
	case ItemType::Item_Coin:
		{
			//pitem = new Coin();
			m_AppearCoin++;
		}                    
		break;
	}

	if (pitem != nullptr)
	{
		//m_ItemList.replace(index,pitem);
		m_ItemList.insert(index,pitem);
	}
	return pitem;
}

ItemBase* ItemManager::GetItem(int index)
{
	cocos2d::Map<int,ItemBase*>::iterator it = m_ItemList.find(index);
	if (it != m_ItemList.end())
	{
		return it->second;
	}
	//if (index < NumItemPlace)
	//{
	//	return m_ItemList.at(index);
	//}
	return nullptr;
}

bool ItemManager::CheckItem(int index)
{
	//if (m_ItemList.at(index) == nullptr)
	//{
	//	return false;
	//}
	cocos2d::Map<int,ItemBase*>::iterator it = m_ItemList.find(index);
	if (it == m_ItemList.end())
	{
		return false;
	}
	return true;
}

void ItemManager::DelItem(int index)
{
	//ItemBase* pItem = m_ItemList.at(index);
	//if (pItem != nullptr)
	//{		
	//	CC_SAFE_DELETE(pItem);
	//	m_ItemList.replace(index,nullptr);
	//}

	cocos2d::Map<int,ItemBase*>::iterator it = m_ItemList.find(index);
	if (it != m_ItemList.end())
	{
		m_ItemList.erase(it);
	}
}

void ItemManager::CleanItems()
{
	//for (int i; i<m_ItemList.size(); ++i)
	//{
	//	ItemBase* pItem = m_ItemList.at(i);
	//	CC_SAFE_DELETE(pItem);
	//	m_ItemList.replace(i,nullptr);
	//}

	m_ItemList.clear();
}