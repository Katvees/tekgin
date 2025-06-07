module katvees.tekgin.combat.attacks;

int Tekgin::Attack::calculateDamage() const
{
	// Check for damage solver
	if (damage_solver) {
		return damage_solver(*this);
	}
	return 0;
}
