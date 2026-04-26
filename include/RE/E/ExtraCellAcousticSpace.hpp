#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellAcousticSpace
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellAcousticSpace };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellAcousticSpace };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellAcousticSpace };

		ExtraCellAcousticSpace()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellAcousticSpace() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSAcousticSpace* acousticSpace{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellAcousticSpace) == 0x20);
}
