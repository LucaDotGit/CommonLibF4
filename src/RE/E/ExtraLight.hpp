#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class REFR_LIGHT;

	class __declspec(novtable) ExtraLight : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLight;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLight;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Light;

		ExtraLight() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLight() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		REFR_LIGHT* lightData{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraLight) == 0x20);
}
