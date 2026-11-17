#include "REX/IO.hpp"

#include "REX/Error.hpp"
#include "REX/Exception.hpp"
#include "REX/FileStream.hpp"
#include "REX/ForEachResult.hpp"
#include "REX/Formatting.hpp"
#include "REX/Localization.hpp"
#include "REX/NotNull.hpp"
#include "REX/Wildcards.hpp"

namespace REX::Impl
{
	namespace
	{
		[[nodiscard]]
		auto ForEachDirectoryEntry(
			const std::filesystem::path& a_directoryPath,
			const std::filesystem::path& a_entryNamePattern,
			const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
			bool a_recursive) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>
		{
			auto isDirectoryError = REX::SystemError();
			if (!std::filesystem::is_directory(a_directoryPath, isDirectoryError)) [[unlikely]] {
				return std::unexpected(isDirectoryError);
			}

			auto directoryItError = REX::SystemError();

			const auto iterateContent = [&a_entryNamePattern, &a_predicate](
											REX::SystemError& a_outDirectoryItError,
											const auto& a_directoryItBegin) -> REX::ForEachResult {
				if (a_outDirectoryItError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return REX::ForEachResult::Break;
				}

				auto directoryIt = std::filesystem::begin(a_directoryItBegin);
				const auto directoryItEnd = std::filesystem::end(a_directoryItBegin);

				for (; directoryIt != directoryItEnd && a_outDirectoryItError.value() == REX::ERROR_NUMBER_SUCCESS;
					 directoryIt.increment(a_outDirectoryItError)) {
					const auto& dirEntry = *directoryIt;
					if (!a_entryNamePattern.empty() &&
						!REX::MatchWildcards(dirEntry.path().filename(), a_entryNamePattern)) {
						continue;
					}

					const auto predicateResult = std::invoke(a_predicate.get(), dirEntry);
					if (!predicateResult.has_value()) {
						a_outDirectoryItError = predicateResult.error();
						return REX::ForEachResult::Break;
					}

					if (predicateResult.value() == REX::ForEachResult::Break) {
						return REX::ForEachResult::Break;
					}
				}

				if (a_outDirectoryItError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return REX::ForEachResult::Break;
				}

				return REX::ForEachResult::Continue;
			};

			constexpr auto DIRECTORY_OPTIONS = std::filesystem::directory_options::skip_permission_denied;

			auto result = REX::ForEachResult::Continue;

			try {
				if (a_recursive) {
					const auto directoryItBegin = std::filesystem::recursive_directory_iterator(
						a_directoryPath,
						DIRECTORY_OPTIONS,
						directoryItError);
					result = iterateContent(directoryItError, directoryItBegin);
				}
				else {
					const auto directoryItBegin =
						std::filesystem::directory_iterator(a_directoryPath, DIRECTORY_OPTIONS, directoryItError);
					result = iterateContent(directoryItError, directoryItBegin);
				}
			}
			catch (const std::filesystem::filesystem_error& error) {
				return std::unexpected(error.code());
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}

			if (directoryItError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return std::unexpected(directoryItError);
			}

			return result;
		}

		[[nodiscard]]
		auto FindDirectoryEntries(
			const std::filesystem::path& a_directoryPath,
			const std::filesystem::path& a_entryNamePattern,
			const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
			bool a_recursive) -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>
		{
			auto entries = std::vector<std::filesystem::path>();

			const auto forEachEntryResult = ForEachDirectoryEntry(
				a_directoryPath,
				a_entryNamePattern,
				[&a_predicate, &entries](const std::filesystem::directory_entry& a_dirEntry) noexcept
					-> std::expected<REX::ForEachResult, REX::SystemError> {
					const auto predicateResult = std::invoke(a_predicate.get(), a_dirEntry);
					if (!predicateResult.has_value()) {
						return std::unexpected(predicateResult.error());
					}

					if (predicateResult.value() == REX::ForEachResult::Break) {
						// The search continues, but the entry is not added to the result.
						return REX::ForEachResult::Continue;
					}

					try {
						entries.push_back(a_dirEntry.path().lexically_normal());
						return REX::ForEachResult::Continue;
					}
					catch (const std::bad_alloc& error) {
						std::ignore = error;
						return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
					}
				},
				a_recursive);

			if (!forEachEntryResult.has_value()) [[unlikely]] {
				return std::unexpected(forEachEntryResult.error());
			}

			return entries;
		}
	}
}

namespace REX
{
	auto CreateParentDirectories(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<bool, REX::SystemError>
	{
		if (a_filePath.empty()) {
			return false;
		}

		const auto parentPath = REX::TryCatch<std::bad_alloc>(
			[&a_filePath]() -> std::expected<std::filesystem::path, REX::SystemError> {
				return a_filePath.parent_path();
			},
			[](const std::bad_alloc& a_error) noexcept -> std::expected<std::filesystem::path, REX::SystemError> {
				std::ignore = a_error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			});

		if (!parentPath.has_value()) [[unlikely]] {
			return std::unexpected(parentPath.error());
		}

		if (parentPath->empty()) {
			return false;
		}

		auto createDirsError = REX::SystemError();
		if (!std::filesystem::create_directories(parentPath.value(), createDirsError)) [[unlikely]] {
			return std::unexpected(createDirsError);
		}

		return true;
	}

	template <>
	auto ReadAllTextFromFile(std::filesystem::path a_filePath) noexcept -> std::expected<std::string, REX::SystemError>
	{
		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Open,
			REX::FileAccess::Read,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return std::unexpected(fileStream.error());
		}

		auto readResult = fileStream->ReadText();
		if (!readResult.has_value()) [[unlikely]] {
			return std::unexpected(readResult.error());
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return std::unexpected(closeError);
		}

		return std::move(readResult).value();
	}

	template <>
	auto ReadAllTextFromFile(std::filesystem::path a_filePath) noexcept -> std::expected<std::wstring, REX::SystemError>
	{
		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Open,
			REX::FileAccess::Read,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return std::unexpected(fileStream.error());
		}

		{
			const auto readBom = fileStream->Read<wchar_t>();
			if (!readBom.has_value()) [[unlikely]] {
				return std::unexpected(readBom.error());
			}

			if (readBom.value() != std::bit_cast<wchar_t>(REX::UTF16_BOM)) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::illegal_byte_sequence));
			}
		}

		const auto readText = fileStream->ReadText();
		if (!readText.has_value()) [[unlikely]] {
			return std::unexpected(readText.error());
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return std::unexpected(closeError);
		}

		if ((readText->size() % sizeof(wchar_t)) != 0) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::illegal_byte_sequence));
		}

		try {
			return std::wstring{reinterpret_cast<const wchar_t*>(readText->data()), readText->size() / sizeof(wchar_t)};
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}
	}

	auto ReadAllLinesFromFile(std::filesystem::path a_filePath) noexcept
		-> std::expected<std::vector<std::string>, REX::SystemError>
	{
		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Open,
			REX::FileAccess::Read,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return std::unexpected(fileStream.error());
		}

		auto readResult = fileStream->ReadLines();
		if (!readResult.has_value()) [[unlikely]] {
			return std::unexpected(readResult.error());
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return std::unexpected(closeError);
		}

		return std::move(readResult).value();
	}

	auto ReadAllBytesFromFile(std::filesystem::path a_filePath) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Open,
			REX::FileAccess::Read,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return std::unexpected(fileStream.error());
		}

		auto readResult = fileStream->ReadBytes();
		if (!readResult.has_value()) [[unlikely]] {
			return std::unexpected(readResult.error());
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return std::unexpected(closeError);
		}

		return std::move(readResult).value();
	}

	template <>
	auto WriteAllTextToFile(std::filesystem::path a_filePath, std::string_view a_text) noexcept -> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Create,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteText(a_text);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	template <>
	auto WriteAllTextToFile(std::filesystem::path a_filePath, std::wstring_view a_text) noexcept -> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Create,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeBomError = fileStream->Write(std::bit_cast<wchar_t>(REX::UTF16_BOM));
		if (writeBomError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeBomError;
		}

		const auto writeTextError = fileStream->WriteText(
			std::string_view{reinterpret_cast<const char*>(a_text.data()), a_text.size() * sizeof(wchar_t)});
		if (writeTextError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeTextError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto WriteAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string> a_lines) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Create,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteLines(a_lines);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto WriteAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string_view> a_lines) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Create,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteLines(a_lines);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto WriteAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::byte> a_bytes) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Create,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteBytes(a_bytes);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto WriteAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::uint8_t> a_bytes) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Create,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteBytes(a_bytes);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto AppendAllTextToFile(std::filesystem::path a_filePath, std::string_view a_text) noexcept -> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Append,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteText(a_text);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto AppendAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string> a_lines) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Append,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteLines(a_lines);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto AppendAllLinesToFile(std::filesystem::path a_filePath, std::span<const std::string_view> a_lines) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Append,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteLines(a_lines);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto AppendAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::byte> a_bytes) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Append,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteBytes(a_bytes);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto AppendAllBytesToFile(std::filesystem::path a_filePath, std::span<const std::uint8_t> a_bytes) noexcept
		-> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Append,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteBytes(a_bytes);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto AppendLineToFile(std::filesystem::path a_filePath, std::string_view a_line) noexcept -> REX::SystemError
	{
		const auto createDirsResult = REX::CreateParentDirectories(a_filePath);
		if (!createDirsResult.has_value() && createDirsResult.error().value() != REX::ERROR_NUMBER_SUCCESS) {
			return createDirsResult.error();
		}

		auto fileStream = REX::FileStream::Open(
			std::move(a_filePath),
			REX::FileMode::Append,
			REX::FileAccess::Write,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			return fileStream.error();
		}

		const auto writeError = fileStream->WriteLine(a_line);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeError;
		}

		const auto closeError = fileStream->Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return closeError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FindFilesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_fileNamePattern,
		bool a_recursive) noexcept -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>
	{
		return Impl::FindDirectoryEntries(
			a_directoryPath,
			a_fileNamePattern,
			[](const std::filesystem::directory_entry& a_dirEntry) noexcept
				-> std::expected<REX::ForEachResult, REX::SystemError> {
				auto isFileError = REX::SystemError();
				if (!a_dirEntry.is_regular_file(isFileError)) {
					return REX::ForEachResult::Break;
				}

				return REX::ForEachResult::Continue;
			},
			a_recursive);
	}

	auto FindDirectoriesInDirectory(
		const std::filesystem::path& a_directoryPath,
		const std::filesystem::path& a_directoryNamePattern,
		bool a_recursive) noexcept -> std::expected<std::vector<std::filesystem::path>, REX::SystemError>
	{
		return Impl::FindDirectoryEntries(
			a_directoryPath,
			a_directoryNamePattern,
			[](const std::filesystem::directory_entry& a_dirEntry) noexcept
				-> std::expected<REX::ForEachResult, REX::SystemError> {
				auto isDirectoryError = REX::SystemError();
				if (!a_dirEntry.is_directory(isDirectoryError)) {
					return REX::ForEachResult::Break;
				}

				return REX::ForEachResult::Continue;
			},
			a_recursive);
	}

	auto ForEachEntryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
		const std::filesystem::path& a_entryNamePattern,
		bool a_recursive) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>
	{
		return Impl::ForEachDirectoryEntry(a_directoryPath, a_entryNamePattern, a_predicate, a_recursive);
	}

	auto ForEachFileInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
		const std::filesystem::path& a_fileNamePattern,
		bool a_recursive) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>
	{
		return Impl::ForEachDirectoryEntry(
			a_directoryPath,
			a_fileNamePattern,
			[&a_predicate](const std::filesystem::directory_entry& a_dirEntry) noexcept
				-> std::expected<REX::ForEachResult, REX::SystemError> {
				auto isFileError = REX::SystemError();
				if (!a_dirEntry.is_regular_file(isFileError)) {
					return REX::ForEachResult::Break;
				}

				return std::invoke(a_predicate.get(), a_dirEntry);
			},
			a_recursive);
	}

	auto ForEachDirectoryInDirectory(
		const std::filesystem::path& a_directoryPath,
		const REX::NotNull<std::move_only_function<DirectoryEntryPredicate>>& a_predicate,
		const std::filesystem::path& a_directoryNamePattern,
		bool a_recursive) noexcept -> std::expected<REX::ForEachResult, REX::SystemError>
	{
		return Impl::ForEachDirectoryEntry(
			a_directoryPath,
			a_directoryNamePattern,
			[&a_predicate](const std::filesystem::directory_entry& a_dirEntry) noexcept
				-> std::expected<REX::ForEachResult, REX::SystemError> {
				auto isDirectoryError = REX::SystemError();
				if (!a_dirEntry.is_directory(isDirectoryError)) {
					return REX::ForEachResult::Break;
				}

				return std::invoke(a_predicate.get(), a_dirEntry);
			},
			a_recursive);
	}

	auto RotateFile(const std::filesystem::path& a_filePath, std::size_t a_fileRotationCount) noexcept
		-> REX::SystemError
	{
		return RotateFile(a_filePath, a_fileRotationCount, "{:s}.{:d}{:s}"sv);
	}

	auto RotateFile(
		const std::filesystem::path& a_filePath,
		std::size_t a_fileRotationCount,
		REX::FormatString<std::string_view, std::size_t, std::string_view> a_fileRotationFormat) noexcept
		-> REX::SystemError
	{
		if (a_fileRotationCount == 0) {
			auto truncateError = REX::SystemError();
			std::filesystem::resize_file(a_filePath, 0, truncateError);
			return truncateError;
		}

		const auto fileParentPath = REX::TryCatch<std::bad_alloc>(
			[&a_filePath]() -> std::expected<std::filesystem::path, REX::SystemError> {
				return a_filePath.parent_path();
			},
			[](const std::bad_alloc& a_error) noexcept -> std::expected<std::filesystem::path, REX::SystemError> {
				std::ignore = a_error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			});

		if (!fileParentPath.has_value()) [[unlikely]] {
			return fileParentPath.error();
		}

		const auto fileStemPath = REX::TryCatch<std::bad_alloc>(
			[&a_filePath]() -> std::expected<std::string, REX::SystemError> {
				return a_filePath.stem().generic_string();
			},
			[](const std::bad_alloc& a_error) noexcept -> std::expected<std::string, REX::SystemError> {
				std::ignore = a_error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			});

		if (!fileStemPath.has_value()) [[unlikely]] {
			return fileStemPath.error();
		}

		const auto fileExtension = REX::TryCatch<std::bad_alloc>(
			[&a_filePath]() -> std::expected<std::string, REX::SystemError> {
				return a_filePath.extension().generic_string();
			},
			[](const std::bad_alloc& a_error) noexcept -> std::expected<std::string, REX::SystemError> {
				std::ignore = a_error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			});

		if (!fileExtension.has_value()) [[unlikely]] {
			return fileExtension.error();
		}

		const auto getRotatedFilePath =
			[&a_fileRotationFormat, &fileStemPath, &fileExtension, &fileParentPath](
				std::size_t a_index) noexcept -> std::expected<std::filesystem::path, REX::SystemError> {
			try {
				const auto fileName = std::filesystem::path(
					REX::Format(
						a_fileRotationFormat,
						std::string_view(fileStemPath.value()),
						static_cast<std::size_t>(a_index), // NOLINT(readability-redundant-casting)
						std::string_view(fileExtension.value())),
					std::filesystem::path::generic_format);

				return fileParentPath.value() / fileName;
			}
			catch (const std::bad_alloc& a_error) {
				std::ignore = a_error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}
		};

		const auto deleteFilePathResult = getRotatedFilePath(a_fileRotationCount);
		if (!deleteFilePathResult.has_value()) [[unlikely]] {
			return deleteFilePathResult.error();
		}

		auto deleteError = REX::SystemError();
		std::filesystem::remove(deleteFilePathResult.value(), deleteError);

		if (deleteError.value() != REX::ERROR_NUMBER_SUCCESS &&
			deleteError != REX::PosixErrorCode::no_such_file_or_directory) [[unlikely]] {
			return deleteError;
		}

		for (auto i = a_fileRotationCount; i > 1; i--) {
			const auto oldFilePathResult = getRotatedFilePath(i - 1);
			if (!oldFilePathResult.has_value()) [[unlikely]] {
				return oldFilePathResult.error();
			}

			const auto newFilePathResult = getRotatedFilePath(i);
			if (!newFilePathResult.has_value()) [[unlikely]] {
				return newFilePathResult.error();
			}

			auto renameError = REX::SystemError();
			std::filesystem::rename(oldFilePathResult.value(), newFilePathResult.value(), renameError);

			if (renameError.value() != REX::ERROR_NUMBER_SUCCESS &&
				renameError != REX::PosixErrorCode::no_such_file_or_directory) [[unlikely]] {
				return renameError;
			}
		}

		const auto currentFilePathResult = getRotatedFilePath(1);
		if (!currentFilePathResult.has_value()) [[unlikely]] {
			return currentFilePathResult.error();
		}

		auto renameError = REX::SystemError();
		std::filesystem::rename(a_filePath, currentFilePathResult.value(), renameError);
		return renameError;
	}
}
