#pragma once
#include "Component.h"
#include "HealthCaller.h"

class HealthComponent : public Component
{
public:
	HealthComponent(ActorObject* object, float maxHealth);
	~HealthComponent() = default;

	void AddHealth(float healAmount);
	void DamageHealth(ActorObject* objectHit, float damageAmount);

private:
	float currentHealth;
	float maxHealth;
};

