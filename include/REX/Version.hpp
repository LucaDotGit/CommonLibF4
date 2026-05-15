#pragma once

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/Hash.hpp"

namespace REX
{
	struct Version final
	{
	public:
		inline static constexpr auto MAX_SIZE = static_cast<std::size_t>(4);

		using value_type = std::uint16_t;
		using container_type = std::array<value_type, MAX_SIZE>;
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

		template <REX::win32_character CharT>
		inline static constexpr auto DEFAULT_SEPARATOR = static_cast<CharT>('.');

		inline static constexpr auto MAX_BUFFER_SIZE = REX::buffer_traits<value_type>::buffer_size::value * MAX_SIZE;

		static const Version MIN;
		static const Version MAX;

		constexpr Version() noexcept = default;
		constexpr ~Version() noexcept = default;

		constexpr explicit Version(value_type a_v01, value_type a_v02, value_type a_v03, value_type a_v04) noexcept
			: _data{ a_v01, a_v02, a_v03, a_v04 }
		{
		}

		constexpr explicit Version(value_type a_v01, value_type a_v02, value_type a_v03) noexcept
			: _data{ a_v01, a_v02, a_v03, 0 }
		{
		}

		constexpr explicit Version(value_type a_v01, value_type a_v02) noexcept
			: _data{ a_v01, a_v02, 0, 0 }
		{
		}

		constexpr explicit Version(value_type a_v01) noexcept
			: _data{ a_v01, 0, 0, 0 }
		{
		}

		constexpr explicit Version(container_type a_version) noexcept
			: _data(a_version)
		{
		}

		constexpr explicit Version(std::span<const value_type, MAX_SIZE> a_version) noexcept
			: _data{ a_version[0], a_version[1], a_version[2], a_version[3] }
		{
		}

		constexpr Version(const Version&) noexcept = default;
		constexpr Version(Version&&) noexcept = default;

		constexpr Version& operator=(const Version&) noexcept = default;
		constexpr Version& operator=(Version&&) noexcept = default;

		constexpr Version& operator=(container_type a_version) noexcept
		{
			_data = a_version;
			return *this;
		}

		constexpr Version& operator=(std::span<value_type, MAX_SIZE> a_version) noexcept
		{
			_data = { a_version[0], a_version[1], a_version[2], a_version[3] };
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Version&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Version&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Version&) const noexcept = default;

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]] constexpr reference front() noexcept { return at(0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return at(0); }

		[[nodiscard]] constexpr reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr iterator begin() noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator end() noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr size_type size() const noexcept { return _data.size(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return _data.max_size(); }

		[[nodiscard]] constexpr value_type GetMajor() const noexcept { return at(0); }
		[[nodiscard]] constexpr value_type GetMinor() const noexcept { return at(1); }
		[[nodiscard]] constexpr value_type GetPatch() const noexcept { return at(2); }
		[[nodiscard]] constexpr value_type GetBuild() const noexcept { return at(3); }

		template <REX::win32_character CharT>
		[[nodiscard]] static constexpr auto FromString(std::basic_string_view<CharT> a_version, CharT a_separator = DEFAULT_SEPARATOR<CharT>) noexcept
			-> std::expected<Version, REX::PosixErrorCode>
		{
			auto parts = container_type();
			auto partIndex = static_cast<std::size_t>(0);

			for (const auto stringPart : std::ranges::views::split(a_version, a_separator)) {
				if (partIndex >= parts.size()) {
					break;
				}

				const auto stringPartView = std::basic_string_view<CharT>(stringPart.begin(), stringPart.end());
				if (stringPartView.empty()) {
					break;
				}

				auto stringPartBuffer = std::array<char, REX::buffer_traits<value_type>::buffer_size::value>();

				for (auto i = 0ui32; i < stringPartBuffer.size() && i < stringPartView.size(); i++) {
					stringPartBuffer[i] = static_cast<char>(stringPartView[i]);
				}

				const auto conversionResult = std::from_chars(
					stringPartBuffer.data(),
					stringPartBuffer.data() + stringPartBuffer.size(),
					parts[partIndex]);
				if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) {
					return std::unexpected(conversionResult.ec);
				}

				partIndex++;
			}

			return Version(parts);
		}

		template <REX::win32_character CharT>
		[[nodiscard]] constexpr auto ToString(std::span<CharT> a_buffer, CharT a_separator = DEFAULT_SEPARATOR<CharT>) const noexcept
			-> std::basic_string_view<CharT>
		{
			auto totalSize = static_cast<std::size_t>(0);

			for (auto it = _data.begin(); it != _data.end(); it++) {
				auto elementBuffer = std::array<char, REX::buffer_traits<value_type>::buffer_size::value>();

				const auto conversionResult = std::to_chars(
					elementBuffer.data(),
					elementBuffer.data() + elementBuffer.size(),
					*it);
				if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) [[unlikely]] {
					REX::Assert(false);
					return {};
				}

				const auto elementSize = std::distance(elementBuffer.data(), conversionResult.ptr);
				totalSize += elementSize;

				if (totalSize > a_buffer.size()) {
					return {};
				}

				std::copy_n(elementBuffer.data(), elementSize, a_buffer.data() + totalSize - elementSize);

				if (it == std::prev(_data.end())) {
					break;
				}

				if (totalSize == a_buffer.size()) {
					return {};
				}

				a_buffer[totalSize] = a_separator;
				totalSize++;
			}

			return std::basic_string_view<CharT>{ a_buffer.data(), totalSize };
		}

		template <REX::win32_character CharT>
		[[nodiscard]] constexpr auto ToString(CharT a_separator = DEFAULT_SEPARATOR<CharT>) const
			-> std::basic_string<CharT>
		{
			auto buffer = std::array<CharT, MAX_BUFFER_SIZE>();
			auto bufferView = ToString<CharT>(buffer, a_separator);
			return std::basic_string<CharT>(bufferView);
		}

		template <REX::unsigned_integer T>
		[[nodiscard]] static constexpr Version Unpack(T a_packedVersion) noexcept;

		template <>
		[[nodiscard]] constexpr Version Unpack(std::uint32_t a_packedVersion) noexcept
		{
			return Version{
				static_cast<value_type>((a_packedVersion >> 0x18ui32) & 0x0FFui32),
				static_cast<value_type>((a_packedVersion >> 0x10ui32) & 0x0FFui32),
				static_cast<value_type>((a_packedVersion >> 0x04ui32) & 0xFFFui32),
				static_cast<value_type>((a_packedVersion >> 0x00ui32) & 0x00Fui32)
			};
		}

		template <>
		[[nodiscard]] constexpr Version Unpack(std::uint64_t a_packedVersion) noexcept
		{
			return Version{
				static_cast<value_type>((a_packedVersion >> 0x30ui64) & 0xFFFFui64),
				static_cast<value_type>((a_packedVersion >> 0x20ui64) & 0xFFFFui64),
				static_cast<value_type>((a_packedVersion >> 0x10ui64) & 0xFFFFui64),
				static_cast<value_type>((a_packedVersion >> 0x00ui64) & 0xFFFFui64)
			};
		}

		template <REX::unsigned_integer T>
		[[nodiscard]] constexpr T Pack() const noexcept;

		template <>
		[[nodiscard]] constexpr std::uint32_t Pack() const noexcept
		{
			return (GetMajor() & 0x0FFui32) << 0x18ui32 |
				   (GetMinor() & 0x0FFui32) << 0x10ui32 |
				   (GetPatch() & 0xFFFui32) << 0x04ui32 |
				   (GetBuild() & 0x0FFui32) << 0x00ui32;
		}

		template <>
		[[nodiscard]] constexpr std::uint64_t Pack() const noexcept
		{
			return (static_cast<std::uint64_t>(GetMajor()) & 0xFFFFui64) << 0x30ui64 |
				   (static_cast<std::uint64_t>(GetMinor()) & 0xFFFFui64) << 0x20ui64 |
				   (static_cast<std::uint64_t>(GetPatch()) & 0xFFFFui64) << 0x10ui64 |
				   (static_cast<std::uint64_t>(GetBuild()) & 0xFFFFui64) << 0x00ui64;
		}

		constexpr void swap(Version& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

		container_type _data{ 0, 0, 0, 0 };
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

	extern template auto Version::FromString(std::string_view a_version, char a_separator) noexcept
		-> std::expected<Version, REX::PosixErrorCode>;
	extern template auto Version::FromString(std::wstring_view a_version, wchar_t a_separator) noexcept
		-> std::expected<Version, REX::PosixErrorCode>;

	extern template auto Version::ToString(std::span<char> a_buffer, char a_separator) const noexcept
		-> std::string_view;
	extern template auto Version::ToString(std::span<wchar_t> a_buffer, wchar_t a_separator) const noexcept
		-> std::wstring_view;

	extern template auto Version::ToString(char a_separator) const
		-> std::string;
	extern template auto Version::ToString(wchar_t a_separator) const
		-> std::wstring;

	static_assert(std::is_standard_layout_v<Version>);
	static_assert(std::is_trivially_destructible_v<Version>);
	static_assert(std::is_trivially_copyable_v<Version>);

	constexpr void swap(Version& a_lhs, Version& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace std
{
	template <>
	struct hash<REX::Version>
	{
	public:
		[[nodiscard]] std::size_t operator()(const REX::Version& a_key) const noexcept
		{
			return REX::HashRange(std::span{ a_key.begin(), a_key.end() });
		}
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<REX::Version>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::Version& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString<char>());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<REX::Version>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::Version& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString<char>());
		}
	};
}
#endif
