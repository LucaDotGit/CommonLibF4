#pragma once

namespace REX
{
	template <class T>
	class AtomicRef final
		: public std::atomic_ref<T>
	{
	private:
		using super = std::atomic_ref<T>;

	public:
		using value_type = super::value_type;

		using super::super;
		using super::operator=;

		constexpr AtomicRef() noexcept = default;
		constexpr ~AtomicRef() noexcept = default;

		constexpr explicit AtomicRef(volatile T& a_value) //
			noexcept(std::is_nothrow_constructible_v<super, value_type&>)
			: super(const_cast<value_type&>(a_value))
		{
		}

		constexpr AtomicRef(const AtomicRef&) = delete;
		constexpr AtomicRef(AtomicRef&&) = delete;

		constexpr AtomicRef& operator=(const AtomicRef&) = delete;
		constexpr AtomicRef& operator=(AtomicRef&&) = delete;
	};

	template <class T>
	AtomicRef(volatile T&) -> AtomicRef<T>;

	extern template class AtomicRef<std::int8_t>;
	extern template class AtomicRef<std::uint8_t>;
	extern template class AtomicRef<std::int16_t>;
	extern template class AtomicRef<std::uint16_t>;
	extern template class AtomicRef<std::int32_t>;
	extern template class AtomicRef<std::uint32_t>;
	extern template class AtomicRef<std::int64_t>;
	extern template class AtomicRef<std::uint64_t>;
	extern template class AtomicRef<REX::Float32>;
	extern template class AtomicRef<REX::Float64>;
	extern template class AtomicRef<REX::Float128>;
}
