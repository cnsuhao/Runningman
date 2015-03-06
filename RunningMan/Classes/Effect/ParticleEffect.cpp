#include "ParticleEffect.h"


ParticleEffect::ParticleEffect(float AliveTime, const std::string& particleFile) :
	cocos2d::ParticleSystemQuad()
{
	this->setPositionType(cocos2d::ParticleSystem::PositionType::GROUPED);
	//
	m_AliveTime = AliveTime;
	m_bAlive = true;
	//
	if (particleFile == "" ||
		particleFile.size() == 0)
	{
		internalInit();
	}
	else
	{
		const std::string& filename = particleFile;
		this->initWithFile(filename);
		this->stopSystem();
	}
}


ParticleEffect::~ParticleEffect(void)
{
}

void ParticleEffect::update(float dt)
{
	cocos2d::ParticleSystemQuad::update(dt);
	//
	if (m_AliveTime > 0.0f)
	{
		m_AliveTime -= dt;
	}
	else
	{
		m_bAlive = false;
	}
}

bool ParticleEffect::getAlive()
{
	return m_bAlive;
}

void ParticleEffect::internalInit()
{
	;
}

