export module katvees.tekgin.core.character;
import std;

import katvees.tekgin.combat.elements;

export namespace Tekgin
{
enum class Size : char { TINY = 0, SMALL = 1, MEDIUM = 1, LARGE = 2, HUGE = 3 }; ///< Size classes of characters

/// Base class for all characters (e.g. enemies, NPCs, player)
class Character
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

	ElementMap<double> m_resistances{};
	ElementMap<double> m_weaknesses{};

 public:
	Character(const Character&)            = default;
	Character(Character&&)                 = default;
	Character& operator=(const Character&) = default;
	Character& operator=(Character&&)      = default;
	virtual ~Character()                   = default;

	Character(Attributes attributes, ElementMap<double> resistances = {}, ElementMap<double> weaknesses = {});

	template<typename... AttributeValues>
	Character(AttributeValues&&... attributes, ElementMap<double> resistances = {}, ElementMap<double> weaknesses = {})
		requires(std::is_constructible_v<Attributes, AttributeValues...>)
		 : attributes(Attributes{ std::forward<AttributeValues>(attributes)... }),
			m_resistances(resistances),
			m_weaknesses(weaknesses)
	{}

	/// Reduce health by damage - defense and apply relevant m_resistances and m_weaknesses
	virtual void takeDamage(int damage, const Element& damage_type);

	/// Initialize stats for character
	virtual void updateStats();

	void                             setResistance(Element element, double value) { m_resistances.get(element) = value; }
	[[nodiscard]] ElementMap<double> getResistances() { return m_resistances; }
	[[nodiscard]] double             getResistance(Element element) const { return m_resistances.get(element); }

	void                             setWeakness(Element element, double value) { m_weaknesses.get(element) = value; }
	[[nodiscard]] ElementMap<double> getWeaknesses() { return m_weaknesses; }
	[[nodiscard]] double             getWeakness(Element element) const { return m_weaknesses.get(element); }
};
} // namespace Tekgin
