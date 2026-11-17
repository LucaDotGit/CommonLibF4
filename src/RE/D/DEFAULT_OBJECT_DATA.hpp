#pragma once

#include "RE/D/DEFAULT_OBJECT.hpp"
#include "RE/D/DEFAULT_OBJECT_TYPE.hpp"
#include "RE/F/FormType.hpp"

namespace RE
{
	class DEFAULT_OBJECT_DATA
	{
	public:
		[[nodiscard]]
		static auto GetDefaultObjects() -> std::span<DEFAULT_OBJECT_DATA, std::to_underlying(DEFAULT_OBJECT::_Count)>
		{
			static const auto DEFAULT_OBJECT_DATA =
				REL::Relocation<std::array<RE::DEFAULT_OBJECT_DATA, std::to_underlying(DEFAULT_OBJECT::_Count)>*>{
					ID::DEFAULT_OBJECT_DATA::DefaultObjects
			};
			return {*DEFAULT_OBJECT_DATA};
		}

		// members
		const char* name;									 // 0x00
		REX::Enum<FormType, std::uint8_t> type;				 // 0x08
		std::uint32_t uniqueID;								 // 0x0C
		REX::Enum<DEFAULT_OBJECT_TYPE, std::int32_t> doType; // 0x10
		const char* newObjectName;							 // 0x18
	};

	static_assert(sizeof(DEFAULT_OBJECT_DATA) == 0x20);
}
