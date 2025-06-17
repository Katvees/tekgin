module katvees.tekgin.core.character;
import std;

import katvees.tekgin.combat.elements;

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

Character::Character(Attributes attributes, ElementMap<double> resistances, ElementMap<double> weaknesses)
	 : attributes(attributes),
		stats(),
		bonus(),
		m_resistances(resistances),
		m_weaknesses(weaknesses)
{
	updateStats();
}

void Character::takeDamage(int damage, const Element& damage_type)
{
	damage *= 1 - getResistance(Element::ALL) + getWeakness(Element::ALL) - getResistance(damage_type)
	        + getWeakness(damage_type);
	damage = damage < 0 ? 0 : damage;
	stats.health -= damage;
}
} // namespace Tekgin
