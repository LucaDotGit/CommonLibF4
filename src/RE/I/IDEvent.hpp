#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/InputEvent.hpp"

namespace RE
{
	class __declspec(novtable) IDEvent : public InputEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IDEvent;
		inline static constexpr const auto& VTABLE = VTABLE::IDEvent;

		~IDEvent() override = default; // 0x00

		// override (InputEvent)
		auto HasIDCode() const -> bool override // 0x02
		{
			return true;
		}

		auto QUserEvent() const -> const BSFixedString& override; // 0x03

		[[nodiscard]]
		auto QDisabled() const noexcept -> bool
		{
			return disabled;
		}

		[[nodiscard]]
		auto QIDCode() const noexcept -> std::int32_t
		{
			return idCode;
		}

		[[nodiscard]]
		auto QRawUserEvent() const noexcept -> BSFixedString
		{
			return strUserEvent;
		}

		// members
		BSFixedString strUserEvent; // 0x28
		std::int32_t idCode{-1};	// 0x30
		bool disabled{false};		// 0x34
	};

	static_assert(sizeof(IDEvent) == 0x38);
}
