#ifndef __Effect_Manager_H__
#define __Effect_Manager_H__

#include "cocos2d.h"

#include "Effect/Effects.h"

enum EffectType
{
	EFFECT_LightHitLeft = 0,
	EFFECT_LightHitRight,
	EFFECT_HeavyHit,
	EFFECT_ShellEffect,
	EFFECT_IceWave,
	EFFECT_ForceField,
	EFFECT_SteamEffect,
	EFFECT_Posion,
	EFFECT_BloodHitLeft,
	EFFECT_BloodHitRight,
	EFFECT_Mud,
};

class EffectManager : cocos2d::Layer
{
public:

	static EffectManager* m_Instance;

	EffectManager(void);
	~EffectManager(void);

	static EffectManager* Instance();

	virtual bool init();  

	virtual void update(float dt);

	void RemoveEffect(int index);

	void RemoveEffect(GameEffect* effect);

	void RemoveEffectWithTag(int tag);

	void RemoveAllEffects();

	void onEnter();

	void onExit();

	GameEffect* AddEffect(cocos2d::Node* node, EffectType type, cocos2d::Vec2 pos, float alivetime, bool bLoop, float onceTime);

	ParticleEffect* AddParticle(std::string parFile,cocos2d::Vec2 pos,float duringTime,cocos2d::Node* NodeParent);

	int AddParticle(ParticleEffect* NewEffect, cocos2d::Node* NodeParent,cocos2d::Vec2 pos);

	void RemoveAllParticleEffects();

	void RemoveParticleEffects(ParticleEffect* effect);

protected:
	static const int PoolVolum;

	cocos2d::Vector<GameEffect*> m_EffectsPool;

	//针对粒子系统的效果
	cocos2d::Vector<ParticleEffect*> m_ParticleEffectsPool;

	cocos2d::SpriteBatchNode* m_EffectBatchNode;
	cocos2d::ParticleBatchNode* m_ParticleBatchNode;

};

#endif //__Effect_Manager_H__
