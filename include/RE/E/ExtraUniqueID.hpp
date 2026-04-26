#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraUniqueID
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraUniqueID };
		inline static constexpr auto VTABLE{ VTABLE::ExtraUniqueID };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kUniqueID };

		ExtraUniqueID()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraUniqueID() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		ContainerID uniqueID{ 0 }; // 18
		TESFormID baseID{ 0 };	   // 1C
	};
	static_assert(sizeof(ExtraUniqueID) == 0x20);
}
