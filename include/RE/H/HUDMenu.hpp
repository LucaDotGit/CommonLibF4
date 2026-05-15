#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class HUDComponentBase;
	class RequestHUDModesEvent;
	class UserEventEnabledEvent;

	class __declspec(novtable) HUDMenu
		: public GameMenuBase,						  // 000
		  public BSTEventSink<UserEventEnabledEvent>, // 0E0
		  public BSTEventSink<RequestHUDModesEvent>	  // 0E8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDMenu };
		inline static constexpr auto VTABLE{ VTABLE::HUDMenu };
		inline static constexpr auto MENU_NAME{ "HUDMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kHUDMenu };

		enum class ShowMenuState : std::int32_t
		{
			kConstructed = 0,
			kShown = 1,
			kHidden = 2,
			kReshowOnDestructor = 3
		};

		~HUDMenu() override; // 00

		void SetHUDColor()
		{
			using FuncType = decltype(&HUDMenu::SetHUDColor);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::HUDMenu::SetHUDColor };
			std::invoke(FUNC, this);
		}

		// members
		BSTSmallArray<msvc::unique_ptr<HUDComponentBase>, 32> hudObjects; // 0F0
		BSTArray<HUDModeType> hudModes;									  // 200
		REX::Enum<ShowMenuState, std::int32_t> hudShowMenuState;		  // 218
	};
	static_assert(sizeof(HUDMenu) == 0x220);
}
