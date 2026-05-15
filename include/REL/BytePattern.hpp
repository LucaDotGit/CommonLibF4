#pragma once

#include "REL/Module.hpp"

#include "REX/Concepts.hpp"
#include "REX/Locale.hpp"
#include "REX/Message.hpp"
#include "REX/SourceLocation.hpp"
#include "REX/StaticString.hpp"

namespace REL::Impl::Characters
{
	[[nodiscard]] constexpr bool IsHexadecimal(char a_char) noexcept
	{
		return REX::IsHexadecimal(a_char);
	}

	[[nodiscard]] constexpr bool IsSpace(char a_char) noexcept
	{
		return a_char == ' ';
	}

	[[nodiscard]] constexpr bool IsWildcard(char a_char) noexcept
	{
		return a_char == '?';
	}
}

namespace REL::Impl::Rules::Impl
{
	[[nodiscard]] constexpr std::uint8_t HexacharactersToHexadecimal(char a_highChar, char a_lowChar) noexcept
	{
		static constexpr auto LUT = []() consteval noexcept {
			auto array = std::array<std::uint8_t, std::numeric_limits<unsigned char>::max() + 1>();

			const auto iterate = [&array](std::uint8_t a_firstByte, unsigned char a_firstChar, unsigned char a_lastChar) noexcept -> void {
				for (; a_firstChar <= a_lastChar; a_firstChar++, a_firstByte++) {
					array[a_firstChar] = a_firstByte;
				}
			};

			iterate(0, '0', '9');
			iterate(0xA, 'a', 'f');
			iterate(0xA, 'A', 'F');

			return array;
		}();

		return static_cast<std::uint8_t>(
			(LUT[static_cast<unsigned char>(a_highChar)] * 0x10) +
			LUT[static_cast<unsigned char>(a_lowChar)]);
	}
}

namespace REL::Impl::Rules
{
	template <char High, char Low>
	class Hexadecimal final
	{
	public:
		Hexadecimal() = delete;

		[[nodiscard]] static constexpr bool Match(std::uint8_t a_byte) noexcept
		{
			constexpr auto EXPECTED = Impl::HexacharactersToHexadecimal(High, Low);
			return a_byte == EXPECTED;
		}
	};

	static_assert(Hexadecimal<'5', '7'>::Match(0x57));
	static_assert(Hexadecimal<'6', '5'>::Match(0x65));
	static_assert(Hexadecimal<'B', 'D'>::Match(0xBD));
	static_assert(Hexadecimal<'1', 'C'>::Match(0x1C));
	static_assert(Hexadecimal<'F', '2'>::Match(0xF2));
	static_assert(Hexadecimal<'9', 'f'>::Match(0x9F));

	static_assert(!Hexadecimal<'D', '4'>::Match(0xF8));
	static_assert(!Hexadecimal<'6', '7'>::Match(0xAA));
	static_assert(!Hexadecimal<'7', '8'>::Match(0xE3));
	static_assert(!Hexadecimal<'6', 'E'>::Match(0x61));

	class Wildcard final
	{
	public:
		Wildcard() = delete;

		[[nodiscard]] static constexpr bool Match([[maybe_unused]] std::uint8_t a_byte) noexcept
		{
			return true;
		}
	};

	static_assert(Wildcard::Match(0xB9));
	static_assert(Wildcard::Match(0x96));
	static_assert(Wildcard::Match(0x35));
	static_assert(Wildcard::Match(0xE4));

	template <char, char>
	constexpr void RuleFor() noexcept;

	template <char C1, char C2>
	[[nodiscard]] constexpr Hexadecimal<C1, C2> RuleFor() noexcept
		requires(Characters::IsHexadecimal(C1) && Characters::IsHexadecimal(C2));

	template <char C1, char C2>
	[[nodiscard]] constexpr Wildcard RuleFor() noexcept
		requires(Characters::IsWildcard(C1) && Characters::IsWildcard(C2));
}

namespace REL::Impl
{
	template <class... Rules>
	class PatternMatcher final
	{
	public:
		static_assert(sizeof...(Rules) >= 1, "At least one rule must be applied for the byte pattern matcher.");

		[[nodiscard]] constexpr bool Match(std::span<const std::uint8_t, sizeof...(Rules)> a_bytes) const noexcept
		{
			auto i = static_cast<std::size_t>(0);
			return (Rules::Match(a_bytes[i++]) && ...);
		}

		[[nodiscard]] constexpr bool Match(std::uintptr_t a_address) const noexcept
		{
			const auto bytes = std::span<const std::uint8_t, sizeof...(Rules)>{
				std::bit_cast<const std::uint8_t*>(a_address), sizeof...(Rules)
			};

			return Match(bytes);
		}

		constexpr void MatchOrFail(std::uintptr_t a_address, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) const noexcept
		{
			if (Match(a_address)) [[likely]] {
				return;
			}

			const auto& module = REL::Module::GetSingleton();
			const auto moduleVersion = module->GetVersion();

			REX::Impl::Fail(
				a_location,
				"A byte pattern has failed to match.\n"
				"This means the plugin is incompatible with either\n"
				"the current version of the executable ({})\n"
				"or another installed module.\n"
				"Address: 0x{:X}"sv,
				moduleVersion,
				a_address);
		}
	};

	template <REX::StaticString String, class... Rules>
	[[nodiscard]] consteval auto CreatePattern() noexcept
	{
		if constexpr (String.size() == 0) {
			return PatternMatcher<Rules...>();
		}
		else if constexpr (String.size() == 1) {
			constexpr auto FIRST_CHAR = String[0];
			if constexpr (Characters::IsHexadecimal(FIRST_CHAR) || Characters::IsWildcard(FIRST_CHAR)) {
				static_assert(false, "The given byte pattern has an unpaired rule.");
			}
			else {
				static_assert(false, "The given byte pattern has trailing characters at the end.");
			}
		}
		else {
			using rule_t = decltype(Impl::Rules::RuleFor<String[0], String[1]>());
			if constexpr (std::same_as<rule_t, void>) {
				static_assert(false, "The given byte pattern failed to match any known rules.");
			}
			else {
				if constexpr (String.size() <= 3) {
					return CreatePattern<String.template substr<2>(), Rules..., rule_t>();
				}
				else if constexpr (Characters::IsSpace(String[2])) {
					return CreatePattern<String.template substr<3>(), Rules..., rule_t>();
				}
				else {
					static_assert(false, "A space character is required to split byte patterns.");
				}
			}
		}
	}
}

namespace REL
{
	template <REX::integer... Bytes>
	[[nodiscard]] consteval auto CreateByteArray(Bytes... a_bytes) noexcept
		-> std::array<std::uint8_t, sizeof...(Bytes)>
	{
		return { static_cast<std::uint8_t>(a_bytes)... };
	}

	template <REX::StaticString String>
	[[nodiscard]] consteval auto CreateBytePattern() noexcept
	{
		return Impl::CreatePattern<String>();
	}
}
