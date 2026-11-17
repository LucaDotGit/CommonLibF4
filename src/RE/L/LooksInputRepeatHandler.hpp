#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) LooksInputRepeatHandler : public BSInputEventUser // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::LooksInputRepeatHandler;
		inline static constexpr const auto& VTABLE = VTABLE::LooksInputRepeatHandler;

		~LooksInputRepeatHandler() override; // 0x00

		// members
		std::array<REX::Float32, 3> repeatTimerArray; // 0x10
		REX::Float32 longRepeatRate;				  // 0x1C
		REX::Float32 shortRepeatRate;				  // 0x20
		std::array<BSFixedString*, 3> lastEventArray; // 0x28
		std::array<bool, 3> processInputEventArray;	  // 0x40
		bool sculptMode;							  // 0x43
		bool featureMode;							  // 0x44
		bool bumpersRepeat;							  // 0x45
	};

	static_assert(sizeof(LooksInputRepeatHandler) == 0x48);
}
