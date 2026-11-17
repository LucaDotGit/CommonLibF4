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
	concept BGSPerkEntryConstraint = std::derived_from<T, BGSPerkEntry> &&
									 !REX::pointer<T> &&
									 !REX::reference<T> &&
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
		inline static constexpr const auto& RTTI = RTTI::BGSPerkEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPerkEntry;

		// add
		virtual auto GetFunction() -> BGSEntryPoint::ENTRY_POINT;			// 0x00 - { return 0; }
		virtual auto GetFunctionData() const -> BGSEntryPointFunctionData*; // 0x01 - { return nullptr; }

		virtual ~BGSPerkEntry(); // 0x02

		virtual auto GetType() const -> PERK_ENTRY_TYPE = 0; // 0x03
		virtual void ClearData();							 // 0x04 - { return; }
		virtual void InitItem(TESFile* a_owner);			 // 0x05 - { return; }
		virtual auto Load(TESFile* a_file) -> bool;			 // 0x06 - { return true; }
		virtual void SetParent(BGSPerk* a_parent);			 // 0x07 - { return; }
		virtual auto GetID() const -> std::uint16_t;		 // 0x08 - { return 0xFFFF; }
		virtual void ApplyPerkEntry(Actor* a_actor) = 0;	 // 0x09
		virtual void RemovePerkEntry(Actor* a_actor) = 0;	 // 0x0A

		GAME_HEAP_REDEFINE_NEW(BGSPerkEntry);

		[[nodiscard]]
		auto Is(PERK_ENTRY_TYPE a_type) const noexcept -> bool
		{
			return GetType() == a_type;
		}

		template <class... Args>
		[[nodiscard]]
		auto Is(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, PERK_ENTRY_TYPE> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]]
		auto Is() const noexcept -> bool
		{
			return Is(T::ENTRY_TYPE);
		}

		[[nodiscard]]
		auto IsNot(PERK_ENTRY_TYPE a_type) const noexcept -> bool
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]]
		auto IsNot(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, PERK_ENTRY_TYPE> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]]
		auto IsNot() const noexcept -> bool
		{
			return IsNot(T::ENTRY_TYPE);
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]]
		auto As() noexcept -> T*
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BGSPerkEntryConstraint T>
		[[nodiscard]]
		auto As() const noexcept -> const T*
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		std::uint8_t rank{0};	  // 0x08
		std::uint8_t priority{0}; // 0x09
	};

	static_assert(sizeof(BGSPerkEntry) == 0x10);
}
