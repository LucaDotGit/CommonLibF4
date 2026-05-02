#include "REX/Translate.hpp"

namespace REX
{
	static constexpr auto UTF16_BOM = L'\uFEFF';

	static_assert(sizeof(wchar_t) == sizeof(std::uint16_t));

	auto ReadTranslationFile(const std::filesystem::path& a_filePath) noexcept
		-> std::expected<std::vector<std::pair<std::wstring, std::wstring>>, REX::SystemError>
	{
		auto stream = std::fstream(a_filePath, std::ios::in | std::ios::binary);
		if (!stream.is_open()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_file_or_directory));
		}

		{
			auto bom = L'\0';

			stream.read(reinterpret_cast<char*>(std::addressof(bom)), sizeof(bom));
			if (stream.bad()) {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::io_error));
			}

			if (bom != UTF16_BOM) {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::illegal_byte_sequence));
			}
		}

		auto contentBytes = std::vector<char>();

		try {
			contentBytes = { std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() };
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		if (stream.bad()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::io_error));
		}

		if ((contentBytes.size() % sizeof(wchar_t)) != 0) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::illegal_byte_sequence));
		}

		const auto content = std::wstring_view{ reinterpret_cast<const wchar_t*>(contentBytes.data()), contentBytes.size() / sizeof(wchar_t) };

		auto result = std::vector<std::pair<std::wstring, std::wstring>>();
		for (const auto linePart : std::ranges::views::split(content, L'\n')) {
			const auto line = std::wstring_view{ linePart.begin(), linePart.end() };
			if (line.empty()) {
				continue;
			}

			const auto separatorPos = line.find(TRANSLATION_PAIR_SEPARATOR);
			if (separatorPos == std::wstring::npos) {
				continue;
			}

			const auto key = line.substr(0, separatorPos);
			const auto value = line.substr(separatorPos + 1);

			if (key.empty() || key.front() != TRANSLATION_KEY_PREFIX) {
				continue;
			}

			try {
				if (value.ends_with(L'\r')) {
					result.emplace_back(key, value.substr(0, value.size() - 1));
					continue;
				}

				result.emplace_back(key, value);
			}
			catch ([[maybe_unused]] const std::bad_alloc& error) {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}
		}

		return result;
	}

	REX::SystemError WriteTranslationFile(const std::filesystem::path& a_filePath, std::span<const std::pair<std::wstring, std::wstring>> a_data) noexcept
	{
		auto stream = std::fstream(a_filePath, std::ios::out | std::ios::trunc | std::ios::binary);
		if (!stream.is_open()) {
			return REX::CreateSystemError(REX::PosixErrorCode::io_error);
		}

		auto content = std::wstring();

		for (const auto& [key, value] : a_data) {
			if (key.empty() || key.front() != TRANSLATION_KEY_PREFIX) {
				continue;
			}

			try {
				content += REX::Format(L"{}{}{}\n"sv,
					key, TRANSLATION_PAIR_SEPARATOR, value);
			}
			catch ([[maybe_unused]] const std::bad_alloc& error) {
				return REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory);
			}
		}

		stream.write(reinterpret_cast<const char*>(std::addressof(UTF16_BOM)), sizeof(UTF16_BOM));
		if (!stream.good()) {
			return REX::CreateSystemError(REX::PosixErrorCode::io_error);
		}

		stream.write(reinterpret_cast<const char*>(content.data()), static_cast<std::streamsize>(content.size() * sizeof(wchar_t)));
		if (!stream.good()) {
			return REX::CreateSystemError(REX::PosixErrorCode::io_error);
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}
}
