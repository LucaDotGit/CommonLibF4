#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadius : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraRadius;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraRadius;
		inline static constexpr auto TYPE = EXTRA_DATA_TYPE::Radius;

		// members
		REX::Float32 radius; // 0x18
	};

	static_assert(sizeof(ExtraRadius) == 0x20);
}
