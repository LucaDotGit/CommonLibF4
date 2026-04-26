#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/G/GameMenuBase.hpp"

namespace RE
{
	class __declspec(novtable) SitWaitMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SitWaitMenu };
		inline static constexpr auto VTABLE{ VTABLE::SitWaitMenu };
		inline static constexpr auto MENU_NAME{ "SitWaitMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kSitWaitMenu };

		~SitWaitMenu() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;														// 01
		void MapCodeObjectFunctions() override;															// 02
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;								// 03
		void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest) override; // 09

		static void OnEnterFurniture(ObjectRefHandle a_refHandle)
		{
			using FuncType = decltype(&SitWaitMenu::OnEnterFurniture);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::SitWaitMenu::OnEnterFurniture };
			FUNC(a_refHandle);
		}

		static void OnExitFurniture()
		{
			using FuncType = decltype(&SitWaitMenu::OnExitFurniture);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::SitWaitMenu::OnExitFurniture };
			FUNC();
		}

		// members
		BSTArray<BSFixedString> overridingMenus; // E0
	};
	static_assert(sizeof(SitWaitMenu) == 0xF8);
}
