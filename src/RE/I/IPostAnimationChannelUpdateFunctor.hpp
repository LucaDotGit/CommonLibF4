#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) IPostAnimationChannelUpdateFunctor
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IPostAnimationChannelUpdateFunctor;
		inline static constexpr const auto& VTABLE = VTABLE::IPostAnimationChannelUpdateFunctor;

		virtual ~IPostAnimationChannelUpdateFunctor() = default; // 0x00

		// add
		virtual void DoPostAnimationChannelUpdate() = 0; // 0x01

		GAME_HEAP_REDEFINE_NEW(IPostAnimationChannelUpdateFunctor);
	};

	static_assert(sizeof(IPostAnimationChannelUpdateFunctor) == 0x08);
}
