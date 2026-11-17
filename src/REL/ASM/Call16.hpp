#pragma once

#include "REL/ASM/Call6.hpp"

namespace REL::ASM
{
	class Call16 final
	{
	public:
		constexpr explicit Call16(std::uintptr_t a_address) noexcept :
			address(std::bit_cast<std::array<std::uint8_t, sizeof(std::uintptr_t)>>(a_address))
		{
		}

		template <class T>
		constexpr explicit Call16(const T* a_func) noexcept :
			Call16(std::bit_cast<std::uintptr_t>(a_func))
		{
		}

		constexpr ~Call16() noexcept = default;

		constexpr Call16(const Call16&) noexcept = default;
		constexpr Call16(Call16&&) noexcept = default;

		constexpr auto operator=(const Call16&) noexcept -> Call16& = default;
		constexpr auto operator=(Call16&&) noexcept -> Call16& = default;

		[[nodiscard]]
		constexpr auto operator==(const Call16&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Call16&) const noexcept = default;

		constexpr void swap(Call16& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(call, a_other.call);
			std::swap(opCode, a_other.opCode);
			std::swap(disposition, a_other.disposition);
			std::swap(address, a_other.address);
		}

		// members
		Call6 call{0x02};												// 0x00
		std::uint8_t opCode{0xEB};										// 0x06
		std::uint8_t disposition{0x08};									// 0x07
		std::array<std::uint8_t, sizeof(std::uintptr_t)> address{0x00}; // 0x08 - [rip]
	};

	static_assert(sizeof(Call16) == 0x10);
}
