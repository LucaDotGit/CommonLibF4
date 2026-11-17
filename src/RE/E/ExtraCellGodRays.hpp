#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellGodRays : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCellGodRays;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCellGodRays;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::CellGodRays;

		ExtraCellGodRays() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellGodRays() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSGodRays* godRays{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraCellGodRays) == 0x20);
}
