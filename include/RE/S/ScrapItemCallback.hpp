#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"

namespace RE
{
	class __declspec(novtable) ScrapItemCallback
		: public ExamineConfirmMenu::ICallback // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::__ScrapItemCallback };
		inline static constexpr auto VTABLE{ VTABLE::__ScrapItemCallback };

		ScrapItemCallback(ExamineMenu* a_thisMenu, std::uint32_t a_itemIndex)
			: ExamineConfirmMenu::ICallback(a_thisMenu),
			  itemIndex(a_itemIndex)
		{
			REL::EmplaceVtable(this);
		}

		~ScrapItemCallback() override; // 00

		// override (ExamineConfirmMenu::ICallback)
		void OnAccept() override; // 01

		// members
		std::uint32_t itemIndex; // 10
	};
	static_assert(sizeof(ScrapItemCallback) == 0x18);
}
