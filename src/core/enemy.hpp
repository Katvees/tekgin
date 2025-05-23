#pragma once
#include "core/character_base.hpp"
#include "core/interface/saveable.hpp"
#include <functional>

#define ulong unsigned long long

using std::hash;

namespace Tekgin
{
class Enemy : public Character, ISaveable
{
	static ulong count;

	ulong       id;
	hash<ulong> id_hash;

 public:
	void Save() override;
	void Load() override;

	ulong       getId() override { return id; };
	hash<ulong> getIdHash() override { return id_hash; };
};
} // namespace Tekgin
