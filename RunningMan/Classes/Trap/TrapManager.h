#ifndef __Trap_Manager_H__
#define __Trap_Manager_H__

#include "cocos2d.h"

#include "TrapBase.h"

class TrapManager
{
private:
	//cocos2d::Vector<TrapBase*> m_TrapList;

	cocos2d::Map<int,TrapBase*> m_TrapList;

	static TrapManager* m_Instance;

	TrapManager(void);

	const static int NumTrapPlace;
public:
	static TrapManager* Instance();
	~TrapManager(void);

	void update(float dt);

	TrapBase* CreateTrap(int index, TrapType type);

	void CleanTraps();

	void DestoryAll();

	int GetNumActiveTraps();

	TrapBase* GetTrap(int index);

	void delTrap(int index);

	bool CheckTrap(int index);
};

#endif //__Trap_Manager_H__