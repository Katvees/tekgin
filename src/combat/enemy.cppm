export module katvees.tekgin.combat.enemy;
import <functional>;

import katvees.tekgin.core.character;
import katvees.tekgin.core.interfaces.saveable;

#define ulong unsigned long long

using std::hash;

export namespace Tekgin
{
class Enemy : public Character, ISaveable
{
	static ulong count;

	ulong       id;
	hash<ulong> id_hash;

 public:
	void save() override;
	void load() override;

	ulong       getId() override { return id; };
	hash<ulong> getIdHash() override { return id_hash; };
};
} // namespace Tekgin
