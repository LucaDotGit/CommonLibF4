#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/E/ExtraLightDataStruct.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLightData
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraLightData };
		inline static constexpr auto VTABLE{ VTABLE::ExtraLightData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kLightData };

		ExtraLightData()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLightData() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		ExtraLightDataStruct data; // 18
	};
	static_assert(sizeof(ExtraLightData) == 0x30);

}
