#pragma once

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"

namespace REX
{
	template <REX::win32_character CharT>
	inline constexpr auto TRANSLATION_KEY_PREFIX = static_cast<CharT>('$');

	template <REX::win32_character CharT>
	inline constexpr auto TRANSLATION_PAIR_SEPARATOR = static_cast<CharT>('\t');

	[[nodiscard]] auto ReadTranslationFile(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::wstring, std::wstring>>, REX::SystemError>;
	REX::SystemError WriteTranslationFile(const std::filesystem::path& a_filePath, std::span<const std::pair<std::wstring, std::wstring>> a_data) noexcept;
}
