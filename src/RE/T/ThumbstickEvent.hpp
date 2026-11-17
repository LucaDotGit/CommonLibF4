#pragma once

#include "RE/D/DIRECTION_VAL.hpp"
#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) ThumbstickEvent : public IDEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ThumbstickEvent;
		inline static constexpr const auto& VTABLE = VTABLE::ThumbstickEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::Thumbstick;

		enum class THUMBSTICK_ID : std::int32_t
		{
			Left = 11,
			Right = 12
		};

		~ThumbstickEvent() override = default; // 0x00

		// members
		REX::Float32 xValue{static_cast<REX::Float32>(0.0)}; // 0x38
		REX::Float32 yValue{static_cast<REX::Float32>(0.0)}; // 0x3C
		DIRECTION_VAL prevDir{DIRECTION_VAL::None};			 // 0x40
		DIRECTION_VAL currDir{DIRECTION_VAL::None};			 // 0x44
	};

	static_assert(sizeof(ThumbstickEvent) == 0x48);
}
