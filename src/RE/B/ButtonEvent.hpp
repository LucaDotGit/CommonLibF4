#pragma once

#include "RE/I/IDEvent.hpp"

namespace RE
{
	enum class BS_BUTTON_CODE : std::int32_t;

	class __declspec(novtable) ButtonEvent : public IDEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ButtonEvent;
		inline static constexpr const auto& VTABLE = VTABLE::ButtonEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::Button;

		~ButtonEvent() override = default; // 0x00

		[[nodiscard]]
		auto QAnalogValue() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto QHeldDown(REX::Float32 a_heldDownSecs) const noexcept -> bool;
		[[nodiscard]]
		auto QHeldDown() const noexcept -> bool;
		[[nodiscard]]
		auto QHeldDownSecs() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto QJustPressed() const noexcept -> bool;
		[[nodiscard]]
		auto QPressed() const noexcept -> bool;
		[[nodiscard]]
		auto QReleased(REX::Float32 a_heldDownSecs) const noexcept -> bool;
		[[nodiscard]]
		auto QReleased() const noexcept -> bool;

		[[nodiscard]]
		auto GetBSButtonCode() const noexcept -> BS_BUTTON_CODE;

		// members
		REX::Float32 value{static_cast<REX::Float32>(0.0)};		   // 0x38
		REX::Float32 heldDownSecs{static_cast<REX::Float32>(0.0)}; // 0x3C
	};

	static_assert(sizeof(ButtonEvent) == 0x40);
}
