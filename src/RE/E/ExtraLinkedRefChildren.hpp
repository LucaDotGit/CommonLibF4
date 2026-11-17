#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLinkedRefChildren : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLinkedRefChildren;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLinkedRefChildren;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::LinkedRefChildren;

		class LinkedRefChild
		{
		public:
			// members
			BGSKeyword* keyword; // 0x00
			ObjectRefHandle ref; // 0x08
		};

		static_assert(sizeof(LinkedRefChild) == 0x10);

		ExtraLinkedRefChildren() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLinkedRefChildren() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_rhs) const -> bool override; // 0x01

		// members
		BSTSmallArray<LinkedRefChild, 1> linkedChildren; // 0x018
	};

	static_assert(sizeof(ExtraLinkedRefChildren) == 0x38);
}
