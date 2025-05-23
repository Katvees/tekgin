#pragma once

#include <functional>

#define ulong unsigned long long

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

	virtual void save() = 0;
	virtual void load() = 0;

	virtual ulong            getId()     = 0;
	virtual std::hash<ulong> getIdHash() = 0;
};
} // namespace Tekgin
