#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraFavorite : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraFavorite;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraFavorite;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Favorite;

		ExtraFavorite() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraFavorite() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		std::int8_t quickKeyIndex{0}; // 0x18
	};

	static_assert(sizeof(ExtraFavorite) == 0x20);
}
