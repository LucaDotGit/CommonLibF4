#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) TESChildCell
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESChildCell;
		inline static constexpr const auto& VTABLE = VTABLE::TESChildCell;

		virtual ~TESChildCell() = default; // 0x00

		// add
		virtual auto GetSaveParentCell() const -> TESObjectCELL* = 0; // 0x01

		GAME_HEAP_REDEFINE_NEW(TESChildCell);
	};

	static_assert(sizeof(TESChildCell) == 0x08);
}
