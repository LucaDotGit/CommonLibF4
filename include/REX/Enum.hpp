#pragma once

#include "REX/AtomicRef.hpp"
#include "REX/Concepts.hpp"

namespace REX::Impl
{
	template <class T, class E, class U>
	concept EnumConstraint =
		REX::enumeration<E> &&
		REX::integer<U> &&
		(std::same_as<T, E> || std::is_convertible_v<T, U>);
}

namespace REX
{
	template <class E, class U = std::underlying_type_t<E>>
	class Enum final
	{
	public:
		using enum_type = E;
		using underlying_type = U;

		inline static constexpr auto is_always_lock_free = REX::AtomicRef<underlying_type>::is_always_lock_free;

		static_assert(REX::enumeration<enum_type>,
			"`Enum` requires `enum_type` to be an enumeration type.");
		static_assert(REX::integer<underlying_type>,
			"`Enum` requires `underlying_type` to be an integer type.");

		static_assert(is_always_lock_free,
			"`Enum` requires `underlying_type` to be always lock-free for atomic operations.");

		constexpr Enum() noexcept = default;
		constexpr ~Enum() noexcept = default;

		template <class T>
		constexpr Enum(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
			: _impl(static_cast<underlying_type>(a_value))
		{
		}

		constexpr Enum(const Enum&) noexcept = default;
		constexpr Enum(Enum&&) noexcept = default;

		constexpr Enum& operator=(enum_type a_value) noexcept
		{
			_impl = static_cast<underlying_type>(a_value);
			return *this;
		}

		constexpr Enum& operator=(const Enum&) noexcept = default;
		constexpr Enum& operator=(Enum&&) noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return !empty(); }
		[[nodiscard]] constexpr explicit operator enum_type() const noexcept { return get(); }
		[[nodiscard]] constexpr explicit operator underlying_type() const noexcept { return _impl; }

		[[nodiscard]] constexpr enum_type operator*() const noexcept { return get(); }

		[[nodiscard]] constexpr underlying_type* underlying_address() noexcept
		{
			return std::addressof(_impl);
		}

		[[nodiscard]] constexpr const underlying_type* underlying_address() const noexcept
		{
			return std::addressof(_impl);
		}

		[[nodiscard]] constexpr REX::AtomicRef<underlying_type> underlying_atomic_ref() noexcept
		{
			return REX::AtomicRef(_impl);
		}

		[[nodiscard]] constexpr REX::AtomicRef<const underlying_type> underlying_atomic_ref() const noexcept
		{
			return REX::AtomicRef(_impl);
		}

		[[nodiscard]] constexpr enum_type get() const noexcept
		{
			return static_cast<enum_type>(_impl);
		}

		[[nodiscard]] constexpr enum_type get_atomic() const noexcept
		{
			auto atomicValue = AtomicRef(_impl);
			return static_cast<enum_type>(atomicValue.load(std::memory_order_acquire));
		}

		[[nodiscard]] constexpr underlying_type underlying() const noexcept
		{
			return _impl;
		}

		[[nodiscard]] constexpr underlying_type underlying_atomic() const noexcept
		{
			auto atomicValue = AtomicRef(_impl);
			return atomicValue.load(std::memory_order_acquire);
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return _impl == static_cast<underlying_type>(0);
		}

		[[nodiscard]] constexpr bool empty_atomic() const noexcept
		{
			auto atomicValue = AtomicRef(_impl);
			return atomicValue.load(std::memory_order_acquire) == static_cast<underlying_type>(0);
		}

		template <class T>
		[[nodiscard]] constexpr bool all(T a_value) const noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			return _impl == static_cast<underlying_type>(a_value);
		}

		template <class T>
		[[nodiscard]] constexpr bool all_atomic(T a_value) const noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			return atomicValue.load(std::memory_order_acquire) == static_cast<underlying_type>(a_value);
		}

		template <class... Args>
		[[nodiscard]] constexpr bool any(Args... a_args) const noexcept
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto loadedValue = _impl;
			return ((loadedValue == static_cast<underlying_type>(a_args)) || ...);
		}

		template <class... Args>
		[[nodiscard]] constexpr bool any_atomic(Args... a_args) const noexcept
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_impl);
			auto loadedValue = atomicValue.load(std::memory_order_acquire);
			return ((loadedValue == static_cast<underlying_type>(a_args)) || ...);
		}

		template <class... Args>
		[[nodiscard]] constexpr bool none(Args... a_args) const noexcept
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto loadedValue = _impl;
			return ((loadedValue != static_cast<underlying_type>(a_args)) && ...);
		}

		template <class... Args>
		[[nodiscard]] constexpr bool none_atomic(Args... a_args) const noexcept
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_impl);
			auto loadedValue = atomicValue.load(std::memory_order_acquire);
			return ((loadedValue != static_cast<underlying_type>(a_args)) && ...);
		}

		template <class T>
		constexpr void store(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			_impl = static_cast<underlying_type>(a_value);
		}

		template <class T>
		constexpr void store_atomic(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			atomicValue.store(static_cast<underlying_type>(a_value),
				std::memory_order_release);
		}

		template <class T>
		constexpr Enum exchange(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			return std::exchange(_impl, static_cast<underlying_type>(a_value));
		}

		template <class T>
		constexpr Enum exchange_atomic(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			return atomicValue.exchange(static_cast<underlying_type>(a_value),
				std::memory_order_acq_rel);
		}

		constexpr void reset() noexcept
		{
			std::exchange(_impl, static_cast<underlying_type>(0));
		}

		constexpr void reset_atomic() noexcept
		{
			auto atomicValue = AtomicRef(_impl);
			atomicValue.exchange(0, std::memory_order_release);
		}

		template <class T>
		constexpr Enum fetch_add(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto oldValue = _impl;
			_impl += static_cast<underlying_type>(a_value);
			return static_cast<enum_type>(oldValue);
		}

		template <class T>
		constexpr Enum fetch_add_atomic(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			auto oldValue = atomicValue.fetch_add(static_cast<underlying_type>(a_value),
				std::memory_order_acq_rel);
			return static_cast<enum_type>(oldValue);
		}

		template <class T>
		constexpr Enum fetch_sub(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto oldValue = _impl;
			_impl -= static_cast<underlying_type>(a_value);
			return static_cast<enum_type>(oldValue);
		}

		template <class T>
		constexpr Enum fetch_sub_atomic(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			auto oldValue = atomicValue.fetch_sub(static_cast<underlying_type>(a_value),
				std::memory_order_acq_rel);
			return static_cast<enum_type>(oldValue);
		}

		template <class Expected, class Desired>
		constexpr bool compare_exchange(Expected& a_expected, Desired a_desired) noexcept
			requires(Impl::EnumConstraint<Expected, enum_type, underlying_type> &&
					 Impl::EnumConstraint<Desired, enum_type, underlying_type>)
		{
			if (_impl != a_expected) {
				a_expected = static_cast<enum_type>(_impl);
				return false;
			}

			_impl = a_desired;
			return true;
		}

		template <class Expected, class Desired>
		constexpr bool compare_exchange_weak_atomic(Expected& a_expected, Desired a_desired) noexcept
			requires(Impl::EnumConstraint<Expected, enum_type, underlying_type> &&
					 Impl::EnumConstraint<Desired, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			return atomicValue.compare_exchange_weak(a_expected, a_desired,
				std::memory_order_acq_rel, std::memory_order_acquire);
		}

		template <class Expected, class Desired>
		constexpr bool compare_exchange_strong_atomic(Expected& a_expected, Desired a_desired) noexcept
			requires(Impl::EnumConstraint<Expected, enum_type, underlying_type> &&
					 Impl::EnumConstraint<Desired, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			return atomicValue.compare_exchange_strong(a_expected, a_desired,
				std::memory_order_acq_rel, std::memory_order_acquire);
		}

		template <class Expected>
		constexpr void wait(Expected a_expected) const noexcept
			requires(Impl::EnumConstraint<Expected, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_impl);
			auto expectedValue = static_cast<underlying_type>(a_expected);
			atomicValue.wait(expectedValue, std::memory_order_acquire);
		}

		constexpr void notify_one() noexcept
		{
			auto atomicValue = AtomicRef(_impl);
			atomicValue.notify_one();
		}

		constexpr void notify_all() noexcept
		{
			auto atomicValue = AtomicRef(_impl);
			atomicValue.notify_all();
		}

		[[nodiscard]] constexpr friend bool operator==(Enum a_lhs, Enum a_rhs) noexcept { return a_lhs.underlying() == a_rhs.underlying(); }
		[[nodiscard]] constexpr friend bool operator==(Enum a_lhs, enum_type a_rhs) noexcept { return a_lhs.underlying() == static_cast<underlying_type>(a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(enum_type a_lhs, Enum a_rhs) noexcept { return static_cast<underlying_type>(a_lhs) == a_rhs.underlying(); }

		[[nodiscard]] constexpr friend auto operator<=>(Enum a_lhs, Enum a_rhs) noexcept { return a_lhs.underlying() <=> a_rhs.underlying(); }
		[[nodiscard]] constexpr friend auto operator<=>(Enum a_lhs, enum_type a_rhs) noexcept { return a_lhs.underlying() <=> static_cast<underlying_type>(a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(enum_type a_lhs, Enum a_rhs) noexcept { return static_cast<underlying_type>(a_lhs) <=> a_rhs.underlying(); }

		[[nodiscard]] constexpr friend Enum operator+(Enum a_lhs, Enum a_rhs) noexcept { return static_cast<enum_type>(a_lhs.underlying() + a_rhs.underlying()); }
		[[nodiscard]] constexpr friend Enum operator+(Enum a_lhs, enum_type a_rhs) noexcept { return static_cast<enum_type>(a_lhs.underlying() + static_cast<underlying_type>(a_rhs)); }
		[[nodiscard]] constexpr friend Enum operator+(enum_type a_lhs, Enum a_rhs) noexcept { return static_cast<enum_type>(static_cast<underlying_type>(a_lhs) + a_rhs.underlying()); }

		constexpr friend Enum& operator+=(Enum& a_lhs, Enum a_rhs) noexcept { return a_lhs = a_lhs + a_rhs; }
		constexpr friend Enum& operator+=(Enum& a_lhs, enum_type a_rhs) noexcept { return a_lhs = a_lhs + a_rhs; }

		[[nodiscard]] constexpr friend Enum operator-(Enum a_lhs, Enum a_rhs) noexcept { return static_cast<enum_type>(a_lhs.underlying() - a_rhs.underlying()); }
		[[nodiscard]] constexpr friend Enum operator-(Enum a_lhs, enum_type a_rhs) noexcept { return static_cast<enum_type>(a_lhs.underlying() - static_cast<underlying_type>(a_rhs)); }
		[[nodiscard]] constexpr friend Enum operator-(enum_type a_lhs, Enum a_rhs) noexcept { return static_cast<enum_type>(static_cast<underlying_type>(a_lhs) - a_rhs.underlying()); }

		constexpr friend Enum& operator-=(Enum& a_lhs, Enum a_rhs) noexcept { return a_lhs = a_lhs - a_rhs; }
		constexpr friend Enum& operator-=(Enum& a_lhs, enum_type a_rhs) noexcept { return a_lhs = a_lhs - a_rhs; }

	private:
		underlying_type _impl{ 0 };
	};

	template <class... Args>
	Enum(Args...) -> Enum<
		std::common_type_t<Args...>,
		std::underlying_type_t<
			std::common_type_t<Args...>>>;
}
