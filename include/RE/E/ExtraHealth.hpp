#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraHealth
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraHealth };
		inline static constexpr auto VTABLE{ VTABLE::ExtraHealth };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kHealth };

		ExtraHealth()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraHealth() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		REX::Float32 health{ 0.0_f32 }; // 18
	};
	static_assert(sizeof(ExtraHealth) == 0x20);
}
