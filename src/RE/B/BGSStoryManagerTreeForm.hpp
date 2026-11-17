#pragma once

#include "RE/B/BGSStoryManagerTreeVisitor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class TESCondition;

	class __declspec(novtable) BGSStoryManagerTreeForm : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryManagerTreeForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryManagerTreeForm;
		inline static constexpr auto FORM_TYPE = FormType::None;

		~BGSStoryManagerTreeForm() override; // 0x00

		// add
		virtual auto QChildCount() const -> std::uint32_t;								// 0x4A - { return 0; }
		virtual auto GetChild(std::uint32_t a_index) const -> BGSStoryManagerTreeForm*; // 0x4B - { return nullptr; }
		virtual auto QConditions() -> TESCondition* = 0;								// 0x4C
		virtual auto AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor)
			-> BGSStoryManagerTreeVisitor::VisitControl = 0; // 0x4D

		// members
		std::uint32_t lastVisitorID; // 0x20
	};

	static_assert(sizeof(BGSStoryManagerTreeForm) == 0x28);
}
