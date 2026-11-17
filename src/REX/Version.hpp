#pragma once

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Conversion.hpp"
#include "REX/Error.hpp"
#include "REX/Hashing.hpp"

namespace REX
{
	class Version final
	{
	public:
		static const Version MIN;
		static const Version MAX;

		using value_type = std::uint16_t;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		inline static constexpr auto MAX_SIZE = static_cast<size_type>(4);
		inline static constexpr auto MAX_STRING_SIZE = REX::buffer_traits<value_type>::buffer_size::value * MAX_SIZE;

		template <REX::win32_character CharT>
		inline static constexpr auto DEFAULT_SEPARATOR = static_cast<CharT>('.');

		constexpr Version() noexcept = default;
		constexpr ~Version() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr Version(value_type a_major) noexcept :
			_major(a_major)
		{
		}

		constexpr Version(value_type a_major, value_type a_minor) noexcept :
			_major(a_major),
			_minor(a_minor)
		{
		}

		constexpr Version(value_type a_major, value_type a_minor, value_type a_patch) noexcept :
			_major(a_major),
			_minor(a_minor),
			_patch(a_patch)
		{
		}

		constexpr Version(value_type a_major, value_type a_minor, value_type a_patch, value_type a_build) noexcept :
			_major(a_major),
			_minor(a_minor),
			_patch(a_patch),
			_build(a_build)
		{
		}

		constexpr explicit Version(std::array<value_type, MAX_SIZE> a_version) noexcept :
			_major(a_version[0]),
			_minor(a_version[1]),
			_patch(a_version[2]),
			_build(a_version[3])
		{
		}

		constexpr explicit Version(std::span<const value_type, MAX_SIZE> a_version) noexcept :
			_major(a_version[0]),
			_minor(a_version[1]),
			_patch(a_version[2]),
			_build(a_version[3])
		{
		}

		constexpr Version(const Version&) noexcept = default;
		constexpr Version(Version&&) noexcept = default;

		constexpr auto operator=(const Version&) noexcept -> Version& = default;
		constexpr auto operator=(Version&&) noexcept -> Version& = default;

		constexpr auto operator=(std::array<value_type, MAX_SIZE> a_version) noexcept -> Version&
		{
			_major = a_version[0];
			_minor = a_version[1];
			_patch = a_version[2];
			_build = a_version[3];
			return *this;
		}

		constexpr auto operator=(std::span<const value_type, MAX_SIZE> a_version) noexcept -> Version&
		{
			_major = a_version[0];
			_minor = a_version[1];
			_patch = a_version[2];
			_build = a_version[3];
			return *this;
		}

		[[nodiscard]]
		constexpr auto operator==(const Version&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Version&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto view() noexcept -> auto
		{
			return std::span(reinterpret_cast<std::array<value_type, MAX_SIZE>&>(_major));
		}

		[[nodiscard]]
		constexpr auto view() const noexcept -> auto
		{
			return std::span(reinterpret_cast<const std::array<value_type, MAX_SIZE>&>(_major));
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return view()[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return view()[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return view().data();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return view().data();
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return begin();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return end();
		}

		[[nodiscard]]
		constexpr auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		constexpr auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto size() const noexcept -> size_type
		{
			return MAX_SIZE;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return MAX_SIZE;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto empty() const noexcept -> bool
		{
			return false;
		}

		[[nodiscard]]
		constexpr auto GetMajor() const noexcept -> value_type
		{
			return _major;
		}

		constexpr void SetMajor(value_type a_major) noexcept
		{
			_major = a_major;
		}

		[[nodiscard]]
		constexpr auto GetMinor() const noexcept -> value_type
		{
			return _minor;
		}

		constexpr void SetMinor(value_type a_minor) noexcept
		{
			_minor = a_minor;
		}

		[[nodiscard]]
		constexpr auto GetPatch() const noexcept -> value_type
		{
			return _patch;
		}

		constexpr void SetPatch(value_type a_patch) noexcept
		{
			_patch = a_patch;
		}

		[[nodiscard]]
		constexpr auto GetBuild() const noexcept -> value_type
		{
			return _build;
		}

		constexpr void SetBuild(value_type a_build) noexcept
		{
			_build = a_build;
		}

		template <REX::win32_character CharT>
		[[nodiscard]]
		static constexpr auto FromString(
			std::basic_string_view<CharT> a_version,
			CharT a_separator = DEFAULT_SEPARATOR<CharT>) noexcept -> std::expected<Version, REX::PosixErrorCode>
		{
			if (a_version.empty()) [[unlikely]] {
				return std::unexpected(REX::PosixErrorCode::invalid_argument);
			}

			auto elements = std::array<value_type, MAX_SIZE>();
			auto elementIndex = static_cast<std::size_t>(0);

			for (const auto element : std::ranges::views::split(a_version, a_separator)) {
				if (elementIndex >= elements.size()) [[unlikely]] {
					return std::unexpected(REX::PosixErrorCode::invalid_argument);
				}

				const auto elementView = std::basic_string_view<CharT>{element.begin(), element.end()};
				if (elementView.empty()) [[unlikely]] {
					return std::unexpected(REX::PosixErrorCode::invalid_argument);
				}

				auto elementBuffer = std::array<char, REX::buffer_traits<value_type>::buffer_size::value>();
				for (auto i = static_cast<std::uint32_t>(0); i < elementBuffer.size() && i < elementView.size(); i++) {
					elementBuffer[i] = static_cast<char>(elementView[i]);
				}

				const auto conversionResult = REX::FromString<value_type>(elementBuffer.data());
				if (!conversionResult.has_value()) [[unlikely]] {
					return std::unexpected(conversionResult.error());
				}

				elements[elementIndex++] = conversionResult.value();
			}

			return Version(elements);
		}

		template <REX::win32_character CharT>
		[[nodiscard]]
		auto ToString(std::span<CharT> a_buffer, CharT a_separator = DEFAULT_SEPARATOR<CharT>) const noexcept
			-> std::basic_string_view<CharT>;

		template <>
		[[nodiscard]]
		auto ToString(std::span<char> a_buffer, char a_separator) const noexcept -> std::basic_string_view<char>;

		template <>
		[[nodiscard]]
		auto ToString(std::span<wchar_t> a_buffer, wchar_t a_separator) const noexcept
			-> std::basic_string_view<wchar_t>;

		template <REX::win32_character CharT>
		[[nodiscard]]
		auto ToString(CharT a_separator = DEFAULT_SEPARATOR<CharT>) const -> std::basic_string<CharT>
		{
			auto buffer = std::array<CharT, MAX_STRING_SIZE>();
			const auto bufferView = ToString<CharT>(buffer, a_separator);
			return std::basic_string<CharT>(bufferView);
		}

		template <REX::unsigned_integer T>
		[[nodiscard]]
		static constexpr auto Unpack(T a_packedVersion) noexcept -> Version;

		template <>
		[[nodiscard]]
		constexpr auto Unpack(std::uint32_t a_packedVersion) noexcept -> Version
		{
			return Version{
				static_cast<value_type>(
					(a_packedVersion >> static_cast<std::uint32_t>(0x18)) & static_cast<std::uint32_t>(0x0FF)),
				static_cast<value_type>(
					(a_packedVersion >> static_cast<std::uint32_t>(0x10)) & static_cast<std::uint32_t>(0x0FF)),
				static_cast<value_type>(
					(a_packedVersion >> static_cast<std::uint32_t>(0x04)) & static_cast<std::uint32_t>(0xFFF)),
				static_cast<value_type>(
					(a_packedVersion >> static_cast<std::uint32_t>(0x00)) & static_cast<std::uint32_t>(0x00F))
			};
		}

		template <>
		[[nodiscard]]
		constexpr auto Unpack(std::uint64_t a_packedVersion) noexcept -> Version
		{
			return Version{
				static_cast<value_type>(
					(a_packedVersion >> std::numeric_limits<std::uint16_t>::digits * 3) &
					std::numeric_limits<std::uint16_t>::max()),
				static_cast<value_type>(
					(a_packedVersion >> std::numeric_limits<std::uint16_t>::digits * 2) &
					std::numeric_limits<std::uint16_t>::max()),
				static_cast<value_type>(
					(a_packedVersion >> std::numeric_limits<std::uint16_t>::digits * 1) &
					std::numeric_limits<std::uint16_t>::max()),
				static_cast<value_type>(
					(a_packedVersion >> std::numeric_limits<std::uint16_t>::digits * 0) &
					std::numeric_limits<std::uint16_t>::max())
			};
		}

		template <REX::unsigned_integer T>
		[[nodiscard]]
		constexpr auto Pack() const noexcept -> T;

		template <>
		[[nodiscard]]
		constexpr auto Pack() const noexcept -> std::uint32_t
		{
			return (GetMajor() & static_cast<std::uint32_t>(0x0FF)) << static_cast<std::uint32_t>(0x18) |
				   (GetMinor() & static_cast<std::uint32_t>(0x0FF)) << static_cast<std::uint32_t>(0x10) |
				   (GetPatch() & static_cast<std::uint32_t>(0xFFF)) << static_cast<std::uint32_t>(0x04) |
				   (GetBuild() & static_cast<std::uint32_t>(0x0FF)) << static_cast<std::uint32_t>(0x00);
		}

		template <>
		[[nodiscard]]
		constexpr auto Pack() const noexcept -> std::uint64_t
		{
			return (static_cast<std::uint64_t>(GetMajor()) & std::numeric_limits<std::uint16_t>::max())
					   << std::numeric_limits<std::uint16_t>::digits * 3 |
				   (static_cast<std::uint64_t>(GetMinor()) & std::numeric_limits<std::uint16_t>::max())
					   << std::numeric_limits<std::uint16_t>::digits * 2 |
				   (static_cast<std::uint64_t>(GetPatch()) & std::numeric_limits<std::uint16_t>::max())
					   << std::numeric_limits<std::uint16_t>::digits * 1 |
				   (static_cast<std::uint64_t>(GetBuild()) & std::numeric_limits<std::uint16_t>::max())
					   << std::numeric_limits<std::uint16_t>::digits * 0;
		}

		constexpr void swap(Version& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_major, a_other._major);
			std::swap(_minor, a_other._minor);
			std::swap(_patch, a_other._patch);
			std::swap(_build, a_other._build);
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		value_type _major{0};
		value_type _minor{0};
		value_type _patch{0};
		value_type _build{0};
		// NOLINTEND(readability-identifier-naming)
	};

	inline constexpr auto Version::MIN = Version(
		std::numeric_limits<Version::value_type>::min(),
		std::numeric_limits<Version::value_type>::min(),
		std::numeric_limits<Version::value_type>::min(),
		std::numeric_limits<Version::value_type>::min());

	inline constexpr auto Version::MAX = Version(
		std::numeric_limits<Version::value_type>::max(),
		std::numeric_limits<Version::value_type>::max(),
		std::numeric_limits<Version::value_type>::max(),
		std::numeric_limits<Version::value_type>::max());

	static_assert(std::is_standard_layout_v<Version>);
	static_assert(std::is_trivially_destructible_v<Version>);
	static_assert(std::is_trivially_copyable_v<Version>);
	static_assert(std::is_trivially_move_constructible_v<Version>);

	static_assert(!Version::FromString(""sv).has_value());
	static_assert(Version::FromString("1"sv) == Version(1, 0, 0, 0));
	static_assert(Version::FromString("1.2"sv) == Version(1, 2, 0, 0));
	static_assert(Version::FromString("1.2.3"sv) == Version(1, 2, 3, 0));
	static_assert(Version::FromString("1.2.3.4"sv) == Version(1, 2, 3, 4));
	static_assert(Version::FromString("1-2-3-4"sv, '-') == Version(1, 2, 3, 4));

	static_assert(Version::Unpack(static_cast<std::uint32_t>(0x0102'0034)) == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).Pack<std::uint32_t>() == static_cast<std::uint32_t>(0x0102'0034));

	static_assert(Version::Unpack(static_cast<std::uint64_t>(0x0001'0002'0003'0004)) == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).Pack<std::uint64_t>() == static_cast<std::uint64_t>(0x0001'0002'0003'0004));
}

namespace std
{
	template <>
	struct hash<REX::Version>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Version& a_key) const noexcept -> std::size_t
		{
			return REX::HashRange(a_key);
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<REX::Version> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::Version& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString<char>());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<REX::Version> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::Version& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString<char>());
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <>
	struct meta<REX::Version>
	{
	public:
		using self_type = REX::Version;
		using other_type = std::string;

		inline static constexpr auto read_fn =
			[](self_type& a_self, const other_type& a_other, glz::context& a_context) -> void {
			using namespace std::string_view_literals;

			auto result = self_type::FromString<char>(a_other);
			if (!result.has_value()) {
				a_context.error = glz::error_code::constraint_violated;
				a_context.custom_error_message = "Invalid version"sv;
				return;
			}

			a_self = std::move(result).value();
		};

		inline static constexpr auto write_fn = [](const self_type& a_self, other_type& a_other) -> void {
			a_other = a_self.ToString<char>();
		};

		inline static constexpr auto value = glz::custom<read_fn, write_fn>;
	};
}
#endif
