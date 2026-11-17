#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) BaseBotConfirmCallback : public ExamineConfirmMenu::ICallback // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__BaseBotConfirmCallback;
		inline static constexpr const auto& VTABLE = VTABLE::__BaseBotConfirmCallback;

		explicit BaseBotConfirmCallback(ExamineMenu* a_thisMenu) :
			ExamineConfirmMenu::ICallback(a_thisMenu)
		{
			REL::EmplaceVtable(this);
		}

		~BaseBotConfirmCallback() override; // 0x00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 0x01
	};

	static_assert(sizeof(BaseBotConfirmCallback) == 0x10);
}
