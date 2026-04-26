#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraMaterialSwap
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraMaterialSwap };
		inline static constexpr auto VTABLE{ VTABLE::ExtraMaterialSwap };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kMaterialSwap };

		ExtraMaterialSwap()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraMaterialSwap() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSMaterialSwap* swap{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraMaterialSwap) == 0x20);
}
