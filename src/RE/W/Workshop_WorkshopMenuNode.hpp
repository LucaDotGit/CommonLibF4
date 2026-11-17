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

		auto FindAndSetSelectedNode(std::uint16_t a_row, std::uint32_t a_crc, std::uint16_t& a_outRow) -> bool
		{
			using FuncType = decltype(&WorkshopMenuNode::FindAndSetSelectedNode);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::WorkshopMenuNode::FindAndSetSelectedNode);
			return std::invoke(FUNC, this, a_row, a_crc, a_outRow);
		}

		// members
		BGSKeyword* filterKeyword;										   // 0x00
		WorkshopMenuNode* parent;										   // 0x08
		BSTArray<msvc::unique_ptr<WorkshopMenuNode>> children;			   // 0x10
		BGSConstructibleObject* recipe;									   // 0x28
		BGSConstructibleObject* sourceFormListRecipe;					   // 0x30
		TESForm* form;													   // 0x38
		std::uint32_t uniqueID{std::numeric_limits<std::uint32_t>::max()}; // 0x40
		std::uint16_t row;												   // 0x44
		std::uint16_t column;											   // 0x46
		bool selected;													   // 0x48
	};

	static_assert(sizeof(WorkshopMenuNode) == 0x50);
}
