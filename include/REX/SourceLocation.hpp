#pragma once

namespace REX
{
	[[nodiscard]] consteval std::string_view GetCurrentFileName(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		constexpr auto WINDOWS_PATH_SEPARATOR = '\\';
		constexpr auto UNIX_PATH_SEPARATOR = '/';

		for (auto pathIt = a_filePath.end() - 1; pathIt >= a_filePath.begin(); pathIt--) {
			if (*pathIt == WINDOWS_PATH_SEPARATOR || *pathIt == UNIX_PATH_SEPARATOR) {
				return a_filePath.substr(static_cast<std::size_t>(pathIt - a_filePath.begin() + 1));
			}
		}

		return a_filePath;
	}

	[[nodiscard]] consteval std::string_view GetCurrentFileNameWithoutExtension(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		constexpr auto FILE_EXTENSION_SEPARATOR = '.';

		const auto fileName = GetCurrentFileName(a_filePath);
		for (auto pathIt = fileName.end() - 1; pathIt >= fileName.begin(); pathIt--) {
			if (*pathIt == FILE_EXTENSION_SEPARATOR) {
				return fileName.substr(0, static_cast<std::size_t>(pathIt - fileName.begin()));
			}
		}

		return fileName;
	}

	[[nodiscard]] consteval std::string_view GetCurrentFilePath(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		return a_filePath;
	}

	[[nodiscard]] consteval std::string_view GetCurrentFunctionName(std::string_view a_functionName = __builtin_FUNCTION()) noexcept
	{
		return a_functionName;
	}

	[[nodiscard]] consteval std::string_view GetCurrentFunctionSignature(std::string_view a_functionSignature = __builtin_FUNCSIG()) noexcept
	{
		return a_functionSignature;
	}

	[[nodiscard]] consteval std::uint_least32_t GetCurrentLineNumber(std::uint_least32_t a_lineNumber = __builtin_LINE()) noexcept
	{
		return a_lineNumber;
	}

	[[nodiscard]] consteval std::uint_least32_t GetCurrentColumnNumber(std::uint_least32_t a_columnNumber = __builtin_COLUMN()) noexcept
	{
		return a_columnNumber;
	}
}
