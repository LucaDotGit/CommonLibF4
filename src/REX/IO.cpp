#include "REX/IO.hpp"

#include "REX/Wildcards.hpp"

namespace REX::Impl
{
	[[nodiscard]] static auto MatchEntryNamePattern(
		const std::filesystem::path& a_entryPath,
		const std::filesystem::path& a_entryNamePattern) noexcept
	{
		if (a_entryNamePattern.empty()) {
			return true;
		}

#if _WIN32 == 1
		const auto fileName = a_entryPath.filename().generic_wstring();
		return REX::MatchWildcardsIgnoreCase(
			static_cast<std::wstring_view>(fileName),
			static_cast<std::wstring_view>(a_entryNamePattern.native()));
#else
		const auto fileName = a_entryPath.filename().generic_string();
		return REX::MatchWildcards(
			static_cast<std::string_view>(fileName),
			static_cast<std::string_view>(a_entryNamePattern.native()));
#endif
	}

	[[nodiscard]] static auto ForEachDirectoryEntry(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		bool a_recursive) -> std::expected<bool, REX::SystemError>
	{
		auto isDirError = REX::SystemError();
		if (!std::filesystem::is_directory(a_directoryPath, isDirError)) {
			return std::unexpected(isDirError);
		}

		auto dirItError = REX::SystemError();

		const auto iterateContent = [&](REX::SystemError& a_dirItError, const auto& a_dirItBegin) {
			if (a_dirItError.value() != REX::ERROR_NUMBER_SUCCESS) {
				return false;
			}

			auto dirIt = std::filesystem::begin(a_dirItBegin);
			const auto dirItEnd = std::filesystem::end(a_dirItBegin);

			for (; dirIt != dirItEnd && a_dirItError.value() == REX::ERROR_NUMBER_SUCCESS; dirIt.increment(a_dirItError)) {
				const auto& dirEntry = *dirIt;
				if (!std::invoke(*a_predicate, dirEntry)) {
					return false;
				}
			}

			return a_dirItError.value() == REX::ERROR_NUMBER_SUCCESS;
		};

		constexpr auto DIRECTORY_OPTIONS = std::filesystem::directory_options::skip_permission_denied;

		auto result = false;

		if (a_recursive) {
			const auto dirItBegin = std::filesystem::recursive_directory_iterator(a_directoryPath, DIRECTORY_OPTIONS, dirItError);
			result = iterateContent(dirItError, dirItBegin);
		}
		else {
			const auto dirItBegin = std::filesystem::directory_iterator(a_directoryPath, DIRECTORY_OPTIONS, dirItError);
			result = iterateContent(dirItError, dirItBegin);
		}

		if (dirItError.value() != REX::ERROR_NUMBER_SUCCESS) {
			return std::unexpected(dirItError);
		}

		return result;
	}

	[[nodiscard]] static auto GetDirectoryEntries(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_entryNamePattern,
		bool a_recursive,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate)
		-> std::expected<std::vector<std::filesystem::path>, REX::SystemError>
	{
		auto entries = std::vector<std::filesystem::path>();

		auto forEachEntryResult = ForEachDirectoryEntry(
			a_directoryPath,
			[&a_predicate, &a_entryNamePattern, &entries](const std::filesystem::directory_entry& a_dirEntry) {
				if (!std::invoke(*a_predicate, a_dirEntry)) {
					return true;
				}

				const auto& entryPath = a_dirEntry.path();
				if (!MatchEntryNamePattern(entryPath, a_entryNamePattern)) {
					return true;
				}

				entries.push_back(entryPath.lexically_normal());
				return true;
			},
			a_recursive);

		if (!forEachEntryResult) {
			return std::unexpected(std::move(forEachEntryResult).error());
		}

		return entries;
	}
}

namespace REX
{
	[[nodiscard]] auto GetFilesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_fileNamePattern,
		bool a_recursive) -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>
	{
		return Impl::GetDirectoryEntries(
			a_directoryPath,
			a_fileNamePattern,
			a_recursive,
			[](const std::filesystem::directory_entry& a_dirEntry) noexcept {
				auto isFileError = REX::SystemError();
				return a_dirEntry.is_regular_file(isFileError);
			});
	}

	[[nodiscard]] auto GetDirectoriesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_directoryNamePattern,
		bool a_recursive) -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>
	{
		return Impl::GetDirectoryEntries(
			a_directoryPath,
			a_directoryNamePattern,
			a_recursive,
			[](const std::filesystem::directory_entry& a_dirEntry) noexcept {
				auto isDirError = REX::SystemError();
				return a_dirEntry.is_directory(isDirError);
			});
	}

	[[nodiscard]] auto ForEachEntryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_entryNamePattern,
		bool a_recursive) -> std::expected<bool, REX::SystemError>
	{
		return Impl::ForEachDirectoryEntry(
			a_directoryPath,
			[&a_predicate, &a_entryNamePattern](const std::filesystem::directory_entry& a_dirEntry) {
				const auto& entryPath = a_dirEntry.path();
				if (!Impl::MatchEntryNamePattern(entryPath, a_entryNamePattern)) {
					return true;
				}

				return std::invoke(*a_predicate, a_dirEntry);
			},
			a_recursive);
	}

	[[nodiscard]] auto ForEachFileInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_fileNamePattern,
		bool a_recursive) -> std::expected<bool, REX::SystemError>
	{
		return Impl::ForEachDirectoryEntry(
			a_directoryPath,
			[&a_predicate, &a_fileNamePattern](const std::filesystem::directory_entry& a_dirEntry) {
				auto isFileError = REX::SystemError();
				if (!a_dirEntry.is_regular_file(isFileError)) {
					return true;
				}

				const auto& entryPath = a_dirEntry.path();
				if (!Impl::MatchEntryNamePattern(entryPath, a_fileNamePattern)) {
					return true;
				}

				return std::invoke(*a_predicate, a_dirEntry);
			},
			a_recursive);
	}

	[[nodiscard]] auto ForEachDirectoryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::function<bool(const std::filesystem::directory_entry&)>>& a_predicate,
		const std::filesystem::path& a_directoryNamePattern,
		bool a_recursive) -> std::expected<bool, REX::SystemError>
	{
		return Impl::ForEachDirectoryEntry(
			a_directoryPath,
			[&a_predicate, &a_directoryNamePattern](const std::filesystem::directory_entry& a_dirEntry) {
				auto isDirError = REX::SystemError();
				if (!a_dirEntry.is_directory(isDirError)) {
					return true;
				}

				const auto& entryPath = a_dirEntry.path();
				if (!Impl::MatchEntryNamePattern(entryPath, a_directoryNamePattern)) {
					return true;
				}

				return std::invoke(*a_predicate, a_dirEntry);
			},
			a_recursive);
	}
}
