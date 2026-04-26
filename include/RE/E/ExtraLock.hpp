#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class REFR_LOCK;

	class __declspec(novtable) ExtraLock
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraLock };
		inline static constexpr auto VTABLE{ VTABLE::ExtraLock };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kLock };

		ExtraLock()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLock() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		REFR_LOCK* lock{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraLock) == 0x20);
}
