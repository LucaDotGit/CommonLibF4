#pragma once

#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) CursorMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::CursorMenu;
		inline static constexpr const auto& VTABLE = VTABLE::CursorMenu;
		inline static constexpr auto MENU_NAME = "CursorMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::CursorMenu;

		~CursorMenu() override; // 0x00

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> cursor; // 0xE0
	};

	static_assert(sizeof(CursorMenu) == 0xE8);
}
