#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraReferenceHandles : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraReferenceHandles;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraReferenceHandles;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::ReferenceHandles;

		ExtraReferenceHandles() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraReferenceHandles() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		ObjectRefHandle originalRef;  // 0x18
		ObjectRefHandle containerRef; // 0x1C
	};

	static_assert(sizeof(ExtraReferenceHandles) == 0x20);
}
