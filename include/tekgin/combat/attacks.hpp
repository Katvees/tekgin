#pragma once

#include "tekgin/combat/elements.hpp"
#include <functional>

namespace Tekgin
{
// Implemented as an aggregate struct for easier definition as all fields aren't usually needed
struct Attack
{
	enum class Kind : char { MELEE, RANGED, MAGIC };
	double  damage_coeff = 1.0, range_coeff = 1.0, speed_coeff = 1.0;
	Kind    attack_type = Kind::MELEE;
	Element damage_type = Element::NONE;
	/// A function that calculates the damage for the attack
	std::function<int(const Attack&)> damage_solver;
	/// Calculate damage of attack using damage_solver if set
	[[nodiscard]] int calculateDamage() const;
};
} // namespace Tekgin
