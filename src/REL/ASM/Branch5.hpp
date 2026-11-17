#pragma once

#include "REL/Memory.hpp"

namespace REL::ASM
{
	template <std::uint8_t OP>
	class Branch5 final
	{
	public:
		inline static constexpr auto OP_CODE = OP;

		constexpr explicit Branch5(std::int32_t a_disposition) noexcept :
			disposition(std::bit_cast<std::array<std::uint8_t, sizeof(std::int32_t)>>(a_disposition))
		{
		}

		constexpr explicit Branch5(std::uintptr_t a_address, std::uintptr_t a_func) noexcept :
			disposition(
				std::bit_cast<std::array<std::uint8_t, sizeof(std::int32_t)>>(
					static_cast<std::int32_t>(a_func - (a_address + sizeof(Branch5)))))
		{
		}

		constexpr ~Branch5() noexcept = default;

		constexpr Branch5(const Branch5&) noexcept = default;
		constexpr Branch5(Branch5&&) noexcept = default;

		constexpr auto operator=(const Branch5&) noexcept -> Branch5& = default;
		constexpr auto operator=(Branch5&&) noexcept -> Branch5& = default;

		[[nodiscard]]
		constexpr auto operator==(const Branch5&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Branch5&) const noexcept = default;

		constexpr void swap(Branch5& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(opCode, a_other.opCode);
			std::swap(disposition, a_other.disposition);
		}

		[[nodiscard]]
		static constexpr auto TARGET(std::uintptr_t a_address) noexcept -> std::uintptr_t
		{
			const auto* branch = std::bit_cast<const Branch5*>(a_address);
			if (!branch || branch->opCode != OP_CODE) {
				return REL::INVALID_ADDRESS;
			}

			const auto* begin = std::bit_cast<const std::byte*>(a_address);
			const auto* address = (begin + sizeof(Branch5)) + std::bit_cast<std::int32_t>(branch->disposition);
			return std::bit_cast<std::uintptr_t>(address);
		}

		// members
		std::uint8_t opCode{OP_CODE};									  // 0x00
		std::array<std::uint8_t, sizeof(std::int32_t)> disposition{0x00}; // 0x01
	};
}
