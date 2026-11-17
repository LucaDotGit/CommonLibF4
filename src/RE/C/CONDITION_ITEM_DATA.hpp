#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/F/FUNCTION_DATA.hpp"

namespace RE
{
	enum class CONDITIONITEMOBJECT : std::int32_t;

	class CONDITION_ITEM_DATA
	{
	public:
		// members
		union
		{
		public:
			TESGlobal* global;
			REX::Float32 value;
		}; // 0x00

		ObjectRefHandle runOnRef;							// 0x08
		std::uint32_t dataID;								// 0x0C
		FUNCTION_DATA functionData;							// 0x10
		std::uint8_t compareOr			   : 1;				// 0x28:0
		std::uint8_t aliasParams		   : 1;				// 0x28:1
		std::uint8_t valueIsGlobal		   : 1;				// 0x28:2
		std::uint8_t packDataParams		   : 1;				// 0x28:3
		std::uint8_t swapsSubjectAndTarget : 1;				// 0x28:4
		std::uint8_t condition			   : 3;				// 0x28:5
		REX::Enum<CONDITIONITEMOBJECT, std::int8_t> object; // 0x29
	};

	static_assert(sizeof(CONDITION_ITEM_DATA) == 0x30);
}
