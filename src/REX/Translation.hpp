#pragma once

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"
#include "REX/Localization.hpp"

namespace REX
{
	template <REX::win32_character CharT>
	inline constexpr auto TRANSLATION_KEY_PREFIX = static_cast<CharT>('$');

	template <REX::win32_character CharT>
	inline constexpr auto TRANSLATION_PAIR_SEPARATOR = REX::TAB_CHAR<CharT>;

	template <REX::win32_character CharT>
	[[nodiscard]]
	auto ReadTranslationFile(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::basic_string<CharT>, std::basic_string<CharT>>>, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto ReadTranslationFile<char>(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::string, std::string>>, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto ReadTranslationFile<wchar_t>(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::wstring, std::wstring>>, REX::SystemError>;

	template <REX::win32_character CharT>
	auto WriteTranslationFile(
		const std::filesystem::path& a_filePath,
		std::span<const std::pair<std::basic_string<CharT>, std::basic_string<CharT>>> a_data) noexcept
		-> REX::SystemError;

	template <>
	auto WriteTranslationFile<char>(
		const std::filesystem::path& a_filePath,
		std::span<const std::pair<std::string, std::string>> a_data) noexcept -> REX::SystemError;

	template <>
	auto WriteTranslationFile<wchar_t>(
		const std::filesystem::path& a_filePath,
		std::span<const std::pair<std::wstring, std::wstring>> a_data) noexcept -> REX::SystemError;
}
