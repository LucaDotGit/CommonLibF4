#pragma once

#include "REX/Error.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	bool CreateParentDirectories(const std::filesystem::path& a_filePath);
	bool CreateParentDirectories(const std::filesystem::path& a_filePath, REX::SystemError& a_outError) noexcept;

	[[nodiscard]] auto GetFilesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_fileNamePattern = {},
		bool a_recursive = false)
		-> std::expected<std::vector<std::filesystem::path>, REX::SystemError>;

	[[nodiscard]] auto GetDirectoriesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_directoryNamePattern = {},
		bool a_recursive = false)
		-> std::expected<std::vector<std::filesystem::path>, REX::SystemError>;

	[[nodiscard]] auto ForEachEntryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_entryNamePattern = {},
		bool a_recursive = false)
		-> std::expected<bool, REX::SystemError>;

	[[nodiscard]] auto ForEachFileInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_fileNamePattern = {},
		bool a_recursive = false)
		-> std::expected<bool, REX::SystemError>;

	[[nodiscard]] auto ForEachDirectoryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_directoryNamePattern = {},
		bool a_recursive = false)
		-> std::expected<bool, REX::SystemError>;
}
