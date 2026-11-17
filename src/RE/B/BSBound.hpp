#pragma once

#include "RE/N/NiExtraData.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class __declspec(novtable) BSBound : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSBound;
		inline static constexpr const auto& VTABLE = VTABLE::BSBound;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSBound;

		BSBound() :
			NiExtraData(GetExtraName())
		{
			REL::EmplaceVtable(this);
		}

		BSBound(const NiPoint3& a_center, const NiPoint3& a_extents) :
			NiExtraData(GetExtraName()),
			center(a_center),
			extents(a_extents)
		{
			REL::EmplaceVtable(this);
		}

		~BSBound() override; // 0x00

		[[nodiscard]]
		static auto GetExtraName() -> const BSFixedString&
		{
			static const auto EXTRA_NAME = BSFixedString("BBX"sv);
			return EXTRA_NAME;
		}

		// members
		NiPoint3 center;  // 0x18
		NiPoint3 extents; // 0x24
	};

	static_assert(sizeof(BSBound) == 0x30);
}
