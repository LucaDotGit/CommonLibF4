#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellMusicType
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellMusicType };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellMusicType };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellMusicType };

		ExtraCellMusicType()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellMusicType() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSMusicType* musicType{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellMusicType) == 0x20);

}
