#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class REFR_LIGHT;

	class __declspec(novtable) ExtraLight
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraLight };
		inline static constexpr auto VTABLE{ VTABLE::ExtraLight };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kLight };

		ExtraLight()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLight() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		REFR_LIGHT* lightData{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraLight) == 0x20);
}
