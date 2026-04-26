#pragma once

#if __clang__ == 1
static_assert(true, "This is a workaround: https://github.com/clangd/clangd/issues/1167");
#endif

#if _MSC_VER > 0l
#pragma pack(push, 1)
#endif

#include "REL/Memory.hpp"

namespace REL::Asm
{
	template <std::uint8_t OP>
	struct Branch5 final
	{
	public:
		inline static constexpr auto OP_CODE = OP;

		constexpr explicit Branch5(std::int32_t a_disp) noexcept
			: disp(a_disp)
		{
		}

		constexpr explicit Branch5(std::uintptr_t a_address, std::uintptr_t a_func) noexcept
			: disp(static_cast<std::int32_t>(a_func - (a_address + sizeof(Branch5))))
		{
		}

		constexpr ~Branch5() noexcept = default;

		constexpr Branch5(const Branch5&) noexcept = default;
		constexpr Branch5(Branch5&&) noexcept = default;

		constexpr Branch5& operator=(const Branch5&) noexcept = default;
		constexpr Branch5& operator=(Branch5&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Branch5&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Branch5&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Branch5&) const noexcept = default;

		[[nodiscard]] static constexpr std::uintptr_t TARGET(std::uintptr_t a_address) noexcept
		{
			const auto* branch = std::bit_cast<const Branch5*>(a_address);
			if (!branch || branch->op != OP_CODE) {
				return REL::INVALID_ADDRESS;
			}

			const auto* begin = std::bit_cast<const std::byte*>(a_address);
			const auto address = (begin + sizeof(Branch5)) + branch->disp;
			return std::bit_cast<std::uintptr_t>(address);
		}

		constexpr void swap(Branch5& a_other) noexcept
		{
			std::swap(op, a_other.op);
			std::swap(disp, a_other.disp);
		}

		// members
		std::uint8_t op{ OP_CODE }; // 00
		std::int32_t disp{ 0x00 };	// 01
	};

	using Call5 = Branch5<0xE8>;
	static_assert(sizeof(Call5) == 0x05);

	using Jump5 = Branch5<0xE9>;
	static_assert(sizeof(Jump5) == 0x05);

	template <std::uint8_t OP>
	constexpr void swap(Branch5<OP>& a_lhs, Branch5<OP>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <std::uint8_t RM>
	struct Branch6 final
	{
	public:
		inline static constexpr auto OP_CODE = 0xFF;
		inline static constexpr auto RM_CODE = RM;

		constexpr explicit Branch6(std::int32_t a_disp) noexcept
			: disp(a_disp)
		{
		}

		constexpr explicit Branch6(std::uintptr_t a_address, std::uintptr_t a_func) noexcept
			: disp(static_cast<std::int32_t>(a_func - (a_address + sizeof(Branch6))))
		{
		}

		constexpr ~Branch6() noexcept = default;

		constexpr Branch6(const Branch6&) noexcept = default;
		constexpr Branch6(Branch6&&) noexcept = default;

		constexpr Branch6& operator=(const Branch6&) noexcept = default;
		constexpr Branch6& operator=(Branch6&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Branch6&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Branch6&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Branch6&) const noexcept = default;

		[[nodiscard]] static constexpr std::uintptr_t TARGET(std::uintptr_t a_address) noexcept
		{
			const auto* branch = std::bit_cast<const Branch6*>(a_address);
			if (!branch || branch->op != OP_CODE) {
				return REL::INVALID_ADDRESS;
			}

			const auto* begin = std::bit_cast<const std::byte*>(a_address);
			const auto address = (begin + sizeof(Branch6)) + branch->disp;
			return std::bit_cast<std::uintptr_t>(address);
		}

		constexpr void swap(Branch6& a_other) noexcept
		{
			std::swap(op, a_other.op);
			std::swap(rm, a_other.rm);
			std::swap(disp, a_other.disp);
		}

		// members
		std::uint8_t op{ OP_CODE }; // 00
		std::uint8_t rm{ RM_CODE }; // 01
		std::int32_t disp{ 0x00 };	// 02
	};

	using Call6 = Branch6<0x15>;
	static_assert(sizeof(Call6) == 0x06);

	using Jump6 = Branch6<0x25>;
	static_assert(sizeof(Jump6) == 0x06);

	template <std::uint8_t RM>
	constexpr void swap(Branch6<RM>& a_lhs, Branch6<RM>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	struct Call16 final
	{
	public:
		constexpr explicit Call16(std::uintptr_t a_address) noexcept
			: addr(a_address)
		{
		}

		template <class T>
		constexpr explicit Call16(const T* a_func) noexcept
			: Call16(std::bit_cast<std::uintptr_t>(a_func))
		{
		}

		constexpr ~Call16() noexcept = default;

		constexpr Call16(const Call16&) noexcept = default;
		constexpr Call16(Call16&&) noexcept = default;

		constexpr Call16& operator=(const Call16&) noexcept = default;
		constexpr Call16& operator=(Call16&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Call16&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Call16&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Call16&) const noexcept = default;

		constexpr void swap(Call16& a_other) noexcept
		{
			std::swap(call, a_other.call);
			std::swap(op, a_other.op);
			std::swap(disp, a_other.disp);
			std::swap(addr, a_other.addr);
		}

		// members
		Call6 call{ 0x02 };			 // 00
		std::uint8_t op{ 0xEB };	 // 06
		std::int8_t disp{ 0x08 };	 // 07
		std::uintptr_t addr{ 0x00 }; // 08 - [rip]
	};
	static_assert(sizeof(Call16) == 0x10);

	constexpr void swap(Call16& a_lhs, Call16& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	struct Jump14 final
	{
	public:
		constexpr explicit Jump14(std::uintptr_t a_address) noexcept
			: addr(a_address)
		{
		}

		template <class T>
		constexpr explicit Jump14(const T* a_func) noexcept
			: Jump14(std::bit_cast<std::uintptr_t>(a_func))
		{
		}

		constexpr ~Jump14() noexcept = default;

		constexpr Jump14(const Jump14&) noexcept = default;
		constexpr Jump14(Jump14&&) noexcept = default;

		constexpr Jump14& operator=(const Jump14&) noexcept = default;
		constexpr Jump14& operator=(Jump14&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Jump14&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Jump14&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Jump14&) const noexcept = default;

		constexpr void swap(Jump14& a_other) noexcept
		{
			std::swap(jmp, a_other.jmp);
			std::swap(addr, a_other.addr);
		}

		// members
		Jump6 jmp{ 0x00 };			 // 00
		std::uintptr_t addr{ 0x00 }; // 06 - [rip]
	};
	static_assert(sizeof(Jump14) == 0x0E);

	constexpr void swap(Jump14& a_lhs, Jump14& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if _MSC_VER > 0l
#pragma pack(pop)
#endif
