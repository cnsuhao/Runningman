#include "TrapBanana.h"

USING_NS_CC;

TrapBanana::TrapBanana(void)
{
	m_TrapType = TrapType::TRAP_BANANA;
	m_FrameBaseName = "banana_2";
	m_TotalFrames = 1;
}


TrapBanana::~TrapBanana(void)
{
}

void TrapBanana::update(float dt)
{
	TrapBase::update(dt);
}

bool TrapBanana::checkCollision()
{
	return false;
}