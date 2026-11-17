#pragma once

#include "REX/AtomicRef.hpp"
#include "REX/Concepts.hpp"
#include "REX/Hashing.hpp"

namespace REX::Impl
{
	template <class T, class E, class U>
	concept EnumConstraint =
		REX::enumeration<E> && REX::integer<U> && (std::same_as<T, E> || std::is_convertible_v<T, U>);
}

namespace REX
{
	template <class E, class U = std::underlying_type_t<E>>
	class Enum final
	{
	public:
		using enum_type = E;
		using underlying_type = U;

		static_assert(REX::enumeration<enum_type>, "`Enum` requires `enum_type` to be an enumeration type.");
		static_assert(REX::integer<underlying_type>, "`Enum` requires `underlying_type` to be an integer type.");

		constexpr Enum() noexcept = default;
		constexpr ~Enum() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr Enum(enum_type a_value) noexcept :
			_value(static_cast<underlying_type>(a_value))
		{
		}

		constexpr explicit Enum(underlying_type a_value) noexcept :
			_value(a_value)
		{
		}

		constexpr Enum(const Enum&) noexcept = default;
		constexpr Enum(Enum&&) noexcept = default;

		constexpr auto operator=(enum_type a_value) noexcept -> Enum&
		{
			_value = static_cast<underlying_type>(a_value);
			return *this;
		}

		constexpr auto operator=(const Enum&) noexcept -> Enum& = default;
		constexpr auto operator=(Enum&&) noexcept -> Enum& = default;

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

		template <class T>
		[[nodiscard]]
		constexpr auto all(T a_value) const noexcept -> bool
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			return _value == static_cast<underlying_type>(a_value);
		}

		template <class T>
		[[nodiscard]]
		constexpr auto all_atomic(T a_value) const noexcept -> bool
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			return atomicValue.load(std::memory_order_acquire) == static_cast<underlying_type>(a_value);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto any(Args... a_args) const noexcept -> bool
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto loadedValue = _value;
			return ((loadedValue == static_cast<underlying_type>(a_args)) || ...);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto any_atomic(Args... a_args) const noexcept -> bool
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto loadedValue = atomicValue.load(std::memory_order_acquire);
			return ((loadedValue == static_cast<underlying_type>(a_args)) || ...);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto none(Args... a_args) const noexcept -> bool
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto loadedValue = _value;
			return ((loadedValue != static_cast<underlying_type>(a_args)) && ...);
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto none_atomic(Args... a_args) const noexcept -> bool
			requires((Impl::EnumConstraint<Args, enum_type, underlying_type> && ...))
		{
			auto atomicValue = AtomicRef(_value);
			auto loadedValue = atomicValue.load(std::memory_order_acquire);
			return ((loadedValue != static_cast<underlying_type>(a_args)) && ...);
		}

		template <class T>
		constexpr void store(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			_value = static_cast<underlying_type>(a_value);
		}

		template <class T>
		constexpr void store_atomic(T a_value) noexcept
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.store(static_cast<underlying_type>(a_value), std::memory_order_release);
		}

		template <class T>
		constexpr auto exchange(T a_value) noexcept -> Enum
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			return Enum(std::exchange(_value, static_cast<underlying_type>(a_value)));
		}

		template <class T>
		constexpr auto exchange_atomic(T a_value) noexcept -> Enum
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			return Enum(atomicValue.exchange(static_cast<underlying_type>(a_value), std::memory_order_acq_rel));
		}

		constexpr void reset() noexcept
		{
			std::exchange(_value, static_cast<underlying_type>(0));
		}

		constexpr void reset_atomic() noexcept
		{
			auto atomicValue = AtomicRef(_value);
			atomicValue.exchange(0, std::memory_order_release);
		}

		template <class T>
		constexpr auto fetch_add(T a_value) noexcept -> Enum
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto oldValue = _value;
			_value += static_cast<underlying_type>(a_value);
			return Enum(static_cast<enum_type>(oldValue));
		}

		template <class T>
		constexpr auto fetch_add_atomic(T a_value) noexcept -> Enum
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			auto oldValue = atomicValue.fetch_add(static_cast<underlying_type>(a_value), std::memory_order_acq_rel);
			return Enum(static_cast<enum_type>(oldValue));
		}

		template <class T>
		constexpr auto fetch_sub(T a_value) noexcept -> Enum
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto oldValue = _value;
			_value -= static_cast<underlying_type>(a_value);
			return Enum(static_cast<enum_type>(oldValue));
		}

		template <class T>
		constexpr auto fetch_sub_atomic(T a_value) noexcept -> Enum
			requires(Impl::EnumConstraint<T, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			auto oldValue = atomicValue.fetch_sub(static_cast<underlying_type>(a_value), std::memory_order_acq_rel);
			return Enum(static_cast<enum_type>(oldValue));
		}

		template <class Expected, class Desired>
		constexpr auto compare_exchange(Expected& a_expected, Desired a_desired) noexcept -> bool
			requires(
				Impl::EnumConstraint<Expected, enum_type, underlying_type> &&
				Impl::EnumConstraint<Desired, enum_type, underlying_type>)
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
				Impl::EnumConstraint<Expected, enum_type, underlying_type> &&
				Impl::EnumConstraint<Desired, enum_type, underlying_type>)
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
				Impl::EnumConstraint<Expected, enum_type, underlying_type> &&
				Impl::EnumConstraint<Desired, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			return atomicValue.compare_exchange_strong(
				a_expected,
				a_desired,
				std::memory_order_acq_rel,
				std::memory_order_acquire);
		}

		template <class Expected>
		constexpr void wait(Expected a_expected) const noexcept
			requires(Impl::EnumConstraint<Expected, enum_type, underlying_type>)
		{
			auto atomicValue = AtomicRef(_value);
			auto expectedValue = static_cast<underlying_type>(a_expected);
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
		constexpr friend auto operator==(Enum a_lhs, Enum a_rhs) noexcept -> bool
		{
			return a_lhs.underlying() == a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator==(Enum a_lhs, enum_type a_rhs) noexcept -> bool
		{
			return a_lhs.underlying() == static_cast<underlying_type>(a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(enum_type a_lhs, Enum a_rhs) noexcept -> bool
		{
			return static_cast<underlying_type>(a_lhs) == a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(Enum a_lhs, Enum a_rhs) noexcept -> auto
		{
			return a_lhs.underlying() <=> a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(Enum a_lhs, enum_type a_rhs) noexcept -> auto
		{
			return a_lhs.underlying() <=> static_cast<underlying_type>(a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(enum_type a_lhs, Enum a_rhs) noexcept -> auto
		{
			return static_cast<underlying_type>(a_lhs) <=> a_rhs.underlying();
		}

		[[nodiscard]]
		constexpr friend auto operator+(Enum a_lhs, Enum a_rhs) noexcept -> Enum
		{
			return Enum(static_cast<enum_type>(a_lhs.underlying() + a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator+(Enum a_lhs, enum_type a_rhs) noexcept -> Enum
		{
			return Enum(static_cast<enum_type>(a_lhs.underlying() + static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator+(enum_type a_lhs, Enum a_rhs) noexcept -> Enum
		{
			return Enum(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) + a_rhs.underlying()));
		}

		constexpr friend auto operator+=(Enum& a_lhs, Enum a_rhs) noexcept -> Enum&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator+=(Enum& a_lhs, enum_type a_rhs) noexcept -> Enum&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator-(Enum a_lhs, Enum a_rhs) noexcept -> Enum
		{
			return Enum(static_cast<enum_type>(a_lhs.underlying() - a_rhs.underlying()));
		}

		[[nodiscard]]
		constexpr friend auto operator-(Enum a_lhs, enum_type a_rhs) noexcept -> Enum
		{
			return Enum(static_cast<enum_type>(a_lhs.underlying() - static_cast<underlying_type>(a_rhs)));
		}

		[[nodiscard]]
		constexpr friend auto operator-(enum_type a_lhs, Enum a_rhs) noexcept -> Enum
		{
			return Enum(static_cast<enum_type>(static_cast<underlying_type>(a_lhs) - a_rhs.underlying()));
		}

		constexpr friend auto operator-=(Enum& a_lhs, Enum a_rhs) noexcept -> Enum&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator-=(Enum& a_lhs, enum_type a_rhs) noexcept -> Enum&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		underlying_type _value{0};
		// NOLINTEND(readability-identifier-naming)
	};

	template <class... Args>
	Enum(Args...) -> Enum<std::common_type_t<Args...>, std::underlying_type_t<std::common_type_t<Args...>>>;
}

namespace std
{
	template <class E, class U>
	struct hash<REX::Enum<E, U>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Enum<E, U>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.underlying());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class E, class U>
	struct formatter<REX::Enum<E, U>> : public formatter<std::string>
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
		constexpr auto format(const REX::Enum<E, U>& a_value, FormatContext& a_context) const
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
	struct formatter<REX::Enum<E, U>> : public formatter<std::string>
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
		constexpr auto format(const REX::Enum<E, U>& a_value, FormatContext& a_context) const
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
	struct meta<REX::Enum<E, U>>
	{
	public:
		using self_type = REX::Enum<E, U>;
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
