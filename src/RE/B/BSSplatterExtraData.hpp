#pragma once

#include "RE/B/BSSplatterData.hpp"
#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) BSSplatterExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSSplatterExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::BSSplatterExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSSplatterExtraData;

		BSSplatterExtraData() :
			NiExtraData(GetExtraName())
		{
			REL::EmplaceVtable(this);
		}

		explicit BSSplatterExtraData(const BSSplatterData& a_splatterData) :
			NiExtraData(GetExtraName()),
			splatterData(a_splatterData)
		{
			REL::EmplaceVtable(this);
		}

		~BSSplatterExtraData() override; // 0x00

		[[nodiscard]]
		static auto GetExtraName() -> const BSFixedString&
		{
			static const auto EXTRA_NAME = BSFixedString("SPD"sv);
			return EXTRA_NAME;
		}

		// members
		BSSplatterData splatterData{}; // 0x18
	};

	static_assert(sizeof(BSSplatterExtraData) == 0x28);
}
