#ifndef __GAMESTATUS_MANAGER_H__
#define __GAMESTATUS_MANAGER_H__

#include "cocos2d.h"

enum GameStatus
{
	GAMESTATUS_NULL = 0,
	GAMESTATUS_TITLE,
	GAMESTATUS_SCENEMAP,
	GAMESTATUS_SELECTROLE,
	GAMESTATUS_PLAY,
	GAMESTATUS_SOCIAL,
	GAMESTATUS_PAUSE,
	GAMESTATUS_ABOUT,
	GAMESTATUS_HELP,
	GAMESTATUS_GALLERY,
	GAMESTATUS_DEVELOPER,
	GAMESTATUS_STORYEND
};

class GameStatusManager
{
public:
	
	~GameStatusManager(void);

	static GameStatusManager* Instance();

	void SetStatus(GameStatus state);

	GameStatus GetStatus();

private:
	GameStatusManager(void);

	static GameStatusManager* m_Instance;

	GameStatus m_CurStatus;
};

#endif//__GAMESTATUS_MANAGER_H__