#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellGodRays
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellGodRays };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellGodRays };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellGodRays };

		ExtraCellGodRays()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellGodRays() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSGodRays* godRays{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellGodRays) == 0x20);
}
