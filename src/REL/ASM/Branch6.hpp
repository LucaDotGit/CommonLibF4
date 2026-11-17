#pragma once

#include "REL/Memory.hpp"

namespace REL::ASM
{
	template <std::uint8_t RM>
	class Branch6 final
	{
	public:
		inline static constexpr auto OP_CODE = 0xFF;
		inline static constexpr auto RM_CODE = RM;

		constexpr explicit Branch6(std::int32_t a_disposition) noexcept :
			disposition(std::bit_cast<std::array<std::uint8_t, sizeof(std::int32_t)>>(a_disposition))
		{
		}

		constexpr explicit Branch6(std::uintptr_t a_address, std::uintptr_t a_func) noexcept :
			disposition(
				std::bit_cast<std::array<std::uint8_t, sizeof(std::int32_t)>>(
					static_cast<std::int32_t>(a_func - (a_address + sizeof(Branch6)))))
		{
		}

		constexpr ~Branch6() noexcept = default;

		constexpr Branch6(const Branch6&) noexcept = default;
		constexpr Branch6(Branch6&&) noexcept = default;

		constexpr auto operator=(const Branch6&) noexcept -> Branch6& = default;
		constexpr auto operator=(Branch6&&) noexcept -> Branch6& = default;

		[[nodiscard]]
		constexpr auto operator==(const Branch6&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Branch6&) const noexcept = default;

		constexpr void swap(Branch6& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(opCode, a_other.opCode);
			std::swap(rmCode, a_other.rmCode);
			std::swap(disposition, a_other.disposition);
		}

		[[nodiscard]]
		static constexpr auto TARGET(std::uintptr_t a_address) noexcept -> std::uintptr_t
		{
			const auto* branch = std::bit_cast<const Branch6*>(a_address);
			if (!branch || branch->opCode != OP_CODE) {
				return REL::INVALID_ADDRESS;
			}

			const auto* begin = std::bit_cast<const std::byte*>(a_address);
			const auto* address = (begin + sizeof(Branch6)) + std::bit_cast<std::int32_t>(branch->disposition);
			return std::bit_cast<std::uintptr_t>(address);
		}

		// members
		std::uint8_t opCode{OP_CODE};									  // 0x00
		std::uint8_t rmCode{RM_CODE};									  // 0x01
		std::array<std::uint8_t, sizeof(std::int32_t)> disposition{0x00}; // 0x02
	};
}
