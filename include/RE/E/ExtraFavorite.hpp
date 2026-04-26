#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraFavorite
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraFavorite };
		inline static constexpr auto VTABLE{ VTABLE::ExtraFavorite };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kFavorite };

		ExtraFavorite()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraFavorite() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		std::int8_t quickKeyIndex{ 0 }; // 18
	};
	static_assert(sizeof(ExtraFavorite) == 0x20);
}
