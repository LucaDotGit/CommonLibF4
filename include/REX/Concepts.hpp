#pragma once

namespace REX
{
	template <class T>
	concept nullable =
		std::is_null_pointer_v<T>;

	template <class T>
	concept boolean =
		std::same_as<T, bool>;

	template <class T>
	concept integer =
		std::is_integral_v<T> &&
		!std::same_as<T, bool>;

	template <class T>
	concept signed_integer =
		integer<T> &&
		std::is_signed_v<T>;

	template <class T>
	concept unsigned_integer =
		integer<T> &&
		std::is_unsigned_v<T>;

	template <class T>
	concept floating_point =
		std::is_floating_point_v<T>;

	template <class T>
	concept number =
		integer<T> ||
		floating_point<T>;

	template <class T>
	concept enumeration =
		std::is_enum_v<T>;

	template <class T>
	concept character =
		std::same_as<T, char> ||
		std::same_as<T, wchar_t> ||
		std::same_as<T, char8_t> ||
		std::same_as<T, char16_t> ||
		std::same_as<T, char32_t>;

	template <class T>
	concept win32_character =
		std::same_as<T, char> ||
		std::same_as<T, wchar_t>;

	template <class T>
	concept narrow_character =
		std::same_as<T, char> ||
		std::same_as<T, char8_t>;

	template <class T>
	concept wide_character =
		std::same_as<T, wchar_t> ||
		std::same_as<T, char16_t>;

	template <class T>
	concept u8_character =
		std::same_as<T, char> ||
		std::same_as<T, char8_t>;

	template <class T>
	concept u16_character =
		std::same_as<T, wchar_t> ||
		std::same_as<T, char16_t>;

	template <class T>
	concept u32_character =
		std::same_as<T, char32_t>;

	template <class T>
	concept equality_comparable =
		requires(T a_lhs, T a_rhs) {
			{ a_lhs == a_rhs } -> std::same_as<bool>;
			{ a_lhs != a_rhs } -> std::same_as<bool>;
		};

	template <class T>
	concept nothrow_equality_comparable =
		requires(T a_lhs, T a_rhs) {
			{ a_lhs == a_rhs } noexcept -> std::same_as<bool>;
			{ a_lhs != a_rhs } noexcept -> std::same_as<bool>;
		};

	template <class T, class U>
	concept equality_comparable_with =
		requires(T a_lhs, U a_rhs) {
			{ a_lhs == a_rhs } -> std::same_as<bool>;
			{ a_rhs == a_lhs } -> std::same_as<bool>;
			{ a_lhs != a_rhs } -> std::same_as<bool>;
			{ a_rhs != a_lhs } -> std::same_as<bool>;
		};

	template <class T, class U>
	concept nothrow_equality_comparable_with =
		requires(T a_lhs, U a_rhs) {
			{ a_lhs == a_rhs } noexcept -> std::same_as<bool>;
			{ a_rhs == a_lhs } noexcept -> std::same_as<bool>;
			{ a_lhs != a_rhs } noexcept -> std::same_as<bool>;
			{ a_rhs != a_lhs } noexcept -> std::same_as<bool>;
		};

	template <class T>
	concept three_way_comparable =
		requires(T a_lhs, T a_rhs) {
			{ a_lhs <=> a_rhs } -> std::convertible_to<std::partial_ordering>;
		};

	template <class T>
	concept nothrow_three_way_comparable =
		requires(T a_lhs, T a_rhs) {
			{ a_lhs <=> a_rhs } noexcept -> std::convertible_to<std::partial_ordering>;
		};

	template <class T, class U>
	concept three_way_comparable_with =
		requires(T a_lhs, U a_rhs) {
			{ a_lhs <=> a_rhs } -> std::convertible_to<std::partial_ordering>;
			{ a_rhs <=> a_lhs } -> std::convertible_to<std::partial_ordering>;
		};

	template <class T, class U>
	concept nothrow_three_way_comparable_with =
		requires(T a_lhs, U a_rhs) {
			{ a_lhs <=> a_rhs } noexcept -> std::convertible_to<std::partial_ordering>;
			{ a_rhs <=> a_lhs } noexcept -> std::convertible_to<std::partial_ordering>;
		};

	template <class T>
	concept hashable =
		requires(T a_key) {
			{ std::invoke(std::hash<std::decay_t<T>>(), a_key) } -> std::same_as<std::size_t>;
		};

	template <class T>
	concept nothrow_hashable =
		requires(T a_key) {
			{ std::invoke(std::hash<std::decay_t<T>>(), a_key) } noexcept -> std::same_as<std::size_t>;
		};

	template <class T>
	concept addressable =
		std::is_pointer_v<T> ||
		requires(T a_value) {
			{ &a_value } -> std::same_as<T*>;
		};

	template <class T>
	concept nothrow_addressable =
		std::is_pointer_v<T> ||
		requires(T a_value) {
			{ &a_value } noexcept -> std::same_as<T*>;
		};

	template <class T>
	concept dereferencable =
		std::is_pointer_v<T> ||
		requires(T a_value) {
			{ *a_value };
		};

	template <class T>
	concept nothrow_dereferencable =
		std::is_pointer_v<T> ||
		requires(T a_value) {
			{ *a_value } noexcept;
		};

	template <class T>
	concept arrowable =
		std::is_pointer_v<T> ||
		requires(T a_value) {
			{ a_value.operator->() };
		};

	template <class T>
	concept nothrow_arrowable =
		std::is_pointer_v<T> ||
		requires(T a_value) {
			{ a_value.operator->() } noexcept;
		};

	template <class T>
	concept trivially_readable =
		std::is_trivially_copyable_v<T> &&
		std::is_standard_layout_v<T>;

	template <class T>
	concept trivially_writable =
		std::is_trivially_copyable_v<T> &&
		std::is_standard_layout_v<T> &&
		!std::is_const_v<T>;

	template <class T>
	using remove_cvpr_t =
		std::remove_cv_t<
			std::remove_pointer_t<
				std::remove_reference_t<T>>>;

	template <number>
	struct buffer_traits
	{
		using buffer_size = std::false_type;
	};

	template <>
	struct buffer_traits<std::int8_t>
	{
		// -128 in base 2: "-10000000" (9 chars)
		using buffer_size = std::integral_constant<std::size_t, 9>;
	};

	template <>
	struct buffer_traits<std::uint8_t>
	{
		// 255 in base 2: "11111111" (8 chars)
		using buffer_size = std::integral_constant<std::size_t, 8>;
	};

	template <>
	struct buffer_traits<std::int16_t>
	{
		// -32768 in base 2: "-1000000000000000" (17 chars)
		using buffer_size = std::integral_constant<std::size_t, 17>;
	};

	template <>
	struct buffer_traits<std::uint16_t>
	{
		// 65535 in base 2: "1111111111111111" (16 chars)
		using buffer_size = std::integral_constant<std::size_t, 16>;
	};

	template <>
	struct buffer_traits<std::int32_t>
	{
		// -2147483648 in base 2: "-10000000000000000000000000000000" (33 chars)
		using buffer_size = std::integral_constant<std::size_t, 33>;
	};

	template <>
	struct buffer_traits<std::uint32_t>
	{
		// 4294967295 in base 2: "11111111111111111111111111111111" (32 chars)
		using buffer_size = std::integral_constant<std::size_t, 32>;
	};

	template <>
	struct buffer_traits<std::int64_t>
	{
		// -9223372036854775808 in base 2: "-1000000000000000000000000000000000000000000000000000000000000000" (65 chars)
		using buffer_size = std::integral_constant<std::size_t, 65>;
	};

	template <>
	struct buffer_traits<std::uint64_t>
	{
		// 18446744073709551615 in base 2: "1111111111111111111111111111111111111111111111111111111111111111" (64 chars)
		using buffer_size = std::integral_constant<std::size_t, 64>;
	};

	template <>
	struct buffer_traits<REX::Float32>
	{
		// Source: https://www.reddit.com/r/cpp_questions/comments/1i8zo3f/comment/m98k576
		using buffer_size = std::integral_constant<std::size_t, 48>;
	};

	template <>
	struct buffer_traits<REX::Float64>
	{
		// Source: https://www.reddit.com/r/cpp_questions/comments/1i8zo3f/comment/m98k576
		using buffer_size = std::integral_constant<std::size_t, 327>;
	};

	template <>
	struct buffer_traits<REX::Float128>
	{
#if _MSC_VER > 0l
		static_assert(sizeof(REX::Float64) == sizeof(REX::Float128));

		using buffer_size = std::integral_constant<std::size_t, buffer_traits<REX::Float64>::buffer_size::value>;
#else
		static_assert(sizeof(REX::Float64) < sizeof(REX::Float128));

		// Source: https://www.reddit.com/r/cpp_questions/comments/1i8zo3f/comment/m98k576
		using buffer_size = std::integral_constant<std::size_t, 4954>;
#endif
	};
}
