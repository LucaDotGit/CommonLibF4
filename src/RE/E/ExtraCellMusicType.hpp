#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellMusicType : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCellMusicType;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCellMusicType;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::CellMusicType;

		ExtraCellMusicType() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellMusicType() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSMusicType* musicType{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraCellMusicType) == 0x20);

}
