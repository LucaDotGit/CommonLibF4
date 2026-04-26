#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLocation
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraLocation };
		inline static constexpr auto VTABLE{ VTABLE::ExtraLocation };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kLocation };

		ExtraLocation()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLocation() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSLocation* location{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraLocation) == 0x20);
}
