#pragma once

#include "combat/elements.hpp"
#include "core/character_base.hpp"

struct Attack
{
	enum class Kind : char { MELEE, RANGED, MAGIC };
	double  damage_coeff = 1.0, range_coeff = 1.0, speed_coeff = 1.0;
	Kind    attack_type = Kind::MELEE;
	Element damage_type = Element::NONE;
	Character* attacker = nullptr;
	// [[nodiscard]] int calculateDamage() const;
};
