#pragma once

#include "combat/elements.hpp"

enum class AttackType { MELEE, RANGED, MAGIC };

struct Attack
{
	float damage_coefficient, range_coefficient, speed_coefficient;
	AttackType attack_type;
	Element damage_type;

	Attack(
		float damage_coefficient = 1.0f,
		float range_coefficient = 1.0f,
		float speed_coefficient = 1.0f,
		AttackType attack_type = AttackType::MELEE,
		Element damage_type = Element::NONE
	);
};
