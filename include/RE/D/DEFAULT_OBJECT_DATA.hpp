#pragma once

#include "RE/D/DEFAULT_OBJECT.hpp"
#include "RE/D/DEFAULT_OBJECT_TYPE.hpp"
#include "RE/F/FormType.hpp"

namespace RE
{
	class DEFAULT_OBJECT_DATA
	{
	public:
		[[nodiscard]] static auto GetDefaultObjects()
			-> std::span<DEFAULT_OBJECT_DATA, std::to_underlying(DEFAULT_OBJECT::kTotal)>
		{
			static const auto DEFAULT_OBJECT_DATA = REL::Relocation<std::array<RE::DEFAULT_OBJECT_DATA, std::to_underlying(DEFAULT_OBJECT::kTotal)>*>{ ID::DEFAULT_OBJECT_DATA::DefaultObjects };
			return { *DEFAULT_OBJECT_DATA };
		}

		// members
		const char* name;									 // 00
		REX::Enum<FormType, std::uint8_t> type;				 // 08
		std::uint32_t uniqueID;								 // 0C
		REX::Enum<DEFAULT_OBJECT_TYPE, std::int32_t> doType; // 10
		const char* newObjectName;							 // 18
	};
	static_assert(sizeof(DEFAULT_OBJECT_DATA) == 0x20);
}
