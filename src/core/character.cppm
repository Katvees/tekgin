export module katvees.tekgin.core.character;
import std;

import katvees.tekgin.combat.elements;

using ElementMap = std::array<double, static_cast<std::size_t>(Tekgin::Element::COUNT)>; ///< std::array<Element, Element::COUNT>
///
namespace Tekgin
{
export enum class Size : char { TINY = 0, SMALL = 1, MEDIUM = 1, LARGE = 2, HUGE = 3 }; ///< Size classes of characters

/// Base class for all characters (e.g. enemies, NPCs, player)
export class Character
{

 public:
	/// Contains attributes of character
	struct Attributes
	{
		int  vitality{}, endurance{}, strength{}, dexterity{};  // Physical
		int  charisma{}, intelligence{}, wisdom{}, willpower{}; // Mental
		Size size = Size::MEDIUM;
	};

	const Attributes& getAttributes() { return attributes; }

	/// Contains stats of character
	struct Stats
	{
		int health{}, stamina{}, mana{}, range{}, speed{}, defense{};

		Stats& operator+=(const Stats& rhs);
		Stats& operator-=(const Stats& rhs);
	};


	friend Stats operator+(Stats lhs, const Stats& rhs) { return lhs += rhs; };
	friend Stats operator-(Stats lhs, const Stats& rhs) { return lhs += rhs; };

	/// Get stats with or without bonuses applied
	Stats getStats(bool with_bonuses = false) { return with_bonuses ? stats + bonus : stats; }

 protected:
	Attributes attributes;
	Stats      stats, bonus;

	ElementMap m_resistances{};                      ///< Array associated with the Elements enum class
	ElementMap m_weaknesses{};                       ///< Array associated with the Elements enum class

 public:
	Character(const Character&)            = delete; // Implement later
	Character(Character&&)                 = default;
	Character& operator=(const Character&) = delete; // Implement later
	Character& operator=(Character&&)      = default;
	Character(Attributes attributes, ElementMap m_resistances = {}, ElementMap m_weaknesses = {});
	virtual ~Character() = default;

	/// Reduce health by damage - defense and apply relevant m_resistances and m_weaknesses
	virtual void takeDamage(int damage, const Element& damage_type);

	/// Initialize stats for character
	virtual void updateStats();

	 void                      setResistance(Element element, double value) { m_resistances.at(static_cast<std::size_t>(element)) = value; }
	[[nodiscard]]  ElementMap  getResistances() { return m_resistances; }
	[[nodiscard]]  double      getResistance(Element element) const { return m_resistances.at(static_cast<std::size_t>(element)); }

	 void                      setWeakness(Element element, double value) { m_weaknesses.at(static_cast<std::size_t>(element)) = value; }
	[[nodiscard]]  ElementMap  getWeaknesses() { return m_weaknesses; }
	[[nodiscard]]  double      getWeakness(Element element) const { return m_weaknesses.at(static_cast<std::size_t>(element)); }
};
} // namespace Tekgin
