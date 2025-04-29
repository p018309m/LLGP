#pragma once
#include "Component.h"
#include "HealthCaller.h"

class HealthComponent : public Component
{
public:
	HealthComponent(ActorObject* object, float maxHealth);

	void AddHealth(float healAmount);
	void DamageHealth(float damageAmount);

private:
	float currentHealth;
	float maxHealth;
};

