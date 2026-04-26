#pragma once

#include "RE/B/BGSInventoryItem.hpp"

namespace RE
{
	class BGSObjectInstanceExtra;

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) ApplyChangesFunctor
		: public BGSInventoryItem::StackDataWriteFunctor // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::__ApplyChangesFunctor };
		inline static constexpr auto VTABLE{ VTABLE::__ApplyChangesFunctor };

		ApplyChangesFunctor()
		{
			REL::EmplaceVtable(this);
		}

		// override (BGSInventoryItem::StackDataWriteFunctor)
		void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 01

		// members
		BGSObjectInstanceExtra* extra{ nullptr }; // 10
		TESBoundObject* object{ nullptr };		  // 18
		BGSMod::Attachment::Mod* mod{ nullptr };  // 20
		std::uint8_t rank{ 0 };					  // 28
		bool remove{ false };					  // 29
		bool excludeTemporary{ false };			  // 2A
		std::int8_t favoriteIndex{ 0 };			  // 2B
	};
	static_assert(sizeof(ApplyChangesFunctor) == 0x30);
}
