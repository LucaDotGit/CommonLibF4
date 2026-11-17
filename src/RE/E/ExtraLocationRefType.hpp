#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLocationRefType : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLocationRefType;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLocationRefType;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Location;

		ExtraLocationRefType() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLocationRefType() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BSTArray<BGSLocationRefType*> locationRefTypes; // 0x18
	};

	static_assert(sizeof(ExtraLocationRefType) == 0x30);
}
