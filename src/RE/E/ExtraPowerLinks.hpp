#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) ExtraPowerLinks : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraPowerLinks;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraPowerLinks;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::PowerLinks;

		ExtraPowerLinks() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraPowerLinks() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		class Element
		{
		public:
			// members
			TESFormID formID;		// 0x00
			std::uint32_t linkType; // 0x04
		};

		static_assert(sizeof(Element) == 0x08);

		// members
		BSTArray<Element> powerLinks; // 0x18
	};

	static_assert(sizeof(ExtraPowerLinks) == 0x30);
}
