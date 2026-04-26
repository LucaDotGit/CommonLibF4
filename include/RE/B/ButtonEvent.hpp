#pragma once

#include "RE/I/IDEvent.hpp"

namespace RE
{
	enum class BS_BUTTON_CODE : std::int32_t;

	class __declspec(novtable) ButtonEvent
		: public IDEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ButtonEvent };
		inline static constexpr auto VTABLE{ VTABLE::ButtonEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kButton };

		~ButtonEvent() override = default; // 00

		[[nodiscard]] REX::Float32 QAnalogValue() const noexcept;
		[[nodiscard]] bool QHeldDown(REX::Float32 a_heldDownSecs) const noexcept;
		[[nodiscard]] bool QHeldDown() const noexcept;
		[[nodiscard]] REX::Float32 QHeldDownSecs() const noexcept;
		[[nodiscard]] bool QJustPressed() const noexcept;
		[[nodiscard]] bool QPressed() const noexcept;
		[[nodiscard]] bool QReleased(REX::Float32 a_heldDownSecs) const noexcept;
		[[nodiscard]] bool QReleased() const noexcept;

		[[nodiscard]] BS_BUTTON_CODE GetBSButtonCode() const noexcept;

		// members
		REX::Float32 value{ 0.0_f32 };		  // 38
		REX::Float32 heldDownSecs{ 0.0_f32 }; // 3C
	};
	static_assert(sizeof(ButtonEvent) == 0x40);

	extern template bool InputEvent::Is<ButtonEvent>() const noexcept;
	extern template bool InputEvent::IsNot<ButtonEvent>() const noexcept;

	extern template ButtonEvent* InputEvent::As() noexcept;
	extern template const ButtonEvent* InputEvent::As() const noexcept;
}
