#pragma once

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"
#include "REX/Formatting.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	enum class ForEachResult : std::int32_t;

	using DirectoryEntryPredicate = auto(const std::filesystem::directory_entry&) const
		-> std::expected<REX::ForEachResult, REX::SystemError>;

	auto CreateParentDirectories(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<bool, REX::SystemError>;

	template <REX::win32_character CharT>
	[[nodiscard]]
	auto ReadAllTextFromFile(std::filesystem::path a_filePath) noexcept
		-> std::expected<std::basic_string<CharT>, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto ReadAllTextFromFile(std::filesystem::path a_filePath) noexcept -> std::expected<std::string, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto ReadAllTextFromFile(std::filesystem::path a_filePath) noexcept
		-> std::expected<std::wstring, REX::SystemError>;

	[[nodiscard]]
	auto ReadAllLinesFromFile(std::filesystem::path a_filePath) noexcept
		-> std::expected<std::vector<std::string>, REX::SystemError>;

	[[nodiscard]]
	auto ReadAllBytesFromFile(std::filesystem::path a_filePath) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;

	template <REX::win32_character CharT>
	auto WriteAllTextToFile(std::filesystem::path a_filePath, std::basic_string_view<CharT> a_text) noexcept
		-> REX::SystemError;

	template <>
	auto WriteAllTextToFile(std::filesystem::path a_filePath, std::string_view a_text) noexcept -> REX::SystemError;

	template <>
	auto WriteAllTextToFile(std::filesystem::path a_filePath, std::wstring_view a_text) noexcept -> REX::SystemError;

	auto WriteAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string> a_lines) noexcept
		-> REX::SystemError;
	auto WriteAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string_view> a_lines) noexcept
		-> REX::SystemError;

	auto WriteAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::byte> a_bytes) noexcept
		-> REX::SystemError;
	auto WriteAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::uint8_t> a_bytes) noexcept
		-> REX::SystemError;

	auto AppendAllTextToFile(std::filesystem::path a_filePath, std::string_view a_text) noexcept -> REX::SystemError;

	auto AppendAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string> a_lines) noexcept
		-> REX::SystemError;
	auto AppendAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string_view> a_lines) noexcept
		-> REX::SystemError;

	auto AppendAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::byte> a_bytes) noexcept
		-> REX::SystemError;
	auto AppendAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::uint8_t> a_bytes) noexcept
		-> REX::SystemError;

	auto AppendLineToFile(std::filesystem::path a_filePath, std::string_view a_line) noexcept -> REX::SystemError;

	[[nodiscard]]
	auto FindFilesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_fileNamePattern = {},
		bool a_recursive = false) noexcept -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>;

	[[nodiscard]]
	auto FindDirectoriesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_directoryNamePattern = {},
		bool a_recursive = false) noexcept -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>;

	[[nodiscard]]
	auto ForEachEntryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
		const std::filesystem::path& a_entryNamePattern = {},
		bool a_recursive = false) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>;

	[[nodiscard]]
	auto ForEachFileInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
		const std::filesystem::path& a_fileNamePattern = {},
		bool a_recursive = false) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>;

	[[nodiscard]]
	auto ForEachDirectoryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
		const std::filesystem::path& a_directoryNamePattern = {},
		bool a_recursive = false) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>;

	auto RotateFile(const std::filesystem::path& a_filePath, std::size_t a_fileRotationCount) noexcept
		-> REX::SystemError;

	auto RotateFile(
		const std::filesystem::path& a_filePath,
		std::size_t a_fileRotationCount,
		REX::FormatString<std::string_view, std::size_t, std::string_view> a_fileRotationFormat) noexcept
		-> REX::SystemError;
}
