#include "EffectManager.h"
#include "ResDef.h"
//-------------------------------------------------------
const int EffectManager::PoolVolum = 100;


//-------------------------------------------------------
EffectManager* EffectManager::m_Instance = nullptr;

EffectManager* EffectManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new EffectManager();
	}

	return m_Instance;
}
//-------------------------------------------------------
EffectManager::EffectManager(void)
{
}


EffectManager::~EffectManager(void)
{
}

//-------------------------------------------------------
bool EffectManager::init()
{
	if (cocos2d::Layer::init() == false) return false;

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_GameEffectPListFile);
	m_EffectBatchNode = cocos2d::SpriteBatchNode::create(ResDef::g_GameEffectTextureFile);

	cocos2d::ParticleSystemQuad::create(ResDef::g_GameParticlePListFile);
	m_ParticleBatchNode = cocos2d::ParticleBatchNode::create(ResDef::g_GameParticleTextureFile);

	return true;
}
void EffectManager::update(float dt)
{
	for (int i = 0; i < m_EffectsPool.size(); ++i)
	{
		GameEffect* peffect = m_EffectsPool.at(i);
		//
		cocos2d::Node* Node = (cocos2d::Node*)(peffect->getUserData());

		if (Node != nullptr)
		{
			cocos2d::Vec2 newPoint = Node->getPosition() + peffect->savePos;
			peffect->setPosition(newPoint);
		}
		else
		{
			peffect->setPosition(peffect->savePos);
		}
		//
		peffect->update(dt);
	}
	//
	for (int i = m_ParticleEffectsPool.size() - 1; i > -1; i--)
	{
		ParticleEffect* peffect = m_ParticleEffectsPool.at(i);

		cocos2d::Node* pNode = (cocos2d::Node*)(peffect->getUserData());

		if (pNode != nullptr)
		{
			cocos2d::Vec2 newPoint = pNode->getPosition() + peffect->savePos;
			peffect->setPosition(newPoint);
		}
		else
		{
			peffect->setPosition(peffect->savePos);
		}
		//
		//peffect.Update(dt);
		//
		//if (peffect->getAlive() == false)
		//{
		//	RemoveParticleEffects(peffect);
		//}
	}
}

void EffectManager::RemoveEffect(int index)
{
	cocos2d::Vector<GameEffect*>::iterator it = m_EffectsPool.begin();
	for (; it != m_EffectsPool.end(); ++it)
	{
		GameEffect* peffect = *it;
		if (peffect == nullptr)
		{
			m_EffectsPool.erase(it);
			return;
		}

		if (index == peffect->getIndex())
		{
			peffect->m_bAlive = false;
			peffect->removeFromParentAndCleanup(true);
			peffect->release();
			m_EffectsPool.erase(it);
			return;
		}
	}
}

void EffectManager::RemoveEffect(GameEffect* effect)
{
	cocos2d::Vector<GameEffect*>::iterator it = m_EffectsPool.begin();
	for (; it != m_EffectsPool.end(); ++it)
	{
		GameEffect* peffect = *it;
		if (peffect == nullptr)
		{
			m_EffectsPool.erase(it);
			return;
		}

		if (effect == peffect)
		{
			peffect->m_bAlive = false;
			peffect->removeFromParentAndCleanup(true);
			peffect->release();
			m_EffectsPool.erase(it);
			return;
		}
	}
}

void EffectManager::RemoveEffectWithTag(int tag)
{
	cocos2d::Vector<GameEffect*>::iterator it = m_EffectsPool.begin();
	for (; it != m_EffectsPool.end(); ++it)
	{
		GameEffect* peffect = *it;
		if (peffect == nullptr)
		{
			m_EffectsPool.erase(it);
			return;
		}

		if (tag == peffect->getTag())
		{
			peffect->m_bAlive = false;
			peffect->removeFromParentAndCleanup(true);
			peffect->release();
			m_EffectsPool.erase(it);
			return;
		}
	}
}

void EffectManager::RemoveAllEffects()
{
	for (int i = 0; i < m_EffectsPool.size(); ++i)
	{
		GameEffect* peffect = m_EffectsPool.at(i);

		m_EffectBatchNode->removeChild(peffect, true);

		delete peffect;
	}
	m_EffectsPool.clear();
}

void EffectManager::onEnter()
{
	cocos2d::Layer::onEnter();
	//
	for (int i = 0; i < m_EffectsPool.size(); ++i)
	{
		GameEffect* peffect = m_EffectsPool.at(i);
		peffect->Play();
	}
}

void EffectManager::onExit()
{
	cocos2d::Layer::onExit();
	//
	for (int i = 0; i < m_EffectsPool.size(); ++i)
	{
		GameEffect* peffect = m_EffectsPool.at(i);
		peffect->Stop();
	}
}

GameEffect* EffectManager::AddEffect(cocos2d::Node* node, EffectType type, cocos2d::Vec2 pos, float alivetime, bool bLoop, float onceTime)
{
	GameEffect* pEffect = nullptr;
	switch (type)
	{
	case EffectType::EFFECT_LightHitLeft:
		pEffect = new TestEffect(alivetime, bLoop, onceTime);
		break;
	//case EffectType::EFFECT_LightHitRight:
	//	pEffect = new LightHitRightEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_HeavyHit:
	//	pEffect = new HeavyHitEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_ShellEffect:
	//	pEffect = new ShellEffect(alivetime, bLoop, onceTime);
	//	break;
	//	//                 case EffectType.EFFECT_IceWave:
	//	//                     pEffect = new IceWaveEffect(alivetime, bLoop, onceTime);
	//	//                     break;
	//case EffectType::EFFECT_ForceField:
	//	pEffect = new ForceFieldEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_SteamEffect:
	//	pEffect = new SteamEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_Posion:
	//	pEffect = new PosionEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_BloodHitLeft:
	//	pEffect = new BloodHitLeftEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_BloodHitRight:
	//	pEffect = new BloodHitRightEffect(alivetime, bLoop, onceTime);
	//	break;
	//case EffectType::EFFECT_Mud:
	//	pEffect = new MudEffect(alivetime, bLoop, onceTime);
	//	break;

	}
	if (pEffect != nullptr)
	{
		pEffect->savePos = cocos2d::Vec2(pos.x, pos.y);
		pEffect->setUserData(node);
		m_EffectsPool.pushBack(pEffect);
		m_EffectBatchNode->addChild((Node*)pEffect,20);
		//
		pEffect->Play();
	}

	return pEffect;
}

ParticleEffect* EffectManager::AddParticle(std::string parFile, cocos2d::Vec2 pos, float duringTime,cocos2d::Node* NodeParent)
{
	for (int i = 0;i<m_ParticleEffectsPool.size();++i)
	{
		ParticleEffect* effect = m_ParticleEffectsPool.at(i);
		if (effect->getParticleCount() == 0
			&& effect->isActive() == false)
		{
			effect->release();
			effect = new ParticleEffect(duringTime, parFile);
			//
			return nullptr;
		}
	}
	//
	ParticleEffect* NewEffect = new ParticleEffect( duringTime,parFile );
	if (NodeParent != nullptr)
	{
		NewEffect->setUserData(NodeParent);
	}

	NewEffect->savePos = cocos2d::Vec2(pos.x, pos.y);

	//
	m_ParticleEffectsPool.pushBack(NewEffect);

	m_ParticleBatchNode->addChild(NewEffect);
	//
	return NewEffect;
}

int EffectManager::AddParticle(ParticleEffect* NewEffect, cocos2d::Node* NodeParent,cocos2d::Vec2 pos)
{
	for (int i = 0; i < m_ParticleEffectsPool.size(); ++i)
	{
		ParticleEffect* effect = m_ParticleEffectsPool.at(i);
		if (effect == nullptr)
		{                   
			effect = NewEffect;
			effect->savePos = cocos2d::Vec2(pos.x, pos.y);
			effect->setUserData(NodeParent);
			effect->resetSystem();

			m_ParticleBatchNode->addChild(effect);
			//
			return i;
		}
	}
	//
	NewEffect->setUserData(NodeParent);
	NewEffect->savePos = cocos2d::Vec2(pos.x, pos.y);
	NewEffect->resetSystem();
	m_ParticleBatchNode->addChild(NewEffect);
	m_ParticleEffectsPool.pushBack(NewEffect);
	return m_ParticleEffectsPool.size() - 1;
}

void EffectManager::RemoveAllParticleEffects()
{
	for (int i = 0; i < m_ParticleEffectsPool.size();++i )
	{
		ParticleEffect* effect = m_ParticleEffectsPool.at(i);
		effect->removeFromParentAndCleanup(true);
		effect->release();
	}
	m_ParticleEffectsPool.clear();
}

void EffectManager::RemoveParticleEffects(ParticleEffect* effect)
{
	if (effect!= nullptr && effect->getParent() != nullptr)
	{
		effect->removeFromParentAndCleanup(true);
		effect->release();
		effect = nullptr;
	}
	//这里不应该remove，这样会影响性能
	for (int i=0; i< m_ParticleEffectsPool.size(); ++i)
	{
		if (effect == m_ParticleEffectsPool.at(i))
		{
			m_ParticleEffectsPool.replace(i,nullptr);
		}
		break;
	}
}