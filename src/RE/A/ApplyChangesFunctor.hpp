#pragma once

#include "RE/B/BGSInventoryItem.hpp"

namespace RE
{
	class BGSObjectInstanceExtra;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) ApplyChangesFunctor : public BGSInventoryItem::StackDataWriteFunctor // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__ApplyChangesFunctor;
		inline static constexpr const auto& VTABLE = VTABLE::__ApplyChangesFunctor;

		ApplyChangesFunctor()
		{
			REL::EmplaceVtable(this);
		}

		// override (BGSInventoryItem::StackDataWriteFunctor)
		void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 0x00

		// members
		BGSObjectInstanceExtra* extra{nullptr}; // 0x10
		TESBoundObject* object{nullptr};		// 0x18
		BGSMod::Attachment::Mod* mod{nullptr};	// 0x20
		std::uint8_t rank{0};					// 0x28
		bool remove{false};						// 0x29
		bool excludeTemporary{false};			// 0x2A
		std::int8_t favoriteIndex{0};			// 0x2B
	};

	static_assert(sizeof(ApplyChangesFunctor) == 0x30);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
