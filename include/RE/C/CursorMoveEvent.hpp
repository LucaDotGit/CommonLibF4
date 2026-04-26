#pragma once

#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) CursorMoveEvent
		: public IDEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::CursorMoveEvent };
		inline static constexpr auto VTABLE{ VTABLE::CursorMoveEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kCursorMove };

		~CursorMoveEvent() override = default; // 00

		// members
		std::int32_t cursorPosX{ 0 }; // 38
		std::int32_t cursorPosY{ 0 }; // 3C
	};
	static_assert(sizeof(CursorMoveEvent) == 0x40);

	extern template bool InputEvent::Is<CursorMoveEvent>() const noexcept;
	extern template bool InputEvent::IsNot<CursorMoveEvent>() const noexcept;

	extern template CursorMoveEvent* InputEvent::As() noexcept;
	extern template const CursorMoveEvent* InputEvent::As() const noexcept;
}
