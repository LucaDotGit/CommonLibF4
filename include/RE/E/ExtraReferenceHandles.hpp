#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraReferenceHandles
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraReferenceHandles };
		inline static constexpr auto VTABLE{ VTABLE::ExtraReferenceHandles };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kReferenceHandles };

		ExtraReferenceHandles()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraReferenceHandles() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		ObjectRefHandle originalRef;  // 18
		ObjectRefHandle containerRef; // 1C
	};
	static_assert(sizeof(ExtraReferenceHandles) == 0x20);
}
