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
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerTreeVisitor };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerTreeVisitor };

		enum class VisitControl : std::int32_t;

		virtual ~BGSStoryManagerTreeVisitor(); // 00

		// add
		virtual VisitControl VisitBranchNode(BGSStoryManagerBranchNode& a_node) = 0;				// 01
		virtual VisitControl VisitQuestNode(BGSStoryManagerQuestNode& a_node, bool a_canReset) = 0; // 02
		virtual VisitControl VisitQuest(TESQuest& a_quest) = 0;										// 03
		virtual void Revert() = 0;																	// 04

		// members
		PeriodicUpdateTimer* timer;						   // 08
		std::int32_t currentCursorDepth;				   // 10
		BGSStoryManagerQuestNode* lastQuestParent;		   // 18
		BSTArray<BGSStoryManagerTreeForm*> cursorAncestry; // 20
		std::uint32_t queryID;							   // 38
	};
	static_assert(sizeof(BGSStoryManagerTreeVisitor) == 0x40);
}
