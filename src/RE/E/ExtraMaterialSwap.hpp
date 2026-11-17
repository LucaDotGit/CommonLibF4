#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraMaterialSwap : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraMaterialSwap;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraMaterialSwap;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::MaterialSwap;

		ExtraMaterialSwap() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraMaterialSwap() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSMaterialSwap* swap{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraMaterialSwap) == 0x20);
}
