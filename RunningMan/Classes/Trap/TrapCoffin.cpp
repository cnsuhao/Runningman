#include "TrapCoffin.h"

USING_NS_CC;

TrapCoffin::TrapCoffin(void)
{
	m_TrapType = TrapType::TRAP_COFFIN;
	m_FrameBaseName = "Coffin";
	m_TotalFrames = 1;
}


TrapCoffin::~TrapCoffin(void)
{
}

void TrapCoffin::update(float dt)
{
	TrapBase::update(dt);
}

bool TrapCoffin::checkCollision()
{
	return false;
}