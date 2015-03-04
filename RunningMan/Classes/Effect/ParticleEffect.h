#ifndef __Effect_Particle_H__
#define __Effect_Particle_H__

#include "cocos2d.h"

class ParticleEffect : public cocos2d::ParticleSystemQuad
{
public:
	ParticleEffect(float AliveTime, std::string particleFile);
	~ParticleEffect(void);

	void update(float dt);

	bool getAlive();

	virtual void internalInit();

public:
	float m_AliveTime;
	bool m_bAlive;
	cocos2d::Vec2 savePos;
};

#endif//__Effect_Particle_H__