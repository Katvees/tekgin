#pragma once
#include <uuid/uuid.h>

namespace Tekgin
{
struct ISaveable
{
	virtual ~ISaveable() = default;
	virtual void Save()  = 0;
	virtual void Load()  = 0;

	static void IsLoaded(const uuid_t uuid) = {};
};
} // namespace Tekgin
