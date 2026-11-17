#pragma once

#include "REX/Hashing.hpp"
#include "REX/Math.hpp"

namespace REX
{
	template <std::intmax_t Base, std::intmax_t Exponent>
	class Unit final
	{
	public:
		inline static constexpr auto BASE = Base;
		inline static constexpr auto EXPONENT = Exponent;

		using value_type = std::intmax_t;

		static_assert(BASE != 0, "The base must be non-zero.");
		static_assert(EXPONENT != 0, "The exponent must be non-zero.");

		constexpr Unit() noexcept = default;

		constexpr explicit Unit(value_type a_value) noexcept :
			_value(a_value)
		{
		}

		constexpr ~Unit() noexcept = default;

		constexpr Unit(const Unit&) noexcept = default;
		constexpr Unit(Unit&&) noexcept = default;

		constexpr auto operator=(const Unit&) noexcept -> Unit& = default;
		constexpr auto operator=(Unit&&) noexcept -> Unit& = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return static_cast<bool>(get());
		}

		[[nodiscard]]
		constexpr explicit operator value_type() const noexcept
		{
			return get();
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr explicit operator Unit<OtherBase, OtherExponent>() const noexcept
		{
			return Unit<OtherBase, OtherExponent>(count() / REX::Pow(OtherBase, OtherExponent));
		}

		[[nodiscard]]
		static constexpr auto zero() noexcept -> Unit
		{
			return Unit(0);
		}

		[[nodiscard]]
		static constexpr auto one() noexcept -> Unit
		{
			return Unit(1);
		}

		[[nodiscard]]
		static constexpr auto min() noexcept -> Unit
		{
			return Unit(std::numeric_limits<value_type>::min());
		}

		[[nodiscard]]
		static constexpr auto max() noexcept -> Unit
		{
			return Unit(std::numeric_limits<value_type>::max());
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> value_type
		{
			return _value;
		}

		[[nodiscard]]
		constexpr auto count() const noexcept -> value_type
		{
			return get() * REX::Pow(BASE, EXPONENT);
		}

		constexpr void swap(Unit& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_value, a_other._value);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const Unit& a_lhs, const Unit& a_rhs) noexcept -> bool
		{
			return a_lhs.get() == a_rhs.get();
		}

		[[nodiscard]]
		constexpr friend auto operator==(const Unit& a_lhs, value_type a_rhs) noexcept -> bool
		{
			return a_lhs.get() == a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator==(value_type a_lhs, const Unit& a_rhs) noexcept -> bool
		{
			return a_lhs == a_rhs.get();
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator==(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept
			-> bool
		{
			return a_lhs.count() == a_rhs.count();
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator==(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> bool
		{
			return a_lhs.count() == a_rhs.count();
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const Unit& a_lhs, const Unit& a_rhs) noexcept -> auto
		{
			return a_lhs.get() <=> a_rhs.get();
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const Unit& a_lhs, value_type a_rhs) noexcept -> auto
		{
			return a_lhs.get() <=> a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(value_type a_lhs, const Unit& a_rhs) noexcept -> auto
		{
			return a_lhs <=> a_rhs.get();
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator<=>(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept
			-> auto
		{
			return a_lhs.count() <=> a_rhs.count();
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator<=>(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> auto
		{
			return a_lhs.count() <=> a_rhs.count();
		}

		[[nodiscard]]
		constexpr friend auto operator+(const Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() + a_rhs.get());
		}

		[[nodiscard]]
		constexpr friend auto operator+(const Unit& a_lhs, value_type a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() + a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator+(value_type a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs + a_rhs.get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator+(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() + static_cast<Unit>(a_rhs).get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator+(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(static_cast<Unit>(a_lhs).get() + a_rhs.get());
		}

		constexpr friend auto operator+=(Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator+=(Unit& a_lhs, value_type a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator+=(Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator+=(Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> Unit<OtherBase, OtherExponent>&
		{
			a_lhs = a_lhs + a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator-(const Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() - a_rhs.get());
		}

		[[nodiscard]]
		constexpr friend auto operator-(const Unit& a_lhs, value_type a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() - a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator-(value_type a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs - a_rhs.get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator-(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() - static_cast<Unit>(a_rhs).get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator-(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(static_cast<Unit>(a_lhs).get() - a_rhs.get());
		}

		constexpr friend auto operator-=(Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator-=(Unit& a_lhs, value_type a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator-=(Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator-=(Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> Unit<OtherBase, OtherExponent>&
		{
			a_lhs = a_lhs - a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator*(const Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() * a_rhs.get());
		}

		[[nodiscard]]
		constexpr friend auto operator*(const Unit& a_lhs, value_type a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() * a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator*(value_type a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs * a_rhs.get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator*(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() * static_cast<Unit>(a_rhs).get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator*(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(static_cast<Unit>(a_lhs).get() * a_rhs.get());
		}

		constexpr friend auto operator*=(Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs * a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator*=(Unit& a_lhs, value_type a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs * a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator*=(Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs * a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator*=(Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> Unit<OtherBase, OtherExponent>&
		{
			a_lhs = a_lhs * a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator/(const Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() / a_rhs.get());
		}

		[[nodiscard]]
		constexpr friend auto operator/(const Unit& a_lhs, value_type a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() / a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator/(value_type a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs / a_rhs.get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator/(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() / static_cast<Unit>(a_rhs).get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator/(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(static_cast<Unit>(a_lhs).get() / a_rhs.get());
		}

		constexpr friend auto operator/=(Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs / a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator/=(Unit& a_lhs, value_type a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs / a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator/=(Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs / a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator/=(Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> Unit<OtherBase, OtherExponent>&
		{
			a_lhs = a_lhs / a_rhs;
			return a_lhs;
		}

		[[nodiscard]]
		constexpr friend auto operator%(const Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() % a_rhs.get());
		}

		[[nodiscard]]
		constexpr friend auto operator%(const Unit& a_lhs, value_type a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() % a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator%(value_type a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs % a_rhs.get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator%(const Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit
		{
			return Unit(a_lhs.get() % static_cast<Unit>(a_rhs).get());
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		[[nodiscard]]
		constexpr friend auto operator%(const Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept -> Unit
		{
			return Unit(static_cast<Unit>(a_lhs).get() % a_rhs.get());
		}

		constexpr friend auto operator%=(Unit& a_lhs, const Unit& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs % a_rhs;
			return a_lhs;
		}

		constexpr friend auto operator%=(Unit& a_lhs, value_type a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs % a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator%=(Unit& a_lhs, const Unit<OtherBase, OtherExponent>& a_rhs) noexcept -> Unit&
		{
			a_lhs = a_lhs % a_rhs;
			return a_lhs;
		}

		template <std::intmax_t OtherBase, std::intmax_t OtherExponent>
		constexpr friend auto operator%=(Unit<OtherBase, OtherExponent>& a_lhs, const Unit& a_rhs) noexcept
			-> Unit<OtherBase, OtherExponent>&
		{
			a_lhs = a_lhs % a_rhs;
			return a_lhs;
		}

		constexpr auto operator++() noexcept -> Unit&
		{
			++_value;
			return *this;
		}

		constexpr auto operator++(std::int32_t) noexcept -> Unit
		{
			auto temp = *this;
			++_value;
			return temp;
		}

		constexpr auto operator--() noexcept -> Unit&
		{
			--_value;
			return *this;
		}

		constexpr auto operator--(std::int32_t) noexcept -> Unit
		{
			auto temp = *this;
			--_value;
			return temp;
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		value_type _value{static_cast<value_type>(0)};
		// NOLINTEND(readability-identifier-naming)
	};
}

namespace std
{
	template <std::intmax_t Base, std::intmax_t Exponent>
	struct hash<REX::Unit<Base, Exponent>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Unit<Base, Exponent>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.count());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <std::intmax_t Base, std::intmax_t Exponent>
	struct formatter<REX::Unit<Base, Exponent>> : public formatter<std::string>
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
		constexpr auto format(const REX::Unit<Base, Exponent>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.count());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <std::intmax_t Base, std::intmax_t Exponent>
	struct formatter<REX::Unit<Base, Exponent>> : public formatter<std::string>
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
		constexpr auto format(const REX::Unit<Base, Exponent>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.count());
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <std::intmax_t Base, std::intmax_t Exponent>
	struct meta<REX::Unit<Base, Exponent>>
	{
	public:
		inline static constexpr auto value = [](auto&& a_self) -> decltype(auto) {
			return a_self._value;
		};
	};
}
#endif
