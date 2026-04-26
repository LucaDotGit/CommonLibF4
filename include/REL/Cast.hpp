#pragma once

#include "REX/Contract.hpp"

namespace REL
{
	class IId;

	template <class T, class U>
	[[nodiscard]] constexpr auto* AdjustPointer(U* a_ptr, std::ptrdiff_t a_offset) noexcept
	{
		const auto address = a_ptr ? std::bit_cast<std::uintptr_t>(a_ptr) + a_offset : 0;
		if constexpr (std::is_const_v<U> && std::is_volatile_v<U>) {
			return std::bit_cast<std::add_cv_t<T>*>(address);
		}
		else if constexpr (std::is_const_v<U>) {
			return std::bit_cast<std::add_const_t<T>*>(address);
		}
		else if constexpr (std::is_volatile_v<U>) {
			return std::bit_cast<std::add_volatile_t<T>*>(address);
		}
		else {
			return std::bit_cast<T*>(address);
		}
	}

	template <class T>
	[[nodiscard]] std::uintptr_t GetVtableAddress(const T& a_self) noexcept
		requires(std::is_polymorphic_v<T>)
	{
		return reinterpret_cast<const std::uintptr_t*>(std::addressof(a_self))[0];
	}

	template <class T>
	[[nodiscard]] std::uintptr_t& GetVtableRef(T& a_self) noexcept
		requires(std::is_polymorphic_v<T>)
	{
		return reinterpret_cast<std::uintptr_t*>(std::addressof(a_self))[0];
	}

	template <class T>
	[[nodiscard]] const std::uintptr_t& GetVtableRef(const T& a_self) noexcept
		requires(std::is_polymorphic_v<T>)
	{
		return reinterpret_cast<const std::uintptr_t*>(std::addressof(a_self))[0];
	}

	template <class T>
	void EmplaceVtable(T* a_self, std::uintptr_t a_vtableAddress) noexcept
		requires(std::is_polymorphic_v<T> &&
				 !std::is_const_v<T>)
	{
		if (!a_self) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto& vtableRef = GetVtableRef(*a_self);
		vtableRef = a_vtableAddress;
	}

	template <class T, class Id, std::size_t N>
	void EmplaceVtable(T* a_self, const std::array<Id, N>& a_vtable) noexcept
		requires(std::is_polymorphic_v<T> &&
				 !std::is_const_v<T> &&
				 std::derived_from<Id, REL::IId> &&
				 N > 0)
	{
		if (!a_self) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		EmplaceVtable(a_self, a_vtable[0].GetAddress());
	}

	template <class T>
	void EmplaceVtable(T* a_self) noexcept
		requires(std::is_polymorphic_v<T> &&
				 !std::is_const_v<T> &&
				 std::derived_from<typename decltype(T::VTABLE)::value_type, REL::IId> &&
				 std::tuple_size_v<decltype(T::VTABLE)> > 0)
	{
		if (!a_self) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		EmplaceVtable(a_self, T::VTABLE[0].GetAddress());
	}

	template <class T>
	void MemWriteZero(volatile T* a_ptr, std::size_t a_size = sizeof(T)) noexcept
		requires(!std::is_const_v<T>)
	{
		if (!a_ptr) {
			return;
		}

		std::fill_n(reinterpret_cast<volatile std::byte*>(a_ptr), a_size, static_cast<std::byte>(0));
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr T1 UnrestrictedCast(T2 a_from) //
		noexcept(std::is_nothrow_constructible_v<T1, T2> ||
				 !std::same_as<std::remove_cv_t<T2>, std::remove_cv_t<T1>>)
	{
		if constexpr (std::same_as<std::remove_cv_t<T2>, std::remove_cv_t<T1>>) {
			return T1{ a_from };
		}
		else if constexpr (std::is_reference_v<T2>) {
			return UnrestrictedCast<T1>(std::addressof(a_from));
		}
		else if constexpr (std::is_reference_v<T1>) {
			return *UnrestrictedCast<
				std::add_pointer_t<
					std::remove_reference_t<T1>>>(a_from);
		}
		else if constexpr (std::is_pointer_v<T2> &&
						   std::is_pointer_v<T1>) {
			return static_cast<T1>(
				const_cast<void*>(
					static_cast<const volatile void*>(a_from)));
		}
		else if constexpr ((std::is_pointer_v<T2> && std::is_integral_v<T1>) ||
						   (std::is_integral_v<T2> && std::is_pointer_v<T1>)) {
			return reinterpret_cast<T1>(a_from);
		}
		else {
			union
			{
				std::remove_cv_t<std::remove_reference_t<T2>> from;
				std::remove_cv_t<std::remove_reference_t<T1>> to;
			};

			from = std::forward<T2>(a_from);
			return to;
		}
	}
}