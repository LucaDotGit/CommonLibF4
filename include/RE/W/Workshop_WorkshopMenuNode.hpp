#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"

#include "msvc/memory.hpp"

namespace RE::Workshop
{
	class WorkshopMenuNode
	{
	public:
		GAME_HEAP_REDEFINE_NEW(WorkshopMenuNode);

		bool FindAndSetSelectedNode(std::uint16_t a_row, std::uint32_t a_crc, std::uint16_t& a_outRow)
		{
			using FuncType = decltype(&WorkshopMenuNode::FindAndSetSelectedNode);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::WorkshopMenuNode::FindAndSetSelectedNode };
			return std::invoke(FUNC, this, a_row, a_crc, a_outRow);
		}

		// members
		BGSKeyword* filterKeyword;											 // 00
		WorkshopMenuNode* parent;											 // 08
		BSTArray<msvc::unique_ptr<WorkshopMenuNode>> children;				 // 10
		BGSConstructibleObject* recipe;										 // 28
		BGSConstructibleObject* sourceFormListRecipe;						 // 30
		TESForm* form;														 // 38
		std::uint32_t uniqueID{ std::numeric_limits<std::uint32_t>::max() }; // 40
		std::uint16_t row;													 // 44
		std::uint16_t column;												 // 46
		bool selected;														 // 48
	};
	static_assert(sizeof(WorkshopMenuNode) == 0x50);
}
