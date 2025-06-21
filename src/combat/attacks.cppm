export module katvees.tekgin.combat.attacks;
import std;

import katvees.tekgin.combat.elements;
import katvees.tekgin.core.character;

namespace Tekgin
{
export struct AttackResult;

export template<class C>
concept Attacker = requires(const C& c) {
	c.attack();
	std::is_base_of_v<Character, C>;
};

export struct Attack
{
	enum Kind : std::uint8_t { MELEE, RANGED, MAGIC };

	Kind    kind         = Kind::MELEE;
	Element element      = Element::NONE;
	double  damage_coeff = 1.0, range_coeff = 1.0, speed_coeff = 1.0; ///< @brief Stat coefficients of attach

	/**
	 * @brief Get AttackResult for attack.
	 *
	 * @param attacker Owner of the attack
	 * @return The result of the attack
	 *
	 * @todo Implement support for items, likely remove and handle logic elsewhere
	 */
	AttackResult getResult(Attacker auto& attacker);
};

export struct AttackResult
{
	Attack::Kind kind    = Attack::Kind::MELEE;
	Element      element = Element::NONE;
	int          damage = 0, range = 0, speed = 0; ///< @brief Stats of attack
};

} // namespace Tekgin
