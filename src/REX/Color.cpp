#include "REX/Color.hpp"

#include "REX/Formatting.hpp"

namespace REX
{
	auto Color::ToHexRgbString(std::span<char> a_buffer) const noexcept -> std::string_view
	{
		if (a_buffer.size() < HEXADECIMAL_RGB_STRING_SIZE) {
			return {};
		}

		const auto formatResult = REX::FormatToN(
			a_buffer.begin(),
			static_cast<std::ptrdiff_t>(a_buffer.size()),
			"#{:02X}{:02X}{:02X}"sv,
			GetRed(),
			GetGreen(),
			GetBlue());

		return std::string_view{a_buffer.data(), static_cast<std::size_t>(formatResult.size)};
	}

	auto Color::ToHexRgbaString(std::span<char> a_buffer) const noexcept -> std::string_view
	{
		if (a_buffer.size() < HEXADECIMAL_RGBA_STRING_SIZE) {
			return {};
		}

		const auto formatResult = REX::FormatToN(
			a_buffer.begin(),
			static_cast<std::ptrdiff_t>(a_buffer.size()),
			"#{:02X}{:02X}{:02X}{:02X}"sv,
			GetRed(),
			GetGreen(),
			GetBlue(),
			GetAlpha());

		return std::string_view{a_buffer.data(), static_cast<std::size_t>(formatResult.size)};
	}

	auto Color::ToHexRgbString() const -> std::string
	{
		auto buffer = std::array<char, HEXADECIMAL_RGB_STRING_SIZE>();
		const auto bufferView = ToHexRgbString(buffer);
		return std::string(bufferView);
	}

	auto Color::ToHexRgbaString() const -> std::string
	{
		auto buffer = std::array<char, HEXADECIMAL_RGBA_STRING_SIZE>();
		const auto bufferView = ToHexRgbaString(buffer);
		return std::string(bufferView);
	}

	auto Color::ToString() const -> std::string
	{
		return ToHexRgbaString();
	}
}
