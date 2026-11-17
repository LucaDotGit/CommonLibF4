#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) ModConfirmCallback : public ExamineConfirmMenu::ICallback // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__ModConfirmCallback;
		inline static constexpr const auto& VTABLE = VTABLE::__ModConfirmCallback;

		explicit ModConfirmCallback(ExamineMenu* a_thisMenu) :
			ExamineConfirmMenu::ICallback(a_thisMenu)
		{
			REL::EmplaceVtable(this);
		}

		~ModConfirmCallback() override; // 0x00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 0x01
	};

	static_assert(sizeof(ModConfirmCallback) == 0x10);
}
