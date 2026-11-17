#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraUniqueID : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraUniqueID;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraUniqueID;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::UniqueID;

		ExtraUniqueID() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraUniqueID() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		ContainerID uniqueID{0}; // 0x18
		TESFormID baseID{0};	 // 0x1C
	};

	static_assert(sizeof(ExtraUniqueID) == 0x20);
}
