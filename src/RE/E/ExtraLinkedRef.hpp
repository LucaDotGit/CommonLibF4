#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLinkedRef : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLinkedRef;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLinkedRef;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::LinkedRef;

		class LinkedRef
		{
		public:
			// members
			BGSKeyword* keyword; // 0x00
			TESObjectREFR* ref;	 // 0x08
		};

		static_assert(sizeof(LinkedRef) == 0x10);

		ExtraLinkedRef() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLinkedRef() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BSTSmallArray<LinkedRef, 1> linkedRefs; // 0x018
		bool transientRefs{false};				// 0x038
	};

	static_assert(sizeof(ExtraLinkedRef) == 0x40);
}
