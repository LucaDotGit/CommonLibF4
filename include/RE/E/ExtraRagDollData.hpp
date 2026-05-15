#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/R/RagDollData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRagDollData
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraRagDollData };
		inline static constexpr auto VTABLE{ VTABLE::ExtraRagDollData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kRagDollData };

		ExtraRagDollData()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRagDollData() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		RagDollData* data{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraRagDollData) == 0x20);
}
