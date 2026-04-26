#pragma once

#include "REX/ErrorCode.hpp"

namespace REX
{
	inline constexpr auto TRANSLATION_KEY_PREFIX = L'$';
	inline constexpr auto TRANSLATION_PAIR_SEPARATOR = L'\t';

	[[nodiscard]] auto ReadTranslationFile(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::wstring, std::wstring>>, REX::SystemError>;
	REX::SystemError WriteTranslationFile(const std::filesystem::path& a_filePath, std::span<const std::pair<std::wstring, std::wstring>> a_data) noexcept;
}
