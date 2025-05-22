#pragma once

#include <uuid/uuid.h>

namespace Tekgin
{
struct ISaveable
{
	ISaveable()                            = delete;
	ISaveable(const ISaveable&)            = delete;
	ISaveable& operator=(const ISaveable&) = delete;
	ISaveable(ISaveable&&)                 = delete;
	ISaveable& operator=(ISaveable&&)      = delete;
	virtual ~ISaveable()                   = 0;

	virtual void Save() = 0;
	virtual void Load() = 0;

	uuid_t uuid{};
};
} // namespace Tekgin
