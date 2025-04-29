#include "HealthComponent.h"

HealthComponent::HealthComponent(ActorObject* object, float maxHealth) : Component(object), maxHealth(maxHealth)
{
	currentHealth = maxHealth;
}

void HealthComponent::AddHealth(float healAmount)
{
	currentHealth += healAmount;
	currentHealth = std::clamp(currentHealth, 0.f, maxHealth);
}

void HealthComponent::DamageHealth(float damageAmount)
{
	currentHealth -= damageAmount;
	currentHealth = std::clamp(currentHealth, 0.f, maxHealth);
	if (currentHealth <= 0.f)
		HealthCall::OnDeath(0);

}
