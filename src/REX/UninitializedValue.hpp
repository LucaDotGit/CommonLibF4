#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	template <REX::trivially_readable T>
	class UninitializedValue final
	{
	public:
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init, modernize-use-equals-default)
		constexpr UninitializedValue() noexcept
		{
		}

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr UninitializedValue(T a_value) noexcept :
			value(a_value)
		{
		}

		constexpr ~UninitializedValue() noexcept = default;

		constexpr UninitializedValue(const UninitializedValue&) noexcept = default;
		constexpr UninitializedValue(UninitializedValue&&) noexcept = default;

		constexpr auto operator=(const UninitializedValue&) noexcept -> UninitializedValue& = default;
		constexpr auto operator=(UninitializedValue&&) noexcept -> UninitializedValue& = default;

		[[nodiscard]]
		constexpr auto operator==(const UninitializedValue&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const UninitializedValue&) const noexcept = default;

		[[nodiscard]]
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr operator T() const noexcept
		{
			return value;
		}

		T value;
	};

	static_assert(sizeof(UninitializedValue<std::byte>) == sizeof(std::byte));
}
