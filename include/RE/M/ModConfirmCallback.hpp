#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) ModConfirmCallback
		: public ExamineConfirmMenu::ICallback // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::__ModConfirmCallback };
		inline static constexpr auto VTABLE{ VTABLE::__ModConfirmCallback };

		explicit ModConfirmCallback(ExamineMenu* a_thisMenu)
			: ExamineConfirmMenu::ICallback(a_thisMenu)
		{
			REL::EmplaceVtable(this);
		}

		~ModConfirmCallback() override; // 00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 01
	};
	static_assert(sizeof(ModConfirmCallback) == 0x10);
}
