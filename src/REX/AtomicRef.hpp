#pragma once

namespace REX
{
	template <class T>
	class AtomicRef final : public std::atomic_ref<T>
	{
	private:
		using super = std::atomic_ref<T>;

	public:
		using typename super::value_type;

		using super::super;
		using super::operator=;

		constexpr AtomicRef() noexcept = default;
		constexpr ~AtomicRef() noexcept = default;

		constexpr explicit AtomicRef(volatile T& a_value)
			noexcept(std::is_nothrow_constructible_v<super, value_type&>) :
			super(const_cast<value_type&>(a_value))
		{
		}

		constexpr AtomicRef(const AtomicRef&) = delete;
		constexpr AtomicRef(AtomicRef&&) = delete;

		constexpr auto operator=(const AtomicRef&) -> AtomicRef& = delete;
		constexpr auto operator=(AtomicRef&&) -> AtomicRef& = delete;
	};

	template <class T>
	AtomicRef(volatile T&) -> AtomicRef<T>;

	static_assert(AtomicRef<std::int8_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint8_t>::is_always_lock_free);
	static_assert(AtomicRef<std::int16_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint16_t>::is_always_lock_free);
	static_assert(AtomicRef<std::int32_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint32_t>::is_always_lock_free);
	static_assert(AtomicRef<std::int64_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint64_t>::is_always_lock_free);
	static_assert(AtomicRef<REX::Float32>::is_always_lock_free);
	static_assert(AtomicRef<REX::Float64>::is_always_lock_free);
	static_assert(AtomicRef<REX::Float128>::is_always_lock_free);
}
