#pragma once

#include "RE/C/ContainerItemExtra.hpp"
#include "RE/I/INSTANCE_FILTER.hpp"

namespace RE
{
	class CALCED_OBJECT
	{
	public:
		// members
		TESBoundObject* object;			// 0x00
		const char* overrideName;		// 0x08
		std::int32_t count;				// 0x10
		ContainerItemExtra itemExtra;	// 0x18
		INSTANCE_FILTER instanceFilter; // 0x30
	};

	static_assert(sizeof(CALCED_OBJECT) == 0x58);
}
