#pragma once

namespace RE
{
	class BGSInventoryItem;
}

namespace RE::ActorUtils
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) ArmorRatingVisitorBase
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActorUtils__ArmorRatingVisitorBase;
		inline static constexpr const auto& VTABLE = VTABLE::ActorUtils__ArmorRatingVisitorBase;

		ArmorRatingVisitorBase()
		{
			REL::EmplaceVtable(this);
		}

		ArmorRatingVisitorBase(const Actor* a_actor, bool a_checkEquipped)
		{
			using FuncType = void (ArmorRatingVisitorBase::*)(const Actor*, bool);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorUtils::ArmorRatingVisitorBase::ctor);
			std::invoke(FUNC, this, a_actor, a_checkEquipped);
		}

		// add
		virtual auto ShouldProcess(TESBoundObject* a_object) -> bool; // 0x00 - { return true; }
		virtual void PostProcess(TESBoundObject* a_object);			  // 0x01 - { return; }

		[[nodiscard]]
		auto operator()(const BGSInventoryItem* a_item, std::uint32_t a_stackID) -> std::int64_t
		{
			using FuncType = decltype(&ArmorRatingVisitorBase::operator());
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorUtils::ArmorRatingVisitorBase::call_operator);
			return std::invoke(FUNC, this, a_item, a_stackID);
		}

		// members
		Actor* actor{nullptr};									 // 0x08
		REX::Float32 rating{static_cast<REX::Float32>(0.0)};	 // 0x10
		REX::Float32 armorPerks{static_cast<REX::Float32>(0.0)}; // 0x14
		bool checkEquipped{false};								 // 0x18
	};

	static_assert(sizeof(ArmorRatingVisitorBase) == 0x20);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
