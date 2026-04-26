#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraScale
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraScale };
		inline static constexpr auto VTABLE{ VTABLE::ExtraScale };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kScale };

		ExtraScale()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraScale() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		REX::Float32 scale{ 0.0_f32 }; // 18
	};
	static_assert(sizeof(ExtraScale) == 0x20);
}
