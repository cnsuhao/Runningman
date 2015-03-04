#ifndef __Effects_H__
#define __Effects_H__

#include "Effect/GameEffect.h"
#include "Effect/ParticleEffect.h"

class TestEffect : public GameEffect
{
public:
	TestEffect(float alivetime, bool bLoop, float onceTime);
	~TestEffect(void);
};

#endif //__Effects_H__
