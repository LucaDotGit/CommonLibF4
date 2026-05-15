#pragma once

#include "REX/Path.hpp"

namespace REX
{
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

	[[nodiscard]] consteval std::string_view GetCurrentFileName(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		return REX::GetFileName(a_filePath);
	}

	[[nodiscard]] consteval std::string_view GetCurrentFileNameWithoutExtension(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		return REX::GetFileNameWithoutExtension(a_filePath);
	}

	[[nodiscard]] consteval std::string_view GetCurrentFileExtension(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		return REX::GetFileExtension(a_filePath);
	}

	[[nodiscard]] consteval std::string_view GetCurrentDirectoryPath(std::string_view a_filePath = __builtin_FILE()) noexcept
	{
		return REX::GetDirectoryPath(a_filePath);
	}

	class SourceLocation final
	{
	public:
		constexpr SourceLocation(
			std::string_view a_filePath,
			std::string_view a_functionName,
			std::string_view a_functionSignature,
			std::uint_least32_t a_lineNumber,
			std::uint_least32_t a_columnNumber) noexcept
			: _filePath(a_filePath),
			  _functionName(a_functionName),
			  _functionSignature(a_functionSignature),
			  _lineNumber(a_lineNumber),
			  _columnNumber(a_columnNumber)
		{
		}

		constexpr ~SourceLocation() noexcept = default;

		constexpr SourceLocation(const SourceLocation&) noexcept = default;
		constexpr SourceLocation(SourceLocation&&) noexcept = default;

		constexpr SourceLocation& operator=(const SourceLocation&) noexcept = default;
		constexpr SourceLocation& operator=(SourceLocation&&) noexcept = default;

		[[nodiscard]] static consteval SourceLocation GetCurrent(
			std::string_view a_filePath = __builtin_FILE(),
			std::string_view a_functionName = __builtin_FUNCTION(),
			std::string_view a_functionSignature = __builtin_FUNCSIG(),
			std::uint_least32_t a_lineNumber = __builtin_LINE(),
			std::uint_least32_t a_columnNumber = __builtin_COLUMN()) noexcept
		{
			return {
				a_filePath,
				a_functionName,
				a_functionSignature,
				a_lineNumber,
				a_columnNumber
			};
		}

		[[nodiscard]] constexpr std::string_view GetFilePath() const noexcept { return _filePath; }
		[[nodiscard]] constexpr std::string_view GetFunctionName() const noexcept { return _functionName; }
		[[nodiscard]] constexpr std::string_view GetFunctionSignature() const noexcept { return _functionSignature; }
		[[nodiscard]] constexpr std::uint_least32_t GetLineNumber() const noexcept { return _lineNumber; }
		[[nodiscard]] constexpr std::uint_least32_t GetColumnNumber() const noexcept { return _columnNumber; }

	private:
		std::string_view _filePath;
		std::string_view _functionName;
		std::string_view _functionSignature;
		std::uint_least32_t _lineNumber;
		std::uint_least32_t _columnNumber;
	};
}
