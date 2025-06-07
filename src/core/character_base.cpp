module katvees.tekgin.core.character_base;
import <unordered_map>;
import <sstream>;
import <vector>;


import katvees.tekgin.combat.elements;

using std::unordered_map;

namespace Tekgin
{
Character::Character(const Attributes&                          attrs,
                     const unordered_map<Element, double>&      res,
                     const std::unordered_map<Element, double>& weak)
	 : attributes(attrs),
		stats(),
		bonus(),
		resistances_ptr(std::make_unique<unordered_map<Element, double>>(res)),
		weaknesses_ptr(std::make_unique<unordered_map<Element, double>>(weak))
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
	damage *= 1 - getResistance(Element::ALL).value_or(0.0) + getWeakness(Element::ALL).value_or(0.0)
	        - getResistance(damage_type).value_or(0.0) + getWeakness(damage_type).value_or(0.0);
	damage = damage < 0 ? 0 : damage;
	stats.health -= damage;
}
} // namespace Tekgin
