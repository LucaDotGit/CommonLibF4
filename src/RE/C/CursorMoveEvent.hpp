#pragma once

#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) CursorMoveEvent : public IDEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::CursorMoveEvent;
		inline static constexpr const auto& VTABLE = VTABLE::CursorMoveEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::CursorMove;

		~CursorMoveEvent() override = default; // 0x00

		// members
		std::int32_t cursorPosX{0}; // 0x38
		std::int32_t cursorPosY{0}; // 0x3C
	};

	static_assert(sizeof(CursorMoveEvent) == 0x40);
}
