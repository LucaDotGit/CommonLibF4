#pragma once

#include "REX/Concepts.hpp"

#if (NDEBUG == 0)
#define REX_CONSTEXPR_RELEASE_ONLY const
#define REX_CONSTEVAL_RELEASE_ONLY
#define REX_CONSTINIT_RELEASE_ONLY
#else
#define REX_CONSTEXPR_RELEASE_ONLY constexpr
#define REX_CONSTEVAL_RELEASE_ONLY consteval
#define REX_CONSTINIT_RELEASE_ONLY constinit
#endif

#if (_MSC_VER > 0l)
#define REX_NO_UNIQUE_ADDRESS msvc::no_unique_address
#else
#define REX_NO_UNIQUE_ADDRESS no_unique_address
#endif

#if (__clang__ == 1)
#define REX_NO_INLINE clang::noinline
#elif (__GNUC__ == 1)
#define REX_NO_INLINE gnu::noinline
#elif (_MSC_VER > 0l)
#define REX_NO_INLINE msvc::noinline
#else
#error "The current compiler is not supported."
#endif

#if (__clang__ == 1)
#define REX_ALWAYS_INLINE clang::always_inline
#elif (__GNUC__ == 1)
#define REX_ALWAYS_INLINE gnu::always_inline
#elif (_MSC_VER > 0l)
#define REX_ALWAYS_INLINE msvc::forceinline
#else
#error "The current compiler is not supported."
#endif

#if (__clang__ == 1)
#define REX_EXCEPTION_INLINE clang::always_inline
#elif (__GNUC__ == 1)
#define REX_EXCEPTION_INLINE gnu::always_inline
#elif (_MSC_VER > 0l)
#define REX_EXCEPTION_INLINE
#else
#error "The current compiler is not supported."
#endif

#define REX_STRING_CONCAT_IMPL(a_lhs, a_rhs) a_lhs##a_rhs
#define REX_STRING_CONCAT(a_lhs, a_rhs) REX_STRING_CONCAT_IMPL(a_lhs, a_rhs)

#define REX_STRING_LITERAL(a_type, a_value)                               \
	[]() consteval noexcept -> auto {                                     \
		if constexpr (std::same_as<a_type, char>) {                       \
			return a_value;                                               \
		}                                                                 \
		else if constexpr (std::same_as<a_type, wchar_t>) {               \
			return REX_STRING_CONCAT(L, a_value);                         \
		}                                                                 \
		else if constexpr (std::same_as<a_type, char8_t>) {               \
			return REX_STRING_CONCAT(u8, a_value);                        \
		}                                                                 \
		else if constexpr (std::same_as<a_type, char16_t>) {              \
			return REX_STRING_CONCAT(u, a_value);                         \
		}                                                                 \
		else if constexpr (std::same_as<a_type, char32_t>) {              \
			return REX_STRING_CONCAT(U, a_value);                         \
		}                                                                 \
		else {                                                            \
			static_assert(false, "The character type is not supported."); \
		}                                                                 \
	}()

#define REX_STATIC_FUNCTOR(a_lambda)                                                                      \
	inline static const auto REX_STRING_CONCAT(REX_STATIC_FUNCTOR_, __COUNTER__) = []() -> std::int32_t { \
		std::invoke(a_lambda);                                                                            \
		return 0;                                                                                         \
	}();

namespace REX
{
	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto GetDefaultValue() noexcept -> T
	{
		if constexpr (REX::arithmetic<T> || REX::enumeration<T> || REX::pointer<T>) {
			return static_cast<T>(0);
		}
		else if constexpr (std::is_default_constructible_v<T>) {
			return T();
		}
		else {
			static_assert(false, "The type does not have a default value.");
		}
	}
}
