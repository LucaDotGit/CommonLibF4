#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) ExtraPowerLinks
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraPowerLinks };
		inline static constexpr auto VTABLE{ VTABLE::ExtraPowerLinks };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kPowerLinks };

		ExtraPowerLinks()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraPowerLinks() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		class Element
		{
		public:
			// members
			TESFormID formID;		// 00
			std::uint32_t linkType; // 04
		};
		static_assert(sizeof(Element) == 0x08);

		// members
		BSTArray<Element> powerLinks; // 18
	};
	static_assert(sizeof(ExtraPowerLinks) == 0x30);
}
