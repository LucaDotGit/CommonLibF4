#pragma once

#include "REL/ASM/Jump6.hpp"

namespace REL::ASM
{
	class Jump14 final
	{
	public:
		constexpr explicit Jump14(std::uintptr_t a_address) noexcept :
			address(std::bit_cast<std::array<std::uint8_t, sizeof(std::uintptr_t)>>(a_address))
		{
		}

		template <class T>
		constexpr explicit Jump14(const T* a_func) noexcept :
			Jump14(std::bit_cast<std::uintptr_t>(a_func))
		{
		}

		constexpr ~Jump14() noexcept = default;

		constexpr Jump14(const Jump14&) noexcept = default;
		constexpr Jump14(Jump14&&) noexcept = default;

		constexpr auto operator=(const Jump14&) noexcept -> Jump14& = default;
		constexpr auto operator=(Jump14&&) noexcept -> Jump14& = default;

		[[nodiscard]]
		constexpr auto operator==(const Jump14&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Jump14&) const noexcept = default;

		constexpr void swap(Jump14& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(jump, a_other.jump);
			std::swap(address, a_other.address);
		}

		// members
		Jump6 jump{0x00};												// 0x00
		std::array<std::uint8_t, sizeof(std::uintptr_t)> address{0x00}; // 0x06 - [rip]
	};

	static_assert(sizeof(Jump14) == 0x0E);
}
