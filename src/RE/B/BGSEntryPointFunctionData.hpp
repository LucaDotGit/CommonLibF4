#pragma once

#include "RE/E/EntryPointFunctionType.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSEntryPointFunctionData;
}

namespace RE::Impl
{
	template <class T>
	concept BGSEntryPointFunctionDataConstraint =
		std::derived_from<T, BGSEntryPointFunctionData> &&
		!REX::pointer<T> &&
		!REX::reference<T> &&
		std::same_as<std::remove_cv_t<decltype(T::ENTRY_TYPE)>, EntryPointFunctionType>;
}

namespace RE
{
	class BGSPerkEntry;
	class TESFile;

	class __declspec(novtable) BGSEntryPointFunctionData
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEntryPointFunctionData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEntryPointFunctionData;

		virtual ~BGSEntryPointFunctionData(); // 0x00

		// add
		virtual auto GetType() const -> EntryPointFunctionType = 0;		 // 0x01
		virtual void InitItem(TESForm* a_form);							 // 0x02 - { return; }
		virtual void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry); // 0x03 - { return; }
		virtual auto CheckConvert(std::uint8_t a_arg01) const
			-> BGSEntryPointFunctionData*;					// 0x04 - { return nullptr; }
		virtual auto LoadImpl(TESFile* a_file) -> bool = 0; // 0x05

		GAME_HEAP_REDEFINE_NEW(BGSEntryPointFunctionData);

		[[nodiscard]]
		auto Is(EntryPointFunctionType a_type) const noexcept -> bool
		{
			return GetType() == a_type;
		}

		template <class... Args>
		[[nodiscard]]
		auto Is(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, EntryPointFunctionType> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]]
		auto Is() const noexcept -> bool
		{
			return Is(T::ENTRY_TYPE);
		}

		[[nodiscard]]
		auto IsNot(EntryPointFunctionType a_type) const noexcept -> bool
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]]
		auto IsNot(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, EntryPointFunctionType> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]]
		auto IsNot() const noexcept -> bool
		{
			return IsNot(T::ENTRY_TYPE);
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]]
		auto As() noexcept -> T*
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]]
		auto As() const noexcept -> const T*
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		BGSPerk* parent{nullptr}; // 0x08
		std::uint16_t id{0};	  // 0x10
	};

	static_assert(sizeof(BGSEntryPointFunctionData) == 0x18);
}
