#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BGSMod::Property
{
	enum class OP : std::int32_t;
	enum class TYPE : std::int32_t;

	class Mod
	{
	public:
		union IntFloatPair
		{
		public:
			// members
			std::int32_t int32{0};
			REX::Float32 float32;
		};

		static_assert(sizeof(IntFloatPair) == 0x04);

		class MinMax
		{
		public:
			// members
			IntFloatPair min; // 0x00
			IntFloatPair max; // 0x04
		};

		static_assert(sizeof(MinMax) == 0x08);

		class FormValuePair
		{
		public:
			// members
			TESFormID formID;	// 0x00
			REX::Float32 value; // 0x04
		};

		static_assert(sizeof(FormValuePair) == 0x08);

		union Data
		{
		public:
			// members
			BSFixedString string;
			TESForm* form{nullptr};
			MinMax minMax;
			FormValuePair formValuePair;
		};

		static_assert(sizeof(Data) == 0x08);

		GAME_HEAP_REDEFINE_NEW(Mod);

		// members
		Data data;				   // 0x00
		std::uint32_t target : 11; // 0x08:00
		OP op				 : 2;  // 0x08:11
		TYPE type			 : 3;  // 0x08:13
		std::int16_t step;		   // 0x0C
	};

	static_assert(sizeof(Mod) == 0x10);
}
