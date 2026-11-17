#pragma once

#include "REX/Concepts.hpp"
#include "REX/Macros.hpp"

namespace REX
{
	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto ToSigned(T a_value) noexcept
		requires(REX::unsigned_integer<T>)
	{
		return static_cast<std::make_signed_t<T>>(a_value);
	}

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto ToUnsigned(T a_value) noexcept
		requires(REX::signed_integer<T>)
	{
		return static_cast<std::make_unsigned_t<T>>(a_value);
	}

	template <class To, class From>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto CheckedReinterpretCast(From* a_value) noexcept -> To
		requires(
			REX::pointer<To> &&
			(sizeof(From) == sizeof(std::remove_pointer_t<To>)) &&
			(alignof(From) == alignof(std::remove_pointer_t<To>)) &&
			(requires { reinterpret_cast<To&>(a_value); }))
	{
		return reinterpret_cast<To>(a_value);
	}

	template <class To, class From>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto CheckedReinterpretCast(From& a_value) noexcept -> To
		requires(
			REX::reference<To> &&
			(sizeof(From) == sizeof(std::remove_reference_t<To>)) &&
			(alignof(From) == alignof(std::remove_reference_t<To>)) &&
			(requires { reinterpret_cast<To&>(a_value); }))
	{
		return reinterpret_cast<To>(a_value);
	}

	template <class T1, class T2>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto UnrestrictedCast(T2 a_from)
		noexcept(std::is_nothrow_constructible_v<T1, T2> || !std::same_as<std::remove_cv_t<T2>, std::remove_cv_t<T1>>)
			-> T1
	{
		if constexpr (std::same_as<std::remove_cv_t<T2>, std::remove_cv_t<T1>>) {
			return T1(a_from);
		}
		else if constexpr (REX::reference<T2>) {
			return UnrestrictedCast<T1>(std::addressof(a_from));
		}
		else if constexpr (REX::reference<T1>) {
			return *UnrestrictedCast<std::add_pointer_t<std::remove_reference_t<T1>>>(a_from);
		}
		else if constexpr (REX::pointer<T2> && REX::pointer<T1>) {
			return static_cast<T1>(const_cast<void*>(static_cast<const volatile void*>(a_from)));
		}
		else if constexpr ((REX::pointer<T2> && std::is_integral_v<T1>) ||
						   (std::is_integral_v<T2> && REX::pointer<T1>)) {
			return reinterpret_cast<T1>(a_from);
		}
		else {
			union
			{
			public:
				std::remove_cvref_t<T2> from;
				std::remove_cvref_t<T1> to;
			};

			from = std::forward<T2>(a_from);
			return to;
		}
	}
}
