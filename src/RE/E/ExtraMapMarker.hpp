#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class MapMarkerData;

	class __declspec(novtable) ExtraMapMarker : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraMapMarker;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraMapMarker;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::MapMarker;

		ExtraMapMarker() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraMapMarker() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		MapMarkerData* mapMarkerData{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraMapMarker) == 0x20);
}
