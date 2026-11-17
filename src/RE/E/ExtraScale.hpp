#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraScale : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraScale;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraScale;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Scale;

		ExtraScale() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraScale() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		REX::Float32 scale{static_cast<REX::Float32>(0.0)}; // 0x18
	};

	static_assert(sizeof(ExtraScale) == 0x20);
}
