#pragma once

#include "RE/D/DIRECTION_VAL.hpp"
#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) ThumbstickEvent
		: public IDEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ThumbstickEvent };
		inline static constexpr auto VTABLE{ VTABLE::ThumbstickEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kThumbstick };

		enum class THUMBSTICK_ID : std::int32_t
		{
			kLeft = 11,
			kRight = 12
		};

		~ThumbstickEvent() override = default; // 00

		// members
		REX::Float32 xValue{ 0.0_f32 };				   // 38
		REX::Float32 yValue{ 0.0_f32 };				   // 3C
		DIRECTION_VAL prevDir{ DIRECTION_VAL::kNone }; // 40
		DIRECTION_VAL currDir{ DIRECTION_VAL::kNone }; // 44
	};
	static_assert(sizeof(ThumbstickEvent) == 0x48);

	extern template bool InputEvent::Is<ThumbstickEvent>() const noexcept;
	extern template bool InputEvent::IsNot<ThumbstickEvent>() const noexcept;

	extern template ThumbstickEvent* InputEvent::As() noexcept;
	extern template const ThumbstickEvent* InputEvent::As() const noexcept;
}
