#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellAcousticSpace : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCellAcousticSpace;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCellAcousticSpace;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::CellAcousticSpace;

		ExtraCellAcousticSpace() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellAcousticSpace() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSAcousticSpace* acousticSpace{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraCellAcousticSpace) == 0x20);
}
