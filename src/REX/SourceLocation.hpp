#pragma once

#include "REX/Path.hpp"

#define REX_CURRENT_FILE_PATH __builtin_FILE()
#define REX_CURRENT_FUNCTION_NAME __builtin_FUNCTION()
#define REX_CURRENT_FUNCTION_SIGNATURE __builtin_FUNCSIG()
#define REX_CURRENT_LINE_NUMBER __builtin_LINE()
#define REX_CURRENT_COLUMN_NUMBER __builtin_COLUMN()

namespace REX
{
	[[nodiscard]]
	consteval auto GetCurrentFilePath(std::string_view a_filePath = REX_CURRENT_FILE_PATH) noexcept -> std::string_view
	{
		return a_filePath;
	}

	[[nodiscard]]
	consteval auto GetCurrentFunctionName(std::string_view a_functionName = REX_CURRENT_FUNCTION_NAME) noexcept
		-> std::string_view
	{
		return a_functionName;
	}

	[[nodiscard]]
	consteval auto GetCurrentFunctionSignature(
		std::string_view a_functionSignature = REX_CURRENT_FUNCTION_SIGNATURE) noexcept -> std::string_view
	{
		return a_functionSignature;
	}

	[[nodiscard]]
	consteval auto GetCurrentLineNumber(std::uint_least32_t a_lineNumber = REX_CURRENT_LINE_NUMBER) noexcept
		-> std::uint_least32_t
	{
		return a_lineNumber;
	}

	[[nodiscard]]
	consteval auto GetCurrentColumnNumber(std::uint_least32_t a_columnNumber = REX_CURRENT_COLUMN_NUMBER) noexcept
		-> std::uint_least32_t
	{
		return a_columnNumber;
	}

	[[nodiscard]]
	consteval auto GetCurrentFileName(std::string_view a_filePath = REX_CURRENT_FILE_PATH) noexcept -> std::string_view
	{
		return REX::GetFileName(a_filePath);
	}

	[[nodiscard]]
	consteval auto GetCurrentFileNameWithoutExtension(std::string_view a_filePath = REX_CURRENT_FILE_PATH) noexcept
		-> std::string_view
	{
		return REX::GetFileNameWithoutExtension(a_filePath);
	}

	[[nodiscard]]
	consteval auto GetCurrentFileExtension(std::string_view a_filePath = REX_CURRENT_FILE_PATH) noexcept
		-> std::string_view
	{
		return REX::GetFileExtension(a_filePath);
	}

	[[nodiscard]]
	consteval auto GetCurrentDirectoryPath(std::string_view a_filePath = REX_CURRENT_FILE_PATH) noexcept
		-> std::string_view
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
			std::uint_least32_t a_columnNumber) noexcept :
			_filePath(a_filePath),
			_functionName(a_functionName),
			_functionSignature(a_functionSignature),
			_lineNumber(a_lineNumber),
			_columnNumber(a_columnNumber)
		{
		}

		constexpr ~SourceLocation() noexcept = default;

		constexpr SourceLocation(const SourceLocation&) noexcept = default;
		constexpr SourceLocation(SourceLocation&&) noexcept = default;

		constexpr auto operator=(const SourceLocation&) noexcept -> SourceLocation& = default;
		constexpr auto operator=(SourceLocation&&) noexcept -> SourceLocation& = default;

		[[nodiscard]]
		static consteval auto GetCurrent(
			std::string_view a_filePath = REX_CURRENT_FILE_PATH,
			std::string_view a_functionName = REX_CURRENT_FUNCTION_NAME,
			std::string_view a_functionSignature = REX_CURRENT_FUNCTION_SIGNATURE,
			std::uint_least32_t a_lineNumber = REX_CURRENT_LINE_NUMBER,
			std::uint_least32_t a_columnNumber = REX_CURRENT_COLUMN_NUMBER) noexcept -> SourceLocation
		{
			return {a_filePath, a_functionName, a_functionSignature, a_lineNumber, a_columnNumber};
		}

		[[nodiscard]]
		constexpr auto GetFilePath() const noexcept -> std::string_view
		{
			return _filePath;
		}

		[[nodiscard]]
		constexpr auto GetFunctionName() const noexcept -> std::string_view
		{
			return _functionName;
		}

		[[nodiscard]]
		constexpr auto GetFunctionSignature() const noexcept -> std::string_view
		{
			return _functionSignature;
		}

		[[nodiscard]]
		constexpr auto GetLineNumber() const noexcept -> std::uint_least32_t
		{
			return _lineNumber;
		}

		[[nodiscard]]
		constexpr auto GetColumnNumber() const noexcept -> std::uint_least32_t
		{
			return _columnNumber;
		}

	private:
		std::string_view _filePath;
		std::string_view _functionName;
		std::string_view _functionSignature;
		std::uint_least32_t _lineNumber;
		std::uint_least32_t _columnNumber;
	};
}
