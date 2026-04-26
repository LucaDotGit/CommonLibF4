#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BSISoundDescriptor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSISoundDescriptor };
		inline static constexpr auto VTABLE{ VTABLE::BSISoundDescriptor };

		class ExtraResolutionData;
		class Resolution;

		virtual ~BSISoundDescriptor() = default; // 00

		// add
		virtual bool DoResolve(Resolution& a_resolution, REX::Float32 a_distance, ExtraResolutionData* a_data) const = 0; // 01
		virtual bool DoMultiResolve(BSScrapArray<Resolution>& a_resolution, ExtraResolutionData* a_data) const = 0;		  // 02
		virtual bool DoAudibilityTest(REX::Float32 a_distance) const = 0;												  // 03
		virtual bool DoGetMultiResolves() const = 0;																	  // 04
	};
	static_assert(sizeof(BSISoundDescriptor) == 0x08);
}
