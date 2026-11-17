#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSStoryManagerBranchNode;
	class BGSStoryManagerQuestNode;
	class BGSStoryManagerTreeForm;
	class PeriodicUpdateTimer;

	class __declspec(novtable) BGSStoryManagerTreeVisitor
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryManagerTreeVisitor;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryManagerTreeVisitor;

		enum class VisitControl : std::int32_t;

		virtual ~BGSStoryManagerTreeVisitor(); // 0x00

		// add
		virtual auto VisitBranchNode(BGSStoryManagerBranchNode& a_node) -> VisitControl = 0;				// 0x01
		virtual auto VisitQuestNode(BGSStoryManagerQuestNode& a_node, bool a_canReset) -> VisitControl = 0; // 0x02
		virtual auto VisitQuest(TESQuest& a_quest) -> VisitControl = 0;										// 0x03
		virtual void Revert() = 0;																			// 0x04

		// members
		PeriodicUpdateTimer* timer;						   // 0x08
		std::int32_t currentCursorDepth;				   // 0x10
		BGSStoryManagerQuestNode* lastQuestParent;		   // 0x18
		BSTArray<BGSStoryManagerTreeForm*> cursorAncestry; // 0x20
		std::uint32_t queryID;							   // 0x38
	};

	static_assert(sizeof(BGSStoryManagerTreeVisitor) == 0x40);
}
