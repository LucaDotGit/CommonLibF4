#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCharge
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCharge };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCharge };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCharge };

		ExtraCharge()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCharge() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		REX::Float32 charge{ 0.0_f32 }; // 18
	};
	static_assert(sizeof(ExtraCharge) == 0x20);
}
