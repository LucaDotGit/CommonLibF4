#include "REX/Translation.hpp"

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"
#include "REX/IO.hpp"
#include "REX/Localization.hpp"

namespace REX::Impl
{
	namespace
	{
		template <REX::win32_character CharT>
		auto ReadTranslationFile(const std::filesystem::path& a_filePath) noexcept -> std::expected<
			std::vector<std::pair<std::basic_string<CharT>, std::basic_string<CharT>>>,
			REX::SystemError>
		{
			const auto fileContent = REX::ReadAllTextFromFile<CharT>(a_filePath);
			if (!fileContent.has_value()) [[unlikely]] {
				return std::unexpected(fileContent.error());
			}

			auto result = std::vector<std::pair<std::basic_string<CharT>, std::basic_string<CharT>>>();

			for (const auto line : std::ranges::views::split(
					 std::basic_string_view<CharT>(fileContent.value()),
					 REX::NEWLINE_CHAR<CharT>)) {
				const auto lineView = std::basic_string_view<CharT>{line.begin(), line.end()};
				if (lineView.empty()) {
					continue;
				}

				const auto separatorPos = lineView.find(TRANSLATION_PAIR_SEPARATOR<CharT>);
				if (separatorPos == std::basic_string<CharT>::npos) {
					continue;
				}

				const auto key = lineView.substr(0, separatorPos);
				const auto value = lineView.substr(separatorPos + 1);

				if (key.empty() || key.front() != TRANSLATION_KEY_PREFIX<CharT>) {
					continue;
				}

				try {
					if (!value.ends_with(REX::CARRIAGE_RETURN_CHAR<CharT>)) {
						result.emplace_back(key, value);
						continue;
					}

					const auto trimmedValue = value.substr(0, value.size() - 1);
					result.emplace_back(key, trimmedValue);
				}
				catch (const std::bad_alloc& error) {
					std::ignore = error;
					return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
				}
			}

			return result;
		}

		template <REX::win32_character CharT>
		auto WriteTranslationFile(
			const std::filesystem::path& a_filePath,
			std::span<const std::pair<std::basic_string<CharT>, std::basic_string<CharT>>> a_data) noexcept
			-> REX::SystemError
		{
			auto fileContent = std::basic_string<CharT>();

			for (auto&& [key, value] : a_data) {
				if (key.empty() || key.front() != TRANSLATION_KEY_PREFIX<CharT>) {
					continue;
				}

				try {
					fileContent.reserve(fileContent.size() + key.size() + 1 + value.size() + 1);
				}
				catch (const std::bad_alloc& error) {
					std::ignore = error;
					return REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory);
				}

				fileContent += key;
				fileContent += TRANSLATION_PAIR_SEPARATOR<CharT>;
				fileContent += value;
				fileContent += REX::NEWLINE_CHAR<CharT>;
			}

			return REX::WriteAllTextToFile<CharT>(a_filePath, fileContent);
		}
	}
}

namespace REX
{
	template <>
	auto ReadTranslationFile<char>(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::string, std::string>>, REX::SystemError>
	{
		return Impl::ReadTranslationFile<char>(a_filePath);
	}

	template <>
	auto ReadTranslationFile<wchar_t>(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::wstring, std::wstring>>, REX::SystemError>
	{
		return Impl::ReadTranslationFile<wchar_t>(a_filePath);
	}

	template <>
	auto WriteTranslationFile<char>(
		const std::filesystem::path& a_filePath,
		std::span<const std::pair<std::string, std::string>> a_data) noexcept -> REX::SystemError
	{
		return Impl::WriteTranslationFile<char>(a_filePath, a_data);
	}

	template <>
	auto WriteTranslationFile<wchar_t>(
		const std::filesystem::path& a_filePath,
		std::span<const std::pair<std::wstring, std::wstring>> a_data) noexcept -> REX::SystemError
	{
		return Impl::WriteTranslationFile<wchar_t>(a_filePath, a_data);
	}
}
