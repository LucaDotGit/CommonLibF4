#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BSISoundDescriptor
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSISoundDescriptor;
		inline static constexpr const auto& VTABLE = VTABLE::BSISoundDescriptor;

		class ExtraResolutionData;
		class Resolution;

		virtual ~BSISoundDescriptor() = default; // 0x00

		// add
		virtual auto DoResolve(Resolution& a_resolution, REX::Float32 a_distance, ExtraResolutionData* a_data) const
			-> bool = 0; // 0x01
		virtual auto DoMultiResolve(BSScrapArray<Resolution>& a_resolution, ExtraResolutionData* a_data) const
			-> bool = 0;														  // 0x02
		virtual auto DoAudibilityTest(REX::Float32 a_distance) const -> bool = 0; // 0x03
		virtual auto DoGetMultiResolves() const -> bool = 0;					  // 0x04

		GAME_HEAP_REDEFINE_NEW(BSISoundDescriptor);
	};

	static_assert(sizeof(BSISoundDescriptor) == 0x08);
}
