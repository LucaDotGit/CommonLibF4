#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) ScrapItemCallback : public ExamineConfirmMenu::ICallback // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__ScrapItemCallback;
		inline static constexpr const auto& VTABLE = VTABLE::__ScrapItemCallback;

		ScrapItemCallback(ExamineMenu* a_thisMenu, std::uint32_t a_itemIndex) :
			ExamineConfirmMenu::ICallback(a_thisMenu),
			itemIndex(a_itemIndex)
		{
			REL::EmplaceVtable(this);
		}

		~ScrapItemCallback() override; // 0x00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 0x01

		// members
		std::uint32_t itemIndex; // 0x10
	};

	static_assert(sizeof(ScrapItemCallback) == 0x18);
}
