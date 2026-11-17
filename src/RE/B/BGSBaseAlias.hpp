#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/F/FormType.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::Impl
{
	template <class T>
	concept BGSBaseAliasConstraint = std::derived_from<T, BGSBaseAlias> &&
									 !REX::pointer<T> &&
									 !REX::reference<T> &&
									 std::same_as<std::remove_cv_t<decltype(T::ALIAS_TYPE)>, std::string_view>;
}

namespace RE
{
	class __declspec(novtable) BGSBaseAlias
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraReferenceHandles;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraReferenceHandles;
		inline static constexpr auto FORM_TYPE = FormType::BaseAlias;

		enum class Flags : std::uint32_t
		{
			None = 0,
			Reserves = 1 << 0,
			Optional = 1 << 1,
			QuestObject = 1 << 2,
			AllowReuse = 1 << 3,
			AllowDead = 1 << 4,
			LoadedOnly = 1 << 5,
			Essential = 1 << 6,
			AllowDisabled = 1 << 7,
			StoreName = 1 << 8,
			AllowReserved = 1 << 9,
			Protected = 1 << 10,
			ForcedFromAlias = 1 << 11,
			AllowDestroyed = 1 << 12,
			FindClosestRef = 1 << 13,
			UsesNames = 1 << 14,
			InitiallyDisabled = 1 << 15,
			AllowCleared = 1 << 16,
			ClearNameOnRemove = 1 << 17,
			ActorsOnly = 1 << 18,
			Transient = 1 << 19,
			ExternalLink = 1 << 20,
			NoPickPocket = 1 << 21,
			DataAlias = 1 << 22,
			Companion = 1 << 23,
			SceneOptional = 1 << 24
		};

		enum class FILL_TYPE : std::int16_t
		{
		};

		virtual ~BGSBaseAlias(); // 0x00

		// add
		virtual auto Load() -> bool = 0;						  // 0x01
		virtual void InitItem() = 0;							  // 0x02
		virtual auto QType() const -> const BSFixedString& = 0;	  // 0x03
		virtual auto QExternalQuest() const -> TESQuest* = 0;	  // 0x04
		virtual void ClearExternalQuest() = 0;					  // 0x05
		virtual void UpdateFromExternalAlias() const = 0;		  // 0x06
		virtual auto GetLinkedAlias() const -> BGSBaseAlias* = 0; // 0x07

		GAME_HEAP_REDEFINE_NEW(BGSBaseAlias);

		[[nodiscard]]
		auto GetFormType() const -> FormType;

		[[nodiscard]]
		auto GetAliasID() const -> std::uint32_t
		{
			return aliasID;
		}

		[[nodiscard]]
		auto GetOwningQuest() const -> TESQuest*
		{
			return owningQuest;
		}

		[[nodiscard]]
		auto Is(std::string_view a_type) const noexcept -> bool
		{
			return QType() == a_type;
		}

		template <class... Args>
		[[nodiscard]]
		auto Is(Args&&... a_args) const noexcept -> bool
			requires((std::is_convertible_v<Args, std::string_view> && ...))
		{
			return (Is(std::string_view(std::forward<Args>(a_args))) || ...);
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]]
		auto Is() const noexcept -> bool
		{
			return Is(T::ALIAS_TYPE);
		}

		[[nodiscard]]
		auto IsNot(std::string_view a_type) const noexcept -> bool
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]]
		auto IsNot(Args&&... a_args) const noexcept -> bool
			requires((std::is_convertible_v<Args, std::string_view> && ...))
		{
			return (IsNot(std::string_view(std::forward<Args>(a_args))) && ...);
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]]
		auto IsNot() const noexcept -> bool
		{
			return !Is(T::ALIAS_TYPE);
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]]
		auto As() noexcept -> T*
		{
			return Is(T::ALIAS_TYPE) ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]]
		auto As() const noexcept -> const T*
		{
			return Is(T::ALIAS_TYPE) ? static_cast<const T*>(this) : nullptr;
		}

		// members
		BSFixedString aliasName;					 // 0x08
		TESQuest* owningQuest;						 // 0x10
		std::uint32_t aliasID;						 // 0x18
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 0x1C
		REX::Enum<FILL_TYPE, std::int16_t> fillType; // 0x20
	};

	static_assert(sizeof(BGSBaseAlias) == 0x28);
}
