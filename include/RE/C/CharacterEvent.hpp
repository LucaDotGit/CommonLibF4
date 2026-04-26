#pragma once

#include "RE/I/InputEvent.hpp"

namespace RE
{
	class __declspec(novtable) CharacterEvent
		: public InputEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::CharacterEvent };
		inline static constexpr auto VTABLE{ VTABLE::CharacterEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kChar };

		~CharacterEvent() override = default; // 00

		// members
		std::uint32_t charCode{ 0 }; // 28
	};
	static_assert(sizeof(CharacterEvent) == 0x30);

	extern template bool InputEvent::Is<CharacterEvent>() const noexcept;
	extern template bool InputEvent::IsNot<CharacterEvent>() const noexcept;

	extern template CharacterEvent* InputEvent::As() noexcept;
	extern template const CharacterEvent* InputEvent::As() const noexcept;
}
