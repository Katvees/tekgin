export module katvees.tekgin.combat.enemy;
import std;

import katvees.tekgin.core.character;
import katvees.tekgin.core.interfaces.saveable;

using ullong = unsigned long long;

using std::hash;

export namespace Tekgin
{
class Enemy : public Character, ISaveable
{
	~Enemy() override = default;
	
	static ullong count;

	ullong       id;
	hash<ullong> id_hash;

 public:
	void         save() override;
	void         load() override;
	ullong       getId() override { return id; };
	hash<ullong> getIdHash() override { return id_hash; };
};
} // namespace Tekgin
