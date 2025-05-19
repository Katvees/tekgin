#pragma once

#include "combat/elements.hpp"
#include <cassert>
#include <memory>
#include <optional>
#include <pthread.h>
#include <unordered_map>


namespace Tekgin
{
	/// Size classes of characters
	enum class Size : char { TINY = 0, SMALL = 1, MEDIUM = 1, LARGE = 2, HUGE = 3 };

	/// Base class for all characters (e.g. enemies, NPCs, player)
	class Character
	{
		using ElementMap = std::unordered_map<Element, double>;
		using Element::ALL;

	 public:
		/// Contains attributes of character
		struct Attributes
		{
			int  vitality, endurance, strength, dexterity;  // Physical
			int  charisma, intelligence, wisdom, willpower; // Mental
			Size size = Size::MEDIUM;
		};

		struct Stats
		{
			int health{}, stamina{}, mana{}, range{}, speed{}, defense{};

			Stats operator+=(const Stats& rhs)
			{
				this->health += rhs.health;
				this->stamina += rhs.stamina;
				this->mana += rhs.mana;
				this->range += rhs.range;
				this->speed += rhs.speed;
				this->defense += rhs.defense;
				return *this;
			}
		};

		friend Stats operator+(Stats lhs, const Stats& rhs);

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

		const Attributes& getAttributes() { return attributes; }

		/// Get stats with or without bonuses applied
		Stats getStats(bool with_bonuses = false) { return with_bonuses ? stats + bonus : stats; }

		void setResistance(Element element, double value) { resistances_ptr->insert_or_assign(element, value); }
		[[nodiscard]] ElementMap&           getResistances() { return *resistances_ptr; }
		[[nodiscard]] std::optional<double> getResistance(Element element) const
		{
			const auto& it = resistances_ptr->find(element);
			return it != resistances_ptr->end() ? it->second : std::optional<double>{};
		}

		void setWeakness(Element element, double value) { weaknesses_ptr->insert_or_assign(element, value); }
		[[nodiscard]] ElementMap&           getWeaknesses() { return *weaknesses_ptr; }
		[[nodiscard]] std::optional<double> getWeakness(Element element) const
		{
			const auto& it = weaknesses_ptr->find(element);
			return it != weaknesses_ptr->end() ? it->second : std::optional<double>{};
		}
	};
} // namespace Tekgin
