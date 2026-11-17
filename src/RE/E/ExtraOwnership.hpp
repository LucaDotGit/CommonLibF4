#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraOwnership : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraOwnership;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraOwnership;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Ownership;

		ExtraOwnership() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraOwnership() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESForm* owner{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraOwnership) == 0x20);
}
