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

		constexpr auto operator=(const hkHandle&) noexcept -> hkHandle& = default;
		constexpr auto operator=(hkHandle&&) noexcept -> hkHandle& = default;

		[[nodiscard]]
		constexpr auto operator==(const hkHandle&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const hkHandle&) const noexcept = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return has_value();
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> T
		{
			return value();
		}

		[[nodiscard]]
		constexpr auto operator*() const noexcept -> T
		{
			return value();
		}

		[[nodiscard]]
		constexpr auto has_value() const noexcept -> bool
		{
			return _value < MAX_VALUE;
		}

		[[nodiscard]]
		constexpr auto value() const noexcept -> T
		{
			REX::Assert(has_value());
			return _value;
		}

		[[nodiscard]]
		constexpr auto value_or(T a_default) const noexcept -> T
		{
			return has_value() ? _value : a_default;
		}

		constexpr void reset() noexcept
		{
			_value = MAX_VALUE;
		}

		constexpr void swap(hkHandle& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_value, a_other._value);
		}

	private:
		// members
		T _value{MAX_VALUE}; // 0x00
	};

	static_assert(sizeof(hkHandle<std::uint8_t, 255, void>) == 0x01);
}
