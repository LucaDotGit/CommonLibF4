#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/F/FormType.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::Impl
{
	template <class T>
	concept BGSBaseAliasConstraint =
		std::derived_from<T, BGSBaseAlias> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::ALIAS_TYPE)>, std::string_view>;
}

namespace RE
{
	class __declspec(novtable) BGSBaseAlias
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraReferenceHandles };
		inline static constexpr auto VTABLE{ VTABLE::ExtraReferenceHandles };
		inline static constexpr auto FORM_TYPE{ FormType::kBaseAlias };

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kReserves = 1 << 0,
			kOptional = 1 << 1,
			kQuestObject = 1 << 2,
			kAllowReuse = 1 << 3,
			kAllowDead = 1 << 4,
			kLoadedOnly = 1 << 5,
			kEssential = 1 << 6,
			kAllowDisabled = 1 << 7,
			kStoreName = 1 << 8,
			kAllowReserved = 1 << 9,
			kProtected = 1 << 10,
			kForcedFromAlias = 1 << 11,
			kAllowDestroyed = 1 << 12,
			kFindClosestRef = 1 << 13,
			kUsesNames = 1 << 14,
			kInitiallyDisabled = 1 << 15,
			kAllowCleared = 1 << 16,
			kClearNameOnRemove = 1 << 17,
			kActorsOnly = 1 << 18,
			kTransient = 1 << 19,
			kExternalLink = 1 << 20,
			kNoPickPocket = 1 << 21,
			kDataAlias = 1 << 22,
			kCompanion = 1 << 23,
			kSceneOptional = 1 << 24
		};

		enum class FILL_TYPE : std::int16_t
		{
		};

		virtual ~BGSBaseAlias(); // 00

		// add
		virtual bool Load() = 0;						  // 01
		virtual void InitItem() = 0;					  // 02
		virtual const BSFixedString& QType() const = 0;	  // 03
		virtual TESQuest* QExternalQuest() const = 0;	  // 04
		virtual void ClearExternalQuest() = 0;			  // 05
		virtual void UpdateFromExternalAlias() const = 0; // 06
		virtual BGSBaseAlias* GetLinkedAlias() const = 0; // 07

		GAME_HEAP_REDEFINE_NEW(BGSBaseAlias);

		[[nodiscard]] FormType GetFormType() const;

		[[nodiscard]] std::uint32_t GetAliasID() const { return aliasID; }
		[[nodiscard]] TESQuest* GetOwningQuest() const { return owningQuest; }

		[[nodiscard]] bool Is(std::string_view a_type) const noexcept
		{
			return QType() == a_type;
		}

		template <class... Args>
		[[nodiscard]] bool Is(Args&&... a_args) const noexcept
			requires((std::is_convertible_v<Args, std::string_view> && ...))
		{
			return (Is(static_cast<std::string_view>(std::forward<Args>(a_args))) || ...);
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]] bool Is() const noexcept
		{
			return Is(T::ALIAS_TYPE);
		}

		[[nodiscard]] bool IsNot(std::string_view a_type) const noexcept
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]] bool IsNot(Args&&... a_args) const noexcept
			requires((std::is_convertible_v<Args, std::string_view> && ...))
		{
			return (IsNot(static_cast<std::string_view>(std::forward<Args>(a_args))) && ...);
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]] bool IsNot() const noexcept
		{
			return !Is(T::ALIAS_TYPE);
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]] T* As() noexcept
		{
			return Is(T::ALIAS_TYPE) ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BGSBaseAliasConstraint T>
		[[nodiscard]] const T* As() const noexcept
		{
			return Is(T::ALIAS_TYPE) ? static_cast<const T*>(this) : nullptr;
		}

		// members
		BSFixedString aliasName;					 // 08
		TESQuest* owningQuest;						 // 10
		std::uint32_t aliasID;						 // 18
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 1C
		REX::Enum<FILL_TYPE, std::int16_t> fillType; // 20
	};
	static_assert(sizeof(BGSBaseAlias) == 0x28);
}
