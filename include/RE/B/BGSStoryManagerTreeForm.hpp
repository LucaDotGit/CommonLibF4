#pragma once

#include "RE/B/BGSStoryManagerTreeVisitor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class TESCondition;

	class __declspec(novtable) BGSStoryManagerTreeForm
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerTreeForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerTreeForm };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		~BGSStoryManagerTreeForm() override; // 00

		// add
		virtual std::uint32_t QChildCount() const;																   // 4A - { return 0; }
		virtual BGSStoryManagerTreeForm* GetChild(std::uint32_t a_index) const;									   // 4B - { return nullptr; }
		virtual TESCondition* QConditions() = 0;																   // 4C
		virtual BGSStoryManagerTreeVisitor::VisitControl AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor) = 0; // 4D

		// members
		std::uint32_t lastVisitorID; // 20
	};
	static_assert(sizeof(BGSStoryManagerTreeForm) == 0x28);
}
