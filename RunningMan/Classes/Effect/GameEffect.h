#ifndef __Effect_H__
#define __Effect_H__

#include "cocos2d.h"
#include <string.h>

class GameEffect : public cocos2d::Sprite
{
public:
	GameEffect(float alivetime, bool bLoop, float onceTime);
	~GameEffect(void);

	void Init();

	void update(float delta);

	void Play();

	void Stop();

	bool getAlive();

	int getIndex();

public:
	float m_AliveTime;
	std::string m_FrameName;
	int m_FrameCount;
	int m_Index;
	cocos2d::Vec2 savePos;
	
	cocos2d::ActionInterval* m_Action;

	bool m_bAlive;
	bool m_bLoop;
	float m_fOnceTime;
	bool Playing;

	static const std::string effectTextureName;
	static int s_Index;
	
};

#endif //__Effect_H__