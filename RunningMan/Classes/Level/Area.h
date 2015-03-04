#ifndef __Area_H__
#define __Area_H__

#include "cocos2d.h"
#include "Level/GameLevel.h"

class Area
{
public:
	Area(void);
	~Area(void);

	GameLevel* GetGameLevel(int n)
	{
		if ( n < m_GameLevels.size() )
		{
			return m_GameLevels[n];
		}

		return nullptr;	
	}

	int LevelNum;

	std::vector<GameLevel*> m_GameLevels;
	
};

#endif //__Area_H__