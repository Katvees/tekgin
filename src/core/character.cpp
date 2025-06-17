module katvees.tekgin.core.character;
import std;

import katvees.tekgin.combat.elements;

using ElementMap = std::array<double, static_cast<std::size_t>(Tekgin::Element::COUNT)>; ///< std::array<Element, Element::COUNT>

namespace Tekgin
{
Character::Stats& Character::Stats::operator+=(const Character::Stats& rhs)
{
	this->health += rhs.health;
	this->stamina += rhs.stamina;
	this->mana += rhs.mana;
	this->range += rhs.range;
	this->speed += rhs.speed;
	this->defense += rhs.defense;
	return *this;
}

Character::Stats& Character::Stats::operator-=(const Character::Stats& rhs)
{
	this->health -= rhs.health;
	this->stamina -= rhs.stamina;
	this->mana -= rhs.mana;
	this->range -= rhs.range;
	this->speed -= rhs.speed;
	this->defense -= rhs.defense;
	return *this;
}

Character::Character(Attributes attrs, ElementMap res, ElementMap weak)
	 : attributes(attrs),
		stats(),
		bonus(),
		m_resistances(std::move(res)),
		m_weaknesses(std::move(weak))
{
	updateStats();
}

void Character::updateStats()
{
	stats.health  = static_cast<int>((attributes.vitality * 0.8 + attributes.endurance * 0.4) * 2);
	stats.stamina = static_cast<int>((attributes.vitality * 0.4 + attributes.endurance * 0.8) * 2);
	stats.speed   = static_cast<int>(attributes.vitality * 0.3 + attributes.dexterity * 0.7);
	stats.mana    = static_cast<int>((attributes.willpower + attributes.wisdom * 0.4) * 4);
	stats.range   = static_cast<int>(attributes.size);
	stats.defense = attributes.endurance;
}

void Character::takeDamage(int damage, const Element& damage_type)
{
	damage *= 1 - getResistance(Element::ALL) + getWeakness(Element::ALL)
	        - getResistance(damage_type) + getWeakness(damage_type);
	damage = damage < 0 ? 0 : damage;
	stats.health -= damage;
}
} // namespace Tekgin
