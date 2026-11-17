#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class HUDComponentBase;
	class RequestHUDModesEvent;
	class UserEventEnabledEvent;

	class __declspec(novtable) HUDMenu :
		public GameMenuBase,						// 0x000
		public BSTEventSink<UserEventEnabledEvent>, // 0x0E0
		public BSTEventSink<RequestHUDModesEvent>	// 0x0E8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDMenu;
		inline static constexpr const auto& VTABLE = VTABLE::HUDMenu;
		inline static constexpr auto MENU_NAME = "HUDMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::HUDMenu;

		enum class ShowMenuState : std::int32_t
		{
			Constructed = 0,
			Shown = 1,
			Hidden = 2,
			ReshowOnDestructor = 3
		};

		~HUDMenu() override; // 0x00

		void SetHUDColor()
		{
			using FuncType = decltype(&HUDMenu::SetHUDColor);
			static const auto FUNC = REL::Relocation<FuncType>(ID::HUDMenu::SetHUDColor);
			std::invoke(FUNC, this);
		}

		// members
		BSTSmallArray<msvc::unique_ptr<HUDComponentBase>, 32> hudObjects; // 0x0F0
		BSTArray<HUDModeType> hudModes;									  // 0x200
		REX::Enum<ShowMenuState, std::int32_t> hudShowMenuState;		  // 0x218
	};

	static_assert(sizeof(HUDMenu) == 0x220);
}
