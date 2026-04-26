#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCount
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCount };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCount };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCount };

		ExtraCount()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCount() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		std::uint16_t count{ 0 }; // 18
	};
	static_assert(sizeof(ExtraCount) == 0x20);
}
