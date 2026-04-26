#pragma once

#include "RE/G/GameMenuBase.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) CursorMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::CursorMenu };
		inline static constexpr auto VTABLE{ VTABLE::CursorMenu };
		inline static constexpr auto MENU_NAME{ "CursorMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kCursorMenu };

		~CursorMenu() override; // 00

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> cursor; // E0
	};
	static_assert(sizeof(CursorMenu) == 0xE8);
}
