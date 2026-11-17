#pragma once

#include "REX/AtomicRef.hpp"
#include "REX/Concepts.hpp"
#include "REX/Hashing.hpp"

namespace REX::Impl
{
	template <class T, class E, class U>
	concept EnumSetConstraint =
		REX::enumeration<E> && REX::integer<U> && (std::same_as<T, E> || std::is_convertible_v<T, U>);
}

namespace REX
{
	template <class E, class U = std::underlying_type_t<E>>
	class EnumSet final
	{
	public:
		using enum_type = E;
		using underlying_type = U;

		static_assert(REX::enumeration<enum_type>, "`EnumSet` requires `enum_type` to be an enumeration type.");
		static_assert(REX::integer<underlying_type>, "`EnumSet` requires `underlying_type` to be an integer type.");

		constexpr EnumSet() noexcept = default;
		constexpr ~EnumSet() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr EnumSet(enum_type a_value) noexcept :
			_value(static_cast<underlying_type>(a_value))
		{
		}

		constexpr explicit EnumSet(underlying_type a_value) noexcept :
			_value(a_value)
		{
		}

		template <class... Args>
		constexpr explicit EnumSet(Args... a_values) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
			:
			_value((static_cast<underlying_type>(a_values) | ...))
		{
		}

		constexpr EnumSet(const EnumSet&) noexcept = default;
		constexpr EnumSet(EnumSet&&) noexcept = default;

		constexpr auto operator=(enum_type a_value) noexcept -> EnumSet&
		{
			_value = static_cast<underlying_type>(a_value);
			return *this;
		}

		constexpr auto operator=(const EnumSet&) noexcept -> EnumSet& = default;
		constexpr auto operator=(EnumSet&&) noexcept -> EnumSet& = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return static_cast<bool>(_value);
		}

		[[nodiscard]]
		constexpr explicit operator enum_type() const noexcept
		{
			return get();
		}

		[[nodiscard]]
		constexpr explicit operator underlying_type() const noexcept
		{
			return _value;
		}

		[[nodiscard]]
		constexpr auto underlying_address() noexcept -> underlying_type*
		{
			return std::addressof(_value);
		}

		[[nodiscard]]
		constexpr auto underlying_address() const noexcept -> const underlying_type*
		{
			return std::addressof(_value);
		}

		[[nodiscard]]
		constexpr auto underlying_ref() noexcept -> underlying_type&
		{
			return _value;
		}

		[[nodiscard]]
		constexpr auto underlying_ref() const noexcept -> const underlying_type&
		{
			return _value;
		}

		[[nodiscard]]
		constexpr auto underlying_atomic_ref() noexcept -> REX::AtomicRef<underlying_type>
		{
			return REX::AtomicRef(_value);
		}

		[[nodiscard]]
		constexpr auto underlying_atomic_ref() const noexcept -> REX::AtomicRef<const underlying_type>
		{
			return REX::AtomicRef(_value);
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> enum_type
		{
			return static_cast<enum_type>(_value);
		}

		[[nodiscard]]
		constexpr auto get_atomic() const noexcept -> enum_type
		{
			auto atomicValue = AtomicRef(_value);
			return static_cast<enum_type>(atomicValue.load(std::memory_order_acquire));
		}

		[[nodiscard]]
		constexpr auto underlying() const noexcept -> underlying_type
		{
			return _value;
		}

		[[nodiscard]]
		constexpr auto underlying_atomic() const noexcept -> underlying_type
		{
			auto atomicValue = AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire);
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return _value == static_cast<underlying_type>(0);
		}

		[[nodiscard]]
		constexpr auto empty_atomic() const noexcept -> bool
		{
			auto atomicValue = AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) == static_cast<underlying_type>(0);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto all(Args... a_args) const noexcept -> bool
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			return (_value & (static_cast<underlying_type>(a_args) | ...)) ==
				   (static_cast<underlying_type>(a_args) | ...);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto all_atomic(Args... a_args) const noexcept -> bool
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			return (atomicValue.load(std::memory_order_acquire) & (static_cast<underlying_type>(a_args) | ...)) ==
				   (static_cast<underlying_type>(a_args) | ...);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto any(Args... a_args) const noexcept -> bool
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			return (_value & (static_cast<underlying_type>(a_args) | ...)) != static_cast<underlying_type>(0);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto any_atomic(Args... a_args) const noexcept -> bool
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			return (atomicValue.load(std::memory_order_acquire) & (static_cast<underlying_type>(a_args) | ...)) !=
				   static_cast<underlying_type>(0);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto none(Args... a_args) const noexcept -> bool
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			return (_value & (static_cast<underlying_type>(a_args) | ...)) == static_cast<underlying_type>(0);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto none_atomic(Args... a_args) const noexcept -> bool
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			return (atomicValue.load(std::memory_order_acquire) & (static_cast<underlying_type>(a_args) | ...)) ==
				   static_cast<underlying_type>(0);
		}

		template <class T>
		constexpr void store(T a_value) noexcept
			requires(Impl::EnumSetConstraint<T, enum_type, underlying_type>)
		{
			_value = static_cast<underlying_type>(a_value);
		}

		template <class T>
		constexpr void store_atomic(T a_value) noexcept
			requires(Impl::EnumSetConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.store(static_cast<underlying_type>(a_value), std::memory_order_release);
		}

		template <class T>
		constexpr auto exchange(T a_value) noexcept -> EnumSet
			requires(Impl::EnumSetConstraint<T, enum_type, underlying_type>)
		{
			return std::exchange(_value, static_cast<underlying_type>(a_value));
		}

		template <class T>
		constexpr auto exchange_atomic(T a_value) noexcept -> EnumSet
			requires(Impl::EnumSetConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			return EnumSet(atomicValue.exchange(static_cast<underlying_type>(a_value), std::memory_order_acq_rel));
		}

		template <class... Args>
		constexpr void set(Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			std::exchange(_value, static_cast<underlying_type>(_value | (static_cast<underlying_type>(a_args) | ...)));
		}

		template <class... Args>
		constexpr void set_atomic(Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.fetch_or((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
		}

		template <class... Args>
		constexpr void set(bool a_set, Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			a_set ? std::exchange(
						_value,
						static_cast<underlying_type>(_value | (static_cast<underlying_type>(a_args) | ...))) :
					std::exchange(
						_value,
						static_cast<underlying_type>(_value & ~(static_cast<underlying_type>(a_args) | ...)));
		}

		template <class... Args>
		constexpr void set_atomic(bool a_set, Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			a_set ? atomicValue.fetch_or((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel) :
					atomicValue.fetch_and(~(static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
		}

		template <class... Args>
		constexpr void reset(Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			std::exchange(_value, static_cast<underlying_type>(_value & ~(static_cast<underlying_type>(a_args) | ...)));
		}

		template <class... Args>
		constexpr void reset_atomic(Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.fetch_and(~(static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
		}

		template <class... Args>
		constexpr void reset(bool a_unset, Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			a_unset ? std::exchange(
						  _value,
						  static_cast<underlying_type>(_value & ~(static_cast<underlying_type>(a_args) | ...))) :
					  std::exchange(
						  _value,
						  static_cast<underlying_type>(_value | (static_cast<underlying_type>(a_args) | ...)));
		}

		template <class... Args>
		constexpr void reset_atomic(bool a_unset, Args... a_args) noexcept
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			a_unset ? atomicValue.fetch_and(~(static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel) :
					  atomicValue.fetch_or((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
		}

		constexpr void reset() noexcept
		{
			std::exchange(_value, static_cast<underlying_type>(0));
		}

		constexpr void reset_atomic() noexcept
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.exchange(static_cast<underlying_type>(0), std::memory_order_release);
		}

		template <class... Args>
		constexpr auto fetch_add(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto oldValue = _value;
			_value += (static_cast<underlying_type>(a_args) | ...);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_add_atomic(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto oldValue =
				atomicValue.fetch_add((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_sub(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto oldValue = _value;
			_value -= (static_cast<underlying_type>(a_args) | ...);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_sub_atomic(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto oldValue =
				atomicValue.fetch_sub((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_and(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto oldValue = _value;
			_value &= (static_cast<underlying_type>(a_args) | ...);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_and_atomic(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto oldValue =
				atomicValue.fetch_and((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_or(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto oldValue = _value;
			_value |= (static_cast<underlying_type>(a_args) | ...);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class... Args>
		constexpr auto fetch_or_atomic(Args... a_args) noexcept -> EnumSet
			requires((Impl::EnumSetConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto oldValue =
				atomicValue.fetch_or((static_cast<underlying_type>(a_args) | ...), std::memory_order_acq_rel);
			return EnumSet(static_cast<enum_type>(oldValue));
		}

		template <class Expected, class Desired>
		constexpr auto compare_exchange(Expected& a_expected, Desired a_desired) noexcept -> bool
			requires(
				Impl::EnumSetConstraint<Expected, enum_type, underlying_type> &&
				Impl::EnumSetConstraint<Desired, enum_type, underlying_type>)
		{
			if (_value != a_expected) {
				a_expected = static_cast<enum_type>(_value);
				return false;
			}

			_value = a_desired;
			return true;
		}

		template <class Expected, class Desired>
		constexpr auto compare_exchange_weak_atomic(Expected& a_expected, Desired a_desired) noexcept -> bool
			requires(
				Impl::EnumSetConstraint<Expected, enum_type, underlying_type> &&
				Impl::EnumSetConstraint<Desired, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			return atomicValue.compare_exchange_weak(
				a_expected,
				a_desired,
				std::memory_order_acq_rel,
				std::memory_order_acquire);
		}

		template <class Expected, class Desired>
		constexpr auto compare_exchange_strong_atomic(Expected& a_expected, Desired a_desired) noexcept -> bool
			requires(
				Impl::EnumSetConstraint<Expected, enum_type, underlying_type> &&
				Impl::EnumSetConstraint<Desired, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			return atomicValue.compare_exchange_strong(
				a_expected,
				a_desired,
				std::memory_order_acq_rel,
				std::memory_order_acquire);
		}

		template <class... Expected>
		constexpr void wait(Expected... a_expected) const noexcept
			requires((Impl::EnumSetConstraint<Expected, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto expectedValue = (static_cast<underlying_type>(a_expected) | ...);
			atomicValue.wait(expectedValue, std::memory_order_acquire);
		}

		constexpr void notify_one() noexcept
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.notify_one();
		}

		constexpr void notify_all() noexcept
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.notify_all();
		}

		[[nodiscard]]
		constexpr friend auto operator==(EnumSet a_lhs, EnumSet a_rhs) noexcept -> bool
		{
			return a_lhs.underlying() == a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator==(EnumSet a_lhs, enum_type a_rhs) noexcept -> bool
		{
			return a_lhs.underlying() == static_cast<underlying_type>(a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(enum_type a_lhs, EnumSet a_rhs) noexcept -> bool
		{
			return static_cast<underlying_type>(a_lhs) == a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(EnumSet a_lhs, EnumSet a_rhs) noexcept -> auto
		{
			return a_lhs.underlying() <=> a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(EnumSet a_lhs, enum_type a_rhs) noexcept -> auto
		{
			return a_lhs.underlying() <=> static_cast<underlying_type>(a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(enum_type a_lhs, EnumSet a_rhs) noexcept -> auto
		{
			return static_cast<underlying_type>(a_lhs) <=> a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator+(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() + a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator+(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() + static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator+(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) + a_rhs.underlying()));
		}

		constexpr friend auto operator+=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator+=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator-(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() - a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator-(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() - static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator-(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) - a_rhs.underlying()));
		}

		constexpr friend auto operator-=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator-=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<<(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() << a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator<<(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() << static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator<<(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) << a_rhs.underlying()));
		}

		constexpr friend auto operator<<=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs << a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator<<=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs << a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator>>(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() >> a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator>>(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() >> static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator>>(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) >> a_rhs.underlying()));
		}

		constexpr friend auto operator>>=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs >> a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator>>=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs >> a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator&(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() & a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator&(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() & static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator&(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) & a_rhs.underlying()));
		}

		constexpr friend auto operator&=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs & a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator&=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs & a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator|(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() | a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator|(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() | static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator|(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) | a_rhs.underlying()));
		}

		constexpr friend auto operator|=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs | a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator|=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs | a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator^(EnumSet a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() ^ a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator^(EnumSet a_lhs, enum_type a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(a_lhs.underlying() ^ static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator^(enum_type a_lhs, EnumSet a_rhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) ^ a_rhs.underlying()));
		}

		constexpr friend auto operator^=(EnumSet& a_lhs, EnumSet a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs ^ a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator^=(EnumSet& a_lhs, enum_type a_rhs) noexcept -> EnumSet&
		{
			a_lhs = a_lhs ^ a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator~(EnumSet a_lhs) noexcept -> EnumSet
		{
			return EnumSet(static_cast<enum_type>(~a_lhs.underlying()));
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		underlying_type _value{0};
		// NOLINTEND(readability-identifier-naming)
	};

	template <class... Args>
	EnumSet(Args...) -> EnumSet<std::common_type_t<Args...>, std::underlying_type_t<std::common_type_t<Args...>>>;
}

namespace std
{
	template <class E, class U>
	struct hash<REX::EnumSet<E, U>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::EnumSet<E, U>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.underlying());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class E, class U>
	struct formatter<REX::EnumSet<E, U>> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::EnumSet<E, U>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.underlying());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class E, class U>
	struct formatter<REX::EnumSet<E, U>> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::EnumSet<E, U>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.underlying());
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <class E, class U>
	struct meta<REX::EnumSet<E, U>>
	{
	public:
		using self_type = REX::EnumSet<E, U>;
		using other_type = E;

		inline static constexpr auto read_fn = [](self_type& a_self, const other_type& a_other) noexcept -> void {
			a_self = self_type(a_other);
		};

		inline static constexpr auto write_fn = [](const self_type& a_self, other_type& a_other) noexcept -> void {
			a_other = a_self.get();
		};

		inline static constexpr auto value = glz::custom<read_fn, write_fn>;
	};
}
#endif
