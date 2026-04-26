#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BGSMod::Property
{
	enum class OP : std::int32_t;
	enum class TYPE : std::int32_t;

	class Mod // id == 1
	{
	public:
		union IntFloatPair
		{
		public:
			~IntFloatPair() noexcept { return; }

			// members
			std::int32_t int32{ 0 };
			REX::Float32 float32;
		};
		static_assert(sizeof(IntFloatPair) == 0x04);

		class MinMax
		{
		public:
			// members
			IntFloatPair min; // 00
			IntFloatPair max; // 04
		};
		static_assert(sizeof(MinMax) == 0x08);

		class FormValuePair
		{
		public:
			// members
			TESFormID formID;	// 00
			REX::Float32 value; // 04
		};
		static_assert(sizeof(FormValuePair) == 0x08);

		union Data
		{
		public:
			~Data() noexcept { return; }

			// members
			BSFixedString string;
			TESForm* form{ nullptr };
			MinMax minMax;
			FormValuePair formValuePair;
		};
		static_assert(sizeof(Data) == 0x08);

		GAME_HEAP_REDEFINE_NEW(Mod);

		// members
		Data data;				   // 00
		std::uint32_t target : 11; // 08:00
		OP op				 : 2;  // 08:11
		TYPE type			 : 3;  // 08:13
		std::int16_t step;		   // 0C
	};
	static_assert(sizeof(Mod) == 0x10);
}
