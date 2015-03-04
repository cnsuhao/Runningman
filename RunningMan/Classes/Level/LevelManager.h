#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "cocos2d.h"
#include "Level/Area.h"

class LevelManager
{
public:	
	~LevelManager(void);

	static LevelManager* Instance();

	static const int SceneNum;
	std::vector<Area*> m_Areas;

	Area* VsAreaData;

	void init();

	void FillInfo();

protected:
	LevelManager(void);

	static LevelManager* m_Instance;
};

#endif //__LEVEL_MANAGER_H__