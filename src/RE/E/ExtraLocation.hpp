#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLocation : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLocation;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLocation;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Location;

		ExtraLocation() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLocation() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSLocation* location{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraLocation) == 0x20);
}
