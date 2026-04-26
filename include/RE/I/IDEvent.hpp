#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/InputEvent.hpp"

namespace RE
{
	class __declspec(novtable) IDEvent
		: public InputEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IDEvent };
		inline static constexpr auto VTABLE{ VTABLE::IDEvent };

		~IDEvent() override = default; // 00

		// override (InputEvent)
		bool HasIDCode() const override { return true; }  // 02
		const BSFixedString& QUserEvent() const override; // 03

		[[nodiscard]] bool QDisabled() const noexcept { return disabled; }
		[[nodiscard]] std::uint32_t QIDCode() const noexcept { return idCode; }
		[[nodiscard]] const BSFixedString& QRawUserEvent() const noexcept { return strUserEvent; }

		// members
		BSFixedString strUserEvent; // 28
		std::int32_t idCode{ -1 };	// 30
		bool disabled{ false };		// 34
	};
	static_assert(sizeof(IDEvent) == 0x38);
}
