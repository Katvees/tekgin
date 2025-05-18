#include "combat/attacks.hpp"
#include "core/character_base.hpp"

/// Temporary implementation! Will change!
int Attack::calculateDamage() const
{
	const Character::Attributes& attributes = attacker->getAttributes();
	switch (attack_type) {
	case Kind::MELEE:
		return attributes.strength * damage_coeff;
		break;
	case Kind::RANGED:
		return (attributes.strength * 0.6 + attributes.dexterity * 0.4) * damage_coeff;
		break;
	case Kind::MAGIC:
		return attributes.willpower * damage_coeff;
	}
}
