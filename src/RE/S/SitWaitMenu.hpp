#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) SitWaitMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SitWaitMenu;
		inline static constexpr const auto& VTABLE = VTABLE::SitWaitMenu;
		inline static constexpr auto MENU_NAME = "SitWaitMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::SitWaitMenu;

		~SitWaitMenu() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;														// 0x01
		void MapCodeObjectFunctions() override;															// 0x02
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override;						// 0x03
		void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest) override; // 0x09

		static void OnEnterFurniture(ObjectRefHandle a_refHandle)
		{
			using FuncType = decltype(&SitWaitMenu::OnEnterFurniture);
			static const auto FUNC = REL::Relocation<FuncType>(ID::SitWaitMenu::OnEnterFurniture);
			std::invoke(FUNC, a_refHandle);
		}

		static void OnExitFurniture()
		{
			using FuncType = decltype(&SitWaitMenu::OnExitFurniture);
			static const auto FUNC = REL::Relocation<FuncType>(ID::SitWaitMenu::OnExitFurniture);
			std::invoke(FUNC);
		}

		// members
		BSTArray<BSFixedString> overridingMenus; // 0xE0
	};

	static_assert(sizeof(SitWaitMenu) == 0xF8);
}
