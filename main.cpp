import std;
import katvees.tekgin;

int main()
{
	using namespace Tekgin;
	using enum Util::LogLevel;

	Engine& engine = Engine::get();

	Character chara{
		{ .vitality     = 1,
       .endurance    = 1,
       .strength     = 1,
       .dexterity    = 1,
       .charisma     = 1,
       .intelligence = 1,
       .wisdom       = 1,
       .willpower    = 1,
       .size         = Character::Size::SMALL }
	};

	Enemy enemy1{ chara };
	Enemy enemy2{ const_cast<Character&&>(chara) };
	Enemy enemy3{ dynamic_cast<Character&>(enemy1) };
	Enemy enemy4{ { { .vitality = 0 } } };
	try {
		std::println("{}", Enemy::getCount());
		std::println("{}", chara.getAttributes().vitality);
		std::println("{}", enemy2.getAttributes().vitality);
	} catch (const std::exception& err) {
		Util::log(ERROR, "{}", err.what());
	}
	Util::log(enemy1);
	return 0;
}
