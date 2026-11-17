#pragma once

#include "REX/Concepts.hpp"
#include "REX/Macros.hpp"

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
	inline constexpr auto CURRENT_DIRECTORY = REX_STRING_LITERAL(CharT, "."sv);

	template <REX::character CharT>
	inline constexpr auto PARENT_DIRECTORY = REX_STRING_LITERAL(CharT, ".."sv);

	template <REX::character CharT>
	inline constexpr auto INVALID_PATH_CHARS = []() consteval noexcept -> auto {
#if (_WIN32 == 1)
		constexpr auto EXTRA_CHAR_COUNT = static_cast<std::size_t>(2);
		constexpr auto CONTROL_CHAR_COUNT = static_cast<std::size_t>(32);

		auto chars =
			std::array<CharT, EXTRA_CHAR_COUNT + CONTROL_CHAR_COUNT>{static_cast<CharT>('\0'), static_cast<CharT>('|')};

		for (auto i = static_cast<std::size_t>(0); i < CONTROL_CHAR_COUNT; i++) {
			chars[EXTRA_CHAR_COUNT + i] = static_cast<CharT>(i);
		}

		return chars;
#else
		return std::array{static_cast<CharT>('\0')};
#endif
	}();

	template <REX::character CharT>
	inline constexpr auto INVALID_FILE_NAME_CHARS = []() consteval noexcept -> auto {
#if (_WIN32 == 1)
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
		return std::array{static_cast<CharT>('\0'), static_cast<CharT>('/')};
#endif
	}();

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto GetFileName(std::basic_string_view<CharT> a_filePath) noexcept -> std::basic_string_view<CharT>
	{
		if (a_filePath.empty()) {
			return {};
		}

		for (auto pathIt = std::prev(a_filePath.end()); pathIt != a_filePath.begin(); pathIt--) {
			if (*pathIt == WINDOWS_PATH_SEPARATOR<CharT> || *pathIt == UNIX_PATH_SEPARATOR<CharT>) {
				return a_filePath.substr(static_cast<std::size_t>(pathIt - a_filePath.begin() + 1));
			}
		}

		return a_filePath;
	}

	static_assert(GetFileName("/path/to/file.txt"sv) == "file.txt"sv);
	static_assert(GetFileName("/path/to/file"sv) == "file"sv);
	static_assert(GetFileName("file.txt"sv) == "file.txt"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto GetFileNameWithoutExtension(std::basic_string_view<CharT> a_filePath) noexcept
		-> std::basic_string_view<CharT>
	{
		if (a_filePath.empty()) {
			return {};
		}

		const auto fileName = GetFileName(a_filePath);
		for (auto pathIt = std::prev(fileName.end()); pathIt != fileName.begin(); pathIt--) {
			if (*pathIt == EXTENSION_SEPARATOR<CharT>) {
				return fileName.substr(0, static_cast<std::size_t>(pathIt - fileName.begin()));
			}
		}

		return fileName;
	}

	static_assert(GetFileNameWithoutExtension("/path/to/file.txt"sv) == "file"sv);
	static_assert(GetFileNameWithoutExtension("/path/to/file"sv) == "file"sv);
	static_assert(GetFileNameWithoutExtension("file.txt"sv) == "file"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto GetFileExtension(std::basic_string_view<CharT> a_filePath) noexcept -> std::basic_string_view<CharT>
	{
		if (a_filePath.empty()) {
			return {};
		}

		const auto fileName = GetFileName(a_filePath);
		for (auto pathIt = std::prev(fileName.end()); pathIt != fileName.begin(); pathIt--) {
			if (*pathIt == EXTENSION_SEPARATOR<CharT>) {
				return fileName.substr(static_cast<std::size_t>(pathIt - fileName.begin()));
			}
		}

		return {};
	}

	static_assert(GetFileExtension("/path/to/file.txt"sv) == ".txt"sv);
	static_assert(GetFileExtension("/path/to/file"sv).empty());

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto GetDirectoryPath(std::basic_string_view<CharT> a_filePath) noexcept -> std::basic_string_view<CharT>
	{
		if (a_filePath.empty()) {
			return {};
		}

		for (auto pathIt = std::prev(a_filePath.end()); pathIt != a_filePath.begin(); pathIt--) {
			if (*pathIt == WINDOWS_PATH_SEPARATOR<CharT> || *pathIt == UNIX_PATH_SEPARATOR<CharT>) {
				return a_filePath.substr(0, static_cast<std::size_t>(pathIt - a_filePath.begin()));
			}
		}

		return {};
	}

	static_assert(GetDirectoryPath("/path/to/file.txt"sv) == "/path/to"sv);

	template <REX::character CharT>
	constexpr void NormalizePathSeparators(std::span<CharT> a_path) noexcept
	{
		for (auto& character : a_path) {
			if (character == WINDOWS_PATH_SEPARATOR<CharT>) {
				character = UNIX_PATH_SEPARATOR<CharT>;
			}
		}
	}

	static_assert([]() consteval noexcept -> bool {
		auto path = std::to_array("/path\\to\\file.txt");
		NormalizePathSeparators(std::span<char>(path));
		return std::ranges::equal(path, std::to_array("/path/to/file.txt"));
	}());
}
