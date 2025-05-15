#pragma once

#include "combat/elements.hpp"
#include <map>
#include <memory>

using std::map;

/// Size classes of characters
enum class Size { TINY = 0, SMALL = 1, MEDIUM = 1, LARGE = 2, HUGE = 3 };

/// Base class for all characters (e.g. enemies, NPCs, player)
class Character
{
  public:
	/// Contains attributes of character
	struct Attributes
	{
		int  vitality, endurance, strength, dexterity;  // Physical
		int  charisma, intelligence, wisdom, willpower; // Mental
		Size size = Size::MEDIUM;

	  public:
		Attributes(int vitality, int endurance, int strength, int dexterity, int charisma,
		           int intelligence, int wisdom, int willpower, Size size = Size::MEDIUM);
	};

	struct Stats
	{
		int health, stamina, mana, range, speed, defense;
	};

  protected:
	Attributes attributes;
	Stats      stats, bonus;

	std::unique_ptr<map<Element, float>> resistances_ptr = std::make_unique<map<Element, float>>(); ///< Value is resistance coefficient between 0.0-1.0
	std::unique_ptr<map<Element, float>> weaknesses_ptr = std::make_unique<map<Element, float>>(); ///< Value is weakness coefficient between 0.0-1.0
	map<Element, float>& resistances = *resistances_ptr;
	map<Element, float>& weaknesses  = *weaknesses_ptr;

  public:
	Character(Attributes attributes, map<Element, float> resistances, map<Element, float> weaknesses);

	/// Reduce health by damage - defense and apply relevant resistances and weaknesses
	virtual void takeDamage(int damage, const Element& damage_type);

	/// Initialize stats for character
	virtual void updateStats();

	const map<Element, float>& getResitances() const { return resistances; }

	const map<Element, float>& getWeaknesses() const { return weaknesses; }
};
