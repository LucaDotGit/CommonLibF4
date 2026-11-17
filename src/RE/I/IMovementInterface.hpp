#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) IMovementInterface
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMovementInterface;
		inline static constexpr const auto& VTABLE = VTABLE::IMovementInterface;

		virtual ~IMovementInterface() = default; // 0x00

		GAME_HEAP_REDEFINE_NEW(IMovementInterface);
	};

	static_assert(sizeof(IMovementInterface) == 0x08);
}
