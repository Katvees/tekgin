#pragma once

#include "combat/elements.hpp"
#include <cassert>
#include <initializer_list>
#include <memory>
#include <optional>
#include <unordered_map>


/// Size classes of characters
enum class Size : char { TINY = 0, SMALL = 1, MEDIUM = 1, LARGE = 2, HUGE = 3 };

/// Base class for all characters (e.g. enemies, NPCs, player)
class Character
{
	using ElementMap = std::unordered_map<Element, double>;
	using Element::ALL;

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
		int health{}, stamina{}, mana{}, range{}, speed{}, defense{};
	};


 protected:
	Attributes attributes;
	Stats      stats, bonus;

	std::unique_ptr<ElementMap> resistances_ptr; ///< Value is resistance coefficient between 0.0-1.0
	std::unique_ptr<ElementMap> weaknesses_ptr;  ///< Value is weakness coefficient between 0.0-1.0

 public:
	Character(const Character&)            = delete;
	Character(Character&&)                 = default;
	Character& operator=(const Character&) = delete;
	Character& operator=(Character&&)      = default;
	Character(const Attributes& attributes, const ElementMap& resistances, const ElementMap& weaknesses);
	virtual ~Character() = default;

	/// Reduce health by damage - defense and apply relevant resistances and weaknesses
	virtual void takeDamage(int damage, const Element& damage_type);

	/// Initialize stats for character
	virtual void updateStats();

	void setResitances(Element element, double value) { resistances_ptr->emplace(element, value); }

	[[nodiscard]] ElementMap& getResistances() { return *resistances_ptr; }
	[[nodiscard]] ElementMap& getWeaknesses() { return *weaknesses_ptr; }

	[[nodiscard]] std::optional<double> getResistance(Element element) const
	{
		const auto& it = resistances_ptr->find(element);
		return it != resistances_ptr->end() ? it->second : std::optional<double>{};
	}

	[[nodiscard]] std::optional<double> getWeakness(Element element) const
	{
		const auto& it = weaknesses_ptr->find(element);
		return it != weaknesses_ptr->end() ? it->second : std::optional<double>{};
	}
};
