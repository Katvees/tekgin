#include "core/character_base.hpp"

Character::Character(Attributes attrs, std::map<Element, float> res, std::map<Element, float> weak)
	: attributes(attrs), resistances(res), weaknesses(weak)
{
	updateStats();
}

void Character::updateStats()
{
	stats.health  = (int)(attributes.vitality * 0.8f + attributes.endurance * 0.4f) * 2;
	stats.stamina = (int)(attributes.vitality * 0.4f + attributes.endurance * 0.8f) * 2;
	stats.speed   = (int)(attributes.vitality * 0.3f + attributes.dexterity * 0.7f);
	stats.mana    = (int)(attributes.willpower + attributes.wisdom * 0.4f);
	stats.range   = (int)(attributes.size);
	stats.defense = attributes.endurance;
}

void Character::takeDamage(int damage, const Element& damage_type)
{
	damage *= 1.0f - resistances[Element::ALL] + weaknesses[Element::ALL]
	        - resistances[damage_type] + weaknesses[damage_type];
	// damage = damage < 0 ? 0 : damage;
	stats.health -= damage;
}

Character::Attributes::Attributes(int vi, int en, int st, int de, int ch, int in, int wi, int wp, Size si)
	: vitality(vi), endurance(en), strength(st), dexterity(de), charisma(ch), intelligence(in),
	  wisdom(wi), willpower(wp), size(si)
{
}
