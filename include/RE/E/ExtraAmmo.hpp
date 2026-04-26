#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraAmmo
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraAmmo };
		inline static constexpr auto VTABLE{ VTABLE::ExtraAmmo };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kAmmo };

		ExtraAmmo()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraAmmo() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		std::uint32_t count{ 0 }; // 18
	};
	static_assert(sizeof(ExtraAmmo) == 0x20);
}
