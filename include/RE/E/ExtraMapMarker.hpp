#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class MapMarkerData;

	class __declspec(novtable) ExtraMapMarker
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraMapMarker };
		inline static constexpr auto VTABLE{ VTABLE::ExtraMapMarker };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kMapMarker };

		ExtraMapMarker()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraMapMarker() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		MapMarkerData* mapMarkerData{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraMapMarker) == 0x20);
}
