#include "REX/Compare.hpp"

namespace REX
{
	template bool IsNullOrEmpty<char>(const char*) noexcept;
	template bool IsNullOrEmpty<wchar_t>(const wchar_t*) noexcept;

	template bool IsNullOrEmpty(std::string_view) noexcept;
	template bool IsNullOrEmpty(std::wstring_view) noexcept;

	template bool IsNullOrWhiteSpace(std::string_view) noexcept;
	template bool IsNullOrWhiteSpace(std::wstring_view) noexcept;

	template bool IsNullTerminated(std::string_view) noexcept;
	template bool IsNullTerminated(std::wstring_view) noexcept;

	template bool EqualsIgnoreCase(std::string_view, std::string_view) noexcept;
	template bool EqualsIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template auto CompareIgnoreCase(std::string_view, std::string_view) noexcept;
	template auto CompareIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template bool Contains(std::string_view, std::string_view) noexcept;
	template bool Contains(std::wstring_view, std::wstring_view) noexcept;

	template bool ContainsIgnoreCase(std::string_view, std::string_view) noexcept;
	template bool ContainsIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template bool StartsWith(std::string_view, std::string_view) noexcept;
	template bool StartsWith(std::wstring_view, std::wstring_view) noexcept;

	template bool StartsWithIgnoreCase(std::string_view, std::string_view) noexcept;
	template bool StartsWithIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template bool EndsWith(std::string_view, std::string_view) noexcept;
	template bool EndsWith(std::wstring_view, std::wstring_view) noexcept;

	template bool EndsWithIgnoreCase(std::string_view, std::string_view) noexcept;
	template bool EndsWithIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template std::size_t Find(std::string_view, std::string_view, std::size_t) noexcept;
	template std::size_t Find(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template std::size_t FindIgnoreCase(std::string_view, std::string_view, std::size_t) noexcept;
	template std::size_t FindIgnoreCase(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template std::size_t FindLast(std::string_view, std::string_view, std::size_t) noexcept;
	template std::size_t FindLast(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template std::size_t FindLastIgnoreCase(std::string_view, std::string_view, std::size_t) noexcept;
	template std::size_t FindLastIgnoreCase(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template bool LessIgnoreCase::operator()(const std::string_view&, const std::string_view&) const noexcept;
	template bool LessIgnoreCase::operator()(const std::wstring_view&, const std::wstring_view&) const noexcept;
	template bool LessIgnoreCase::operator()(const std::string&, const std::string&) const noexcept;
	template bool LessIgnoreCase::operator()(const std::wstring&, const std::wstring&) const noexcept;

	template bool GreaterIgnoreCase::operator()(const std::string_view&, const std::string_view&) const noexcept;
	template bool GreaterIgnoreCase::operator()(const std::wstring_view&, const std::wstring_view&) const noexcept;
	template bool GreaterIgnoreCase::operator()(const std::string&, const std::string&) const noexcept;
	template bool GreaterIgnoreCase::operator()(const std::wstring&, const std::wstring&) const noexcept;
}
