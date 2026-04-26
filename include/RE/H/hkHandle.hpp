#pragma once

namespace RE
{
	template <class T, std::uint32_t Max, class Unk>
	class hkHandle
	{
	public:
		inline static constexpr auto MAX_VALUE = Max;

		using value_type = T;

		static_assert(REX::integer<T>);
		static_assert(MAX_VALUE <= std::numeric_limits<T>::max());

		constexpr hkHandle() noexcept = default;
		constexpr ~hkHandle() noexcept = default;

		constexpr hkHandle(const hkHandle&) noexcept = default;
		constexpr hkHandle(hkHandle&&) noexcept = default;

		constexpr hkHandle& operator=(const hkHandle&) noexcept = default;
		constexpr hkHandle& operator=(hkHandle&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const hkHandle&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const hkHandle&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const hkHandle&) const noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return has_value(); }

		[[nodiscard]] constexpr T operator->() const noexcept { return value(); }
		[[nodiscard]] constexpr T operator*() const noexcept { return value(); }

		[[nodiscard]] constexpr bool has_value() const noexcept
		{
			return _value < MAX_VALUE;
		}

		[[nodiscard]] constexpr T value() const noexcept
		{
			REX::Assert(has_value());
			return _value;
		}

		[[nodiscard]] constexpr T value_or(T a_default) const noexcept
		{
			return has_value() ? _value : a_default;
		}

		constexpr void reset() noexcept
		{
			_value = MAX_VALUE;
		}

		constexpr void swap(hkHandle& a_rhs) noexcept
		{
			std::swap(_value, a_rhs._value);
		}

	private:
		// members
		T _value{ MAX_VALUE }; // 00
	};
	static_assert(sizeof(hkHandle<std::uint8_t, 255, void>) == 0x01);

	template <class T, std::uint32_t Max, class Unk>
	constexpr void swap(hkHandle<T, Max, Unk>& a_lhs, hkHandle<T, Max, Unk>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
