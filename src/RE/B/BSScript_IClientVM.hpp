#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) IClientVM
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IClientVM;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IClientVM;

		virtual ~IClientVM() = default; // 0x00

		// add
		virtual auto IsVMFrozen() const -> bool = 0; // 0x01
		virtual void PreSave() = 0;					 // 0x02

		GAME_HEAP_REDEFINE_NEW(IClientVM);
	};

	static_assert(sizeof(IClientVM) == 0x08);
}
