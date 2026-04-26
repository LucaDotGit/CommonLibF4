#pragma once

#include "REX/ErrorCode.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	inline constexpr auto CURRENT_DIRECTORY = "."sv;
	inline constexpr auto PARENT_DIRECTORY = ".."sv;
	inline constexpr auto EXTENSION_SEPARATOR = "."sv;
	inline constexpr auto DIRECTORY_SEPARATOR = "/"sv;

	inline REX_CONSTEXPR_RELEASE auto INVALID_PATH_CHARS = []() REX_CONSTEVAL_RELEASE noexcept {
#if _WIN32 == 1
		constexpr auto EXTRA_CHAR_COUNT = static_cast<std::size_t>(2);
		constexpr auto CONTROL_CHAR_COUNT = static_cast<std::size_t>(32);

		auto chars = std::array<std::string, EXTRA_CHAR_COUNT + CONTROL_CHAR_COUNT>{
			"\0"s, "|"s
		};

		for (auto i = static_cast<std::size_t>(0); i < CONTROL_CHAR_COUNT; i++) {
			chars[EXTRA_CHAR_COUNT + i] = static_cast<char>(i);
		}

		return chars;
#else
		return std::array{ "\0"s };
#endif
	}();

	inline REX_CONSTEXPR_RELEASE auto INVALID_FILE_NAME_CHARS = []() REX_CONSTEVAL_RELEASE noexcept {
#if _WIN32 == 1
		constexpr auto EXTRA_CHAR_COUNT = static_cast<std::size_t>(10);
		constexpr auto CONTROL_CHAR_COUNT = static_cast<std::size_t>(32);

		auto chars = std::array<std::string, EXTRA_CHAR_COUNT + CONTROL_CHAR_COUNT>{
			"\0"s, "\\"s, "/"s, ":"s, "*"s, "?"s, "\""s, "<"s, ">"s, "|"s
		};

		for (auto i = static_cast<std::size_t>(0); i < CONTROL_CHAR_COUNT; i++) {
			chars[EXTRA_CHAR_COUNT + i] = static_cast<char>(i);
		}

		return chars;
#else
		return std::array{ "\0"s, "/"s };
#endif
	}();

	[[nodiscard]] auto GetFilesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_fileNamePattern = {},
		bool a_recursive = false) -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>;

	[[nodiscard]] auto GetDirectoriesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_directoryNamePattern = {},
		bool a_recursive = false) -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>;

	[[nodiscard]] auto ForEachEntryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_entryNamePattern = {},
		bool a_recursive = false) -> std::expected<bool, REX::SystemError>;

	[[nodiscard]] auto ForEachFileInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_fileNamePattern = {},
		bool a_recursive = false) -> std::expected<bool, REX::SystemError>;

	[[nodiscard]] auto ForEachDirectoryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_directoryNamePattern = {},
		bool a_recursive = false) -> std::expected<bool, REX::SystemError>;
}
