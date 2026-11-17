#pragma once

#include "REL/Relocation.hpp"
#include "REX/Contract.hpp"

namespace REL::RTTI
{
	template <class T>
	class Rva final
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;

		constexpr Rva() noexcept = default;
		constexpr ~Rva() noexcept = default;

		constexpr explicit Rva(std::uint32_t a_rva) noexcept :
			_rva(a_rva)
		{
		}

		constexpr Rva(const Rva&) noexcept = default;
		constexpr Rva(Rva&&) noexcept = default;

		constexpr auto operator=(const Rva&) noexcept -> Rva& = default;
		constexpr auto operator=(Rva&&) noexcept -> Rva& = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return good();
		}

		[[nodiscard]]
		constexpr auto operator*() const noexcept -> reference
		{
			REX::Assert(good());
			return *get();
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> pointer
		{
			REX::Assert(good());
			return get();
		}

		[[nodiscard]]
		auto get() const noexcept -> pointer
		{
			if (!good()) {
				return nullptr;
			}

			const auto relocation = REL::Relocation<pointer>(REL::Offset(_rva));
			return relocation.get();
		}

		[[nodiscard]]
		constexpr auto offset() const noexcept -> std::uint32_t
		{
			return _rva;
		}

	protected:
		[[nodiscard]]
		constexpr auto good() const noexcept -> bool
		{
			return _rva != 0;
		}

		// members
		std::uint32_t _rva{0}; // 0x00
	};

	static_assert(sizeof(Rva<std::any>) == 0x04);
}
