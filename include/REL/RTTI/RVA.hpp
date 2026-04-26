#pragma once

#include "REL/Relocation.hpp"

namespace REL::RTTI
{
	template <class T>
	class RVA
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;

		constexpr RVA() noexcept = default;
		constexpr ~RVA() noexcept = default;

		constexpr RVA(std::uint32_t a_rva) noexcept
			: _rva(a_rva)
		{
		}

		constexpr RVA(const RVA&) noexcept = default;
		constexpr RVA(RVA&&) noexcept = default;

		constexpr RVA& operator=(const RVA&) noexcept = default;
		constexpr RVA& operator=(RVA&&) noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return good(); }

		[[nodiscard]] constexpr reference operator*() const noexcept
		{
			REX::Assert(good());
			return *get();
		}

		[[nodiscard]] constexpr pointer operator->() const noexcept
		{
			REX::Assert(good());
			return get();
		}

		[[nodiscard]] pointer get() const noexcept
		{
			if (!good()) {
				return nullptr;
			}

			const auto relocation = REL::Relocation<pointer>{ REL::Offset(_rva) };
			return relocation.get();
		}

		[[nodiscard]] constexpr std::uint32_t offset() const noexcept
		{
			return _rva;
		}

	protected:
		[[nodiscard]] constexpr bool good() const noexcept
		{
			return _rva != 0;
		}

		// members
		std::uint32_t _rva{ 0 }; // 00
	};
	static_assert(sizeof(RVA<std::any>) == 0x04);
}
