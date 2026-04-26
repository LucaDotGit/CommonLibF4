#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/P/PERK_ENTRY_TYPE.hpp"

namespace RE
{
	class BGSPerkEntry;
}

namespace RE::Impl
{
	template <class T>
	concept BGSPerkEntryConstraint =
		std::derived_from<T, BGSPerkEntry> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::ENTRY_TYPE)>, PERK_ENTRY_TYPE>;
}

namespace RE::BGSEntryPoint
{
	enum class ENTRY_POINT : std::int32_t;
}

namespace RE
{
	class BGSEntryPointFunctionData;
	class TESFile;

	class __declspec(novtable) BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSPerkEntry };

		// add
		virtual BGSEntryPoint::ENTRY_POINT GetFunction();			// 00 - { return 0; }
		virtual BGSEntryPointFunctionData* GetFunctionData() const; // 01 - { return nullptr; }

		virtual ~BGSPerkEntry(); // 02

		virtual PERK_ENTRY_TYPE GetType() const = 0;	  // 03
		virtual void ClearData();						  // 04 - { return; }
		virtual void InitItem(TESFile* a_owner);		  // 05 - { return; }
		virtual bool Load(TESFile* a_file);				  // 06 - { return true; }
		virtual void SetParent(BGSPerk* a_parent);		  // 07 - { return; }
		virtual std::uint16_t GetID() const;			  // 08 - { return 0xFFFF; }
		virtual void ApplyPerkEntry(Actor* a_actor) = 0;  // 09
		virtual void RemovePerkEntry(Actor* a_actor) = 0; // 0A

		GAME_HEAP_REDEFINE_NEW(BGSPerkEntry);

		[[nodiscard]] bool Is(PERK_ENTRY_TYPE a_type) const noexcept
		{
			return GetType() == a_type;
		}

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept
			requires((std::same_as<Args, PERK_ENTRY_TYPE> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]] bool Is() const noexcept
		{
			return Is(T::ENTRY_TYPE);
		}

		[[nodiscard]] bool IsNot(PERK_ENTRY_TYPE a_type) const noexcept
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept
			requires((std::same_as<Args, PERK_ENTRY_TYPE> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]] bool IsNot() const noexcept
		{
			return IsNot(T::ENTRY_TYPE);
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]] T* As() noexcept
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]] const T* As() const noexcept
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		std::uint8_t rank{ 0 };		// 08
		std::uint8_t priority{ 0 }; // 09
	};
	static_assert(sizeof(BGSPerkEntry) == 0x10);
}
