#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) BaseBotConfirmCallback
		: public ExamineConfirmMenu::ICallback // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::__BaseBotConfirmCallback };
		inline static constexpr auto VTABLE{ VTABLE::__BaseBotConfirmCallback };

		explicit BaseBotConfirmCallback(ExamineMenu* a_thisMenu)
			: ExamineConfirmMenu::ICallback(a_thisMenu)
		{
			REL::EmplaceVtable(this);
		}

		~BaseBotConfirmCallback() override; // 00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 01
	};
	static_assert(sizeof(BaseBotConfirmCallback) == 0x10);
}
