#pragma once

namespace RE
{
	template <class T>
	class BSTAtomicValue
	{
	public:
		using value_type = T;

		inline static constexpr bool is_always_lock_free = REX::AtomicRef<value_type>::is_always_lock_free;

		constexpr BSTAtomicValue() noexcept = default;
		constexpr ~BSTAtomicValue() noexcept = default;

		constexpr explicit BSTAtomicValue(value_type a_rhs) noexcept
			: _value(a_rhs)
		{
		}

		constexpr BSTAtomicValue(const BSTAtomicValue&) = delete;
		constexpr BSTAtomicValue(BSTAtomicValue&&) = delete;

		constexpr BSTAtomicValue& operator=(const BSTAtomicValue&) = delete;
		constexpr BSTAtomicValue& operator=(BSTAtomicValue&&) = delete;

		constexpr BSTAtomicValue& operator=(value_type a_rhs) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.store(a_rhs, std::memory_order_release);
			return *this;
		}

		constexpr BSTAtomicValue& operator+=(value_type a_rhs) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_add(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		constexpr BSTAtomicValue& operator-=(value_type a_rhs) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_sub(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		constexpr BSTAtomicValue& operator&=(value_type a_rhs) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_and(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		constexpr BSTAtomicValue& operator|=(value_type a_rhs) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_or(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		constexpr BSTAtomicValue& operator^=(value_type a_rhs) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.fetch_xor(a_rhs, std::memory_order_acq_rel);
			return *this;
		}

		constexpr BSTAtomicValue& operator++() noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			++atomicValue;
			return *this;
		}

		constexpr value_type operator--() noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return --atomicValue;
		}

		constexpr value_type operator++(std::int32_t) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue++;
		}

		constexpr value_type operator--(std::int32_t) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue--;
		}

		[[nodiscard]] constexpr value_type operator+(value_type a_rhs) const noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) + a_rhs;
		}

		[[nodiscard]] constexpr value_type operator-(value_type a_rhs) const noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) - a_rhs;
		}

		[[nodiscard]] constexpr value_type operator&(value_type a_rhs) const noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) & a_rhs;
		}

		[[nodiscard]] constexpr value_type operator|(value_type a_rhs) const noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) | a_rhs;
		}

		[[nodiscard]] constexpr value_type operator^(value_type a_rhs) const noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) ^ a_rhs;
		}

		[[nodiscard]] constexpr value_type load() const noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire);
		}

		constexpr void store(value_type a_value) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.store(a_value, std::memory_order_release);
		}

		constexpr value_type exchange(value_type a_value) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.exchange(a_value, std::memory_order_acq_rel);
		}

		constexpr value_type fetch_add(value_type a_value) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_add(a_value, std::memory_order_acq_rel);
		}

		constexpr value_type fetch_sub(value_type a_value) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_sub(a_value, std::memory_order_acq_rel);
		}

		constexpr value_type fetch_and(value_type a_value) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_and(a_value, std::memory_order_acq_rel);
		}

		constexpr value_type fetch_or(value_type a_value) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_or(a_value, std::memory_order_acq_rel);
		}

		constexpr value_type fetch_xor(value_type a_value) noexcept
			requires(REX::integer<value_type>)
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.fetch_xor(a_value, std::memory_order_acq_rel);
		}

		constexpr bool compare_exchange_weak(value_type& a_expected, value_type a_desired) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.compare_exchange_weak(a_expected, a_desired,
				std::memory_order_acq_rel, std::memory_order_acquire);
		}

		constexpr bool compare_exchange_strong(value_type& a_expected, value_type a_desired) noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			return atomicValue.compare_exchange_strong(a_expected, a_desired,
				std::memory_order_acq_rel, std::memory_order_acquire);
		}

		constexpr void wait(value_type a_expected) const noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.wait(a_expected, std::memory_order_acquire);
		}

		constexpr void notify_one() noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.notify_one();
		}

		constexpr void notify_all() noexcept
		{
			auto atomicValue = REX::AtomicRef(_value);
			atomicValue.notify_all();
		}

	private:
		// members
		volatile value_type _value{}; // 00
	};

	template <class T>
	BSTAtomicValue(T) -> BSTAtomicValue<T>;

	extern template class BSTAtomicValue<std::int8_t>;
	extern template class BSTAtomicValue<std::uint8_t>;
	extern template class BSTAtomicValue<std::int16_t>;
	extern template class BSTAtomicValue<std::uint16_t>;
	extern template class BSTAtomicValue<std::int32_t>;
	extern template class BSTAtomicValue<std::uint32_t>;
	extern template class BSTAtomicValue<std::int64_t>;
	extern template class BSTAtomicValue<std::uint64_t>;
	extern template class BSTAtomicValue<REX::Float32>;
	extern template class BSTAtomicValue<REX::Float64>;
	extern template class BSTAtomicValue<REX::Float128>;
}
