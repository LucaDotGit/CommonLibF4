#pragma once

namespace REX
{
	template <REX::character CharT>
	inline constexpr auto WINDOWS_PATH_SEPARATOR = static_cast<CharT>('\\');

	template <REX::character CharT>
	inline constexpr auto UNIX_PATH_SEPARATOR = static_cast<CharT>('/');

	template <REX::character CharT>
	inline constexpr auto EXTENSION_SEPARATOR = static_cast<CharT>('.');

	template <REX::character CharT>
	inline constexpr auto DIRECTORY_SEPARATOR = UNIX_PATH_SEPARATOR<CharT>;

	template <REX::character CharT>
	inline constexpr auto CURRENT_DIRECTORY = std::false_type();

	template <>
	inline constexpr auto CURRENT_DIRECTORY<char> = "."sv;

	template <>
	inline constexpr auto CURRENT_DIRECTORY<wchar_t> = L"."sv;

	template <REX::character CharT>
	inline constexpr auto PARENT_DIRECTORY = std::false_type();

	template <>
	inline constexpr auto PARENT_DIRECTORY<char> = ".."sv;

	template <>
	inline constexpr auto PARENT_DIRECTORY<wchar_t> = L".."sv;

	template <REX::character CharT>
	inline constexpr auto INVALID_PATH_CHARS = []() consteval noexcept {
#if _WIN32 == 1
		constexpr auto EXTRA_CHAR_COUNT = static_cast<std::size_t>(2);
		constexpr auto CONTROL_CHAR_COUNT = static_cast<std::size_t>(32);

		auto chars = std::array<CharT, EXTRA_CHAR_COUNT + CONTROL_CHAR_COUNT>{
			static_cast<CharT>('\0'),
			static_cast<CharT>('|')
		};

		for (auto i = static_cast<std::size_t>(0); i < CONTROL_CHAR_COUNT; i++) {
			chars[EXTRA_CHAR_COUNT + i] = static_cast<CharT>(i);
		}

		return chars;
#else
		return std::array{
			static_cast<CharT>('\0')
		};
#endif
	}();

	template <REX::character CharT>
	inline constexpr auto INVALID_FILE_NAME_CHARS = []() consteval noexcept {
#if _WIN32 == 1
		constexpr auto EXTRA_CHAR_COUNT = static_cast<std::size_t>(10);
		constexpr auto CONTROL_CHAR_COUNT = static_cast<std::size_t>(32);

		auto chars = std::array<CharT, EXTRA_CHAR_COUNT + CONTROL_CHAR_COUNT>{
			static_cast<CharT>('\0'),
			static_cast<CharT>('\\'),
			static_cast<CharT>('/'),
			static_cast<CharT>(':'),
			static_cast<CharT>('*'),
			static_cast<CharT>('?'),
			static_cast<CharT>('"'),
			static_cast<CharT>('<'),
			static_cast<CharT>('>'),
			static_cast<CharT>('|')
		};

		for (auto i = static_cast<std::size_t>(0); i < CONTROL_CHAR_COUNT; i++) {
			chars[EXTRA_CHAR_COUNT + i] = static_cast<CharT>(i);
		}

		return chars;
#else
		return std::array{
			static_cast<CharT>('\0'),
			static_cast<CharT>('/')
		};
#endif
	}();

	template <REX::character CharT>
	[[nodiscard]] constexpr std::basic_string_view<CharT> GetFileName(std::basic_string_view<CharT> a_filePath) noexcept
	{
		if (a_filePath.empty()) {
			return {};
		}

		for (auto pathIt = a_filePath.end() - 1; pathIt != a_filePath.begin(); pathIt--) {
			if (*pathIt == WINDOWS_PATH_SEPARATOR<CharT> || *pathIt == UNIX_PATH_SEPARATOR<CharT>) {
				return a_filePath.substr(static_cast<std::size_t>(pathIt - a_filePath.begin() + 1));
			}
		}

		return a_filePath;
	}

	extern template std::string_view GetFileName(std::string_view a_filePath) noexcept;
	extern template std::wstring_view GetFileName(std::wstring_view a_filePath) noexcept;
	extern template std::u8string_view GetFileName(std::u8string_view a_filePath) noexcept;
	extern template std::u16string_view GetFileName(std::u16string_view a_filePath) noexcept;
	extern template std::u32string_view GetFileName(std::u32string_view a_filePath) noexcept;

	template <REX::character CharT>
	[[nodiscard]] constexpr std::basic_string_view<CharT> GetFileNameWithoutExtension(std::basic_string_view<CharT> a_filePath) noexcept
	{
		if (a_filePath.empty()) {
			return {};
		}

		const auto fileName = GetFileName(a_filePath);
		for (auto pathIt = fileName.end() - 1; pathIt != fileName.begin(); pathIt--) {
			if (*pathIt == EXTENSION_SEPARATOR<CharT>) {
				return fileName.substr(0, static_cast<std::size_t>(pathIt - fileName.begin()));
			}
		}

		return fileName;
	}

	extern template std::string_view GetFileNameWithoutExtension(std::string_view a_filePath) noexcept;
	extern template std::wstring_view GetFileNameWithoutExtension(std::wstring_view a_filePath) noexcept;
	extern template std::u8string_view GetFileNameWithoutExtension(std::u8string_view a_filePath) noexcept;
	extern template std::u16string_view GetFileNameWithoutExtension(std::u16string_view a_filePath) noexcept;
	extern template std::u32string_view GetFileNameWithoutExtension(std::u32string_view a_filePath) noexcept;

	template <REX::character CharT>
	[[nodiscard]] constexpr std::basic_string_view<CharT> GetFileExtension(std::basic_string_view<CharT> a_filePath) noexcept
	{
		if (a_filePath.empty()) {
			return {};
		}

		const auto fileName = GetFileName(a_filePath);
		for (auto pathIt = fileName.end() - 1; pathIt != fileName.begin(); pathIt--) {
			if (*pathIt == EXTENSION_SEPARATOR<CharT>) {
				return fileName.substr(static_cast<std::size_t>(pathIt - fileName.begin()));
			}
		}

		return {};
	}

	extern template std::string_view GetFileExtension(std::string_view a_filePath) noexcept;
	extern template std::wstring_view GetFileExtension(std::wstring_view a_filePath) noexcept;
	extern template std::u8string_view GetFileExtension(std::u8string_view a_filePath) noexcept;
	extern template std::u16string_view GetFileExtension(std::u16string_view a_filePath) noexcept;
	extern template std::u32string_view GetFileExtension(std::u32string_view a_filePath) noexcept;

	template <REX::character CharT>
	[[nodiscard]] constexpr std::basic_string_view<CharT> GetDirectoryPath(std::basic_string_view<CharT> a_filePath) noexcept
	{
		if (a_filePath.empty()) {
			return {};
		}

		for (auto pathIt = a_filePath.end() - 1; pathIt != a_filePath.begin(); pathIt--) {
			if (*pathIt == WINDOWS_PATH_SEPARATOR<CharT> || *pathIt == UNIX_PATH_SEPARATOR<CharT>) {
				return a_filePath.substr(0, static_cast<std::size_t>(pathIt - a_filePath.begin()));
			}
		}

		return {};
	}

	extern template std::string_view GetDirectoryPath(std::string_view a_filePath) noexcept;
	extern template std::wstring_view GetDirectoryPath(std::wstring_view a_filePath) noexcept;
	extern template std::u8string_view GetDirectoryPath(std::u8string_view a_filePath) noexcept;
	extern template std::u16string_view GetDirectoryPath(std::u16string_view a_filePath) noexcept;
	extern template std::u32string_view GetDirectoryPath(std::u32string_view a_filePath) noexcept;

	template <REX::character CharT>
	constexpr void GeneralizePath(std::span<CharT> a_path) noexcept
	{
		for (auto& character : a_path) {
			if (character == WINDOWS_PATH_SEPARATOR<CharT>) {
				character = UNIX_PATH_SEPARATOR<CharT>;
			}
		}
	}

	extern template void GeneralizePath(std::span<char> a_path) noexcept;
	extern template void GeneralizePath(std::span<wchar_t> a_path) noexcept;
	extern template void GeneralizePath(std::span<char8_t> a_path) noexcept;
	extern template void GeneralizePath(std::span<char16_t> a_path) noexcept;
	extern template void GeneralizePath(std::span<char32_t> a_path) noexcept;
}
