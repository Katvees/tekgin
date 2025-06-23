module;
#include <cassert>
module katvees.tekgin.combat.enemy;

using enum Tekgin::Util::LogLevel;

namespace Tekgin
{

Enemy::Enemy(Character character) : Character(std::move(character))
{
	Util::log(DEBUG, "Constructed Enemy from Character ({})", s_count);
	Util::log(DEBUG, *this);
	assert(s_count >= 0 && "Enemy count negative during contruction");
}

Enemy::~Enemy()
{
	assert(s_count >= 0 && "Enemy count negative after destruction");
	Util::log(DEBUG, "Destructed Enemy({})", s_count--);
}

void Enemy::serialize(std::ostream& ostr) const { ostr << "Enemy"; }
void Enemy::deserialize(std::istream& istr) const { std::cout << istr.rdbuf(); }

Util::LogData<int> Enemy::logFormat() const { return Util::log_format_helper("Health: {}", this->stats.health); }
} // namespace Tekgin
