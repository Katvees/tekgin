#include "core/character_base.hpp"

Character::Character(Attributes attrs, std::map<Element, float> res, map<Element, float> weak)
	: attributes(attrs), resistances(std::make_unique<std::map<Element, float>>(res)),
	  weaknesses(std::make_unique<std::map<Element, float>>(weak))
{
	updateStats();
}

void Character::updateStats()
{
	this->stats.health = (int)(this->attributes.vitality * 0.8f + this->attributes.endurance * 0.4f) * 2;
	this->stats.stamina = (int)(this->attributes.vitality * 0.4f + this->attributes.endurance * 0.8f) * 2;
	this->stats.speed = (int)(this->attributes.vitality * 0.3f + this->attributes.dexterity * 0.7f);
	this->stats.mana  = (int)(this->attributes.willpower + this->attributes.wisdom * 0.4f);
	this->stats.range = (int)(this->attributes.size);
	this->stats.defense = this->attributes.endurance;
}

void Character::takeDamage(int damage, const Element& damage_type)
{
	damage *= 1.0f - this->resistances[Element::ALL] + this->weaknesses[Element::ALL]
	        - this->resistances[damage_type] + this->weaknesses[damage_type];
	// damage = damage < 0 ? 0 : damage;
	this->stats.health -= damage;
}

Character::Attributes::Attributes(int vi, int en, int st, int de, int ch, int in, int wi, int wp, Size si)
	: vitality(vi), endurance(en), strength(st), dexterity(de), charisma(ch), intelligence(in),
	  wisdom(wi), willpower(wp), size(si)
{}
