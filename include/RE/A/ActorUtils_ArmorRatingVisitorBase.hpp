#pragma once

namespace RE
{
	class BGSInventoryItem;
}

namespace RE::ActorUtils
{
	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) ArmorRatingVisitorBase
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorUtils__ArmorRatingVisitorBase };
		inline static constexpr auto VTABLE{ VTABLE::ActorUtils__ArmorRatingVisitorBase };

		ArmorRatingVisitorBase()
		{
			REL::EmplaceVtable(this);
		}

		ArmorRatingVisitorBase(const Actor* a_actor, bool a_checkEquipped)
		{
			using FuncType = void (ArmorRatingVisitorBase::*)(const Actor*, bool);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ActorUtils::ArmorRatingVisitorBase::ctor };
			FUNC(this, a_actor, a_checkEquipped);
		}

		// add
		virtual bool ShouldProcess(TESBoundObject* a_object); // 00 - { return true; }
		virtual void PostProcess(TESBoundObject* a_object);	  // 01 - { return; }

		[[nodiscard]] std::int64_t operator()(const BGSInventoryItem* a_item, std::uint32_t a_stackID)
		{
			using FuncType = decltype(&ArmorRatingVisitorBase::operator());
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ActorUtils::ArmorRatingVisitorBase::call_operator };
			return std::invoke(FUNC, this, a_item, a_stackID);
		}

		// members
		Actor* actor{ nullptr };			// 08
		REX::Float32 rating{ 0.0_f32 };		// 10
		REX::Float32 armorPerks{ 0.0_f32 }; // 14
		bool checkEquipped{ false };		// 18
	};
	static_assert(sizeof(ArmorRatingVisitorBase) == 0x20);
}
