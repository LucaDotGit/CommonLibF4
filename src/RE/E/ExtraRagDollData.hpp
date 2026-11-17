#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/R/RagDollData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRagDollData : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraRagDollData;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraRagDollData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::RagDollData;

		ExtraRagDollData() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRagDollData() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		RagDollData* data{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraRagDollData) == 0x20);
}
