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
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::ENTRY_TYPE)>, EntryPointFunctionType>;
}

namespace RE
{
	class BGSPerkEntry;
	class TESFile;

	class __declspec(novtable) BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionData };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionData };

		virtual ~BGSEntryPointFunctionData(); // 00

		// add
		virtual EntryPointFunctionType GetType() const = 0;							 // 01
		virtual void InitItem(TESForm* a_form);										 // 02 - { return; }
		virtual void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry);			 // 03 - { return; }
		virtual BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const; // 04 - { return nullptr; }
		virtual bool LoadImpl(TESFile* a_file) = 0;									 // 05

		GAME_HEAP_REDEFINE_NEW(BGSEntryPointFunctionData);

		[[nodiscard]] bool Is(EntryPointFunctionType a_type) const noexcept
		{
			return GetType() == a_type;
		}

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept
			requires((std::same_as<Args, EntryPointFunctionType> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]] bool Is() const noexcept
		{
			return Is(T::ENTRY_TYPE);
		}

		[[nodiscard]] bool IsNot(EntryPointFunctionType a_type) const noexcept
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept
			requires((std::same_as<Args, EntryPointFunctionType> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]] bool IsNot() const noexcept
		{
			return IsNot(T::ENTRY_TYPE);
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]] T* As() noexcept
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BGSEntryPointFunctionDataConstraint T>
		[[nodiscard]] const T* As() const noexcept
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		BGSPerk* parent{ nullptr }; // 08
		std::uint16_t id{ 0 };		// 10
	};
	static_assert(sizeof(BGSEntryPointFunctionData) == 0x18);
}
