#pragma once

namespace RE
{
	template <class T>
	class BSTAtomicValue
	{
	public:
		using value_type = T;

		constexpr BSTAtomicValue() noexcept = default;
		constexpr ~BSTAtomicValue() noexcept = default;

		constexpr explicit BSTAtomicValue(value_type a_rhs) noexcept :
			_value(a_rhs)
		{
		}

		constexpr BSTAtomicValue(const BSTAtomicValue&) = delete;
		constexpr BSTAtomicValue(BSTAtomicValue&&) = delete;

		constexpr auto operator=(const BSTAtomicValue&) -> BSTAtomicValue& = delete;
		constexpr auto operator=(BSTAtomicValue&&) -> BSTAtomicValue& = delete;

		[[nodiscard]]
		constexpr auto operator==(const BSTAtomicValue& a_rhs) const noexcept -> bool
		{
			const auto leftAtomicValue = REX::AtomicRef(_value);
			const auto rightAtomicValue = REX::AtomicRef(a_rhs._value);
			return leftAtomicValue.load(std::memory_order_acquire) == rightAtomicValue.load(std::memory_order_acquire);
		}

		[[nodiscard]]
		constexpr auto operator==(value_type a_rhs) const noexcept -> bool
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) == a_rhs;
		}

		[[nodiscard]]
		constexpr auto operator<=>(const BSTAtomicValue& a_rhs) const noexcept -> auto
		{
			const auto leftAtomicValue = REX::AtomicRef(_value);
			const auto rightAtomicValue = REX::AtomicRef(a_rhs._value);
			return leftAtomicValue.load(std::memory_order_acquire) <=> rightAtomicValue.load(std::memory_order_acquire);
		}

		[[nodiscard]]
		constexpr auto operator<=>(value_type a_rhs) const noexcept -> auto
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) <=> a_rhs;
		}

		constexpr auto operator=(value_type a_rhs) noexcept -> BSTAtomicValue&
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.store(a_rhs, std::memory_order_release);
			return *this;
		}

		[[nodiscard]]
		constexpr auto operator+(value_type a_rhs) const noexcept -> value_type
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) + a_rhs;
		}

		constexpr auto operator+=(value_type a_rhs) noexcept -> BSTAtomicValue&
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_add(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		[[nodiscard]]
		constexpr auto operator-(value_type a_rhs) const noexcept -> value_type
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) - a_rhs;
		}

		constexpr auto operator-=(value_type a_rhs) noexcept -> BSTAtomicValue&
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_sub(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		[[nodiscard]]
		constexpr auto operator&(value_type a_rhs) const noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) & a_rhs;
		}

		constexpr auto operator&=(value_type a_rhs) noexcept -> BSTAtomicValue&
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_and(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		[[nodiscard]]
		constexpr auto operator|(value_type a_rhs) const noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) | a_rhs;
		}

		constexpr auto operator|=(value_type a_rhs) noexcept -> BSTAtomicValue&
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_or(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		[[nodiscard]]
		constexpr auto operator^(value_type a_rhs) const noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) ^ a_rhs;
		}

		constexpr auto operator^=(value_type a_rhs) noexcept -> BSTAtomicValue&
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_xor(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		constexpr auto operator++() noexcept -> BSTAtomicValue&
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			++atomicValue;
			return *this;
		}

		constexpr auto operator++(std::int32_t) noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue++;
		}

		constexpr auto operator--() noexcept -> BSTAtomicValue&
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			--atomicValue;
			return *this;
		}

		constexpr auto operator--(std::int32_t) noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue--;
		}

		[[nodiscard]]
		constexpr auto load() const noexcept -> value_type
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire);
		}

		constexpr void store(value_type a_value) noexcept
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.store(a_value, std::memory_order_release);
		}

		constexpr auto exchange(value_type a_value) noexcept -> value_type
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.exchange(a_value, std::memory_order_acq_rel);
		}

		constexpr auto fetch_add(value_type a_value) noexcept -> value_type
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_add(a_value, std::memory_order_acq_rel);
		}

		constexpr auto fetch_sub(value_type a_value) noexcept -> value_type
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_sub(a_value, std::memory_order_acq_rel);
		}

		constexpr auto fetch_and(value_type a_value) noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_and(a_value, std::memory_order_acq_rel);
		}

		constexpr auto fetch_or(value_type a_value) noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_or(a_value, std::memory_order_acq_rel);
		}

		constexpr auto fetch_xor(value_type a_value) noexcept -> value_type
			requires(REX::integer<value_type>)
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_xor(a_value, std::memory_order_acq_rel);
		}

		constexpr auto compare_exchange_weak(value_type& a_expected, value_type a_desired) noexcept -> bool
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.compare_exchange_weak(
				a_expected,
				a_desired,
				std::memory_order_acq_rel,
				std::memory_order_acquire);
		}

		constexpr auto compare_exchange_strong(value_type& a_expected, value_type a_desired) noexcept -> bool
		{
			const auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.compare_exchange_strong(
				a_expected,
				a_desired,
				std::memory_order_acq_rel,
				std::memory_order_acquire);
		}

		constexpr void wait(value_type a_expected) const noexcept
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.wait(a_expected, std::memory_order_acquire);
		}

		constexpr void notify_one() noexcept
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.notify_one();
		}

		constexpr void notify_all() noexcept
		{
			const auto atomicValue = REX::AtomicRef(_value);
			atomicValue.notify_all();
		}

	private:
		// members
		volatile value_type _value{static_cast<value_type>(0)}; // 0x00
	};

	template <class T>
	BSTAtomicValue(T) -> BSTAtomicValue<T>;
}
