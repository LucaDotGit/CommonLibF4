#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) RepairFailureCallback : public ExamineConfirmMenu::ICallback // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__RepairFailureCallback;
		inline static constexpr const auto& VTABLE = VTABLE::__RepairFailureCallback;

		explicit RepairFailureCallback(ExamineMenu* a_thisMenu) :
			ExamineConfirmMenu::ICallback(a_thisMenu)
		{
			REL::EmplaceVtable(this);
		}

		~RepairFailureCallback() override; // 0x00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 0x01
	};

	static_assert(sizeof(RepairFailureCallback) == 0x10);
}
