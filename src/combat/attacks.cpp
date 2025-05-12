#include "combat/attacks.hpp"
#include "combat/elements.hpp"

Attack::Attack(float dc, float rc, float sc, AttackType at, Element dt) :
	damage_coefficient(dc), range_coefficient(rc), speed_coefficient(sc), attack_type(at), damage_type(dt)
{
}
