#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraOwnership
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraOwnership };
		inline static constexpr auto VTABLE{ VTABLE::ExtraOwnership };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kOwnership };

		ExtraOwnership()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraOwnership() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESForm* owner{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraOwnership) == 0x20);
}
