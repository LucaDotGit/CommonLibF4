#pragma once

#include "RE/I/InputEvent.hpp"

namespace RE
{
	class __declspec(novtable) CharacterEvent : public InputEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::CharacterEvent;
		inline static constexpr const auto& VTABLE = VTABLE::CharacterEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::Char;

		~CharacterEvent() override = default; // 0x00

		// members
		std::uint32_t charCode{0}; // 0x28
	};

	static_assert(sizeof(CharacterEvent) == 0x30);
}
