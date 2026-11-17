#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCount : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCount;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCount;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Count;

		ExtraCount() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCount() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		std::uint16_t count{0}; // 0x18
	};

	static_assert(sizeof(ExtraCount) == 0x20);
}
