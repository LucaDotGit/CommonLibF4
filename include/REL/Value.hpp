#pragma once

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"

#include "REX/Hash.hpp"

namespace REL
{
	template <class T>
	class IValue
	{
	public:
		using value_type = T;

		static_assert(std::is_default_constructible_v<value_type>);
		static_assert(std::is_destructible_v<value_type>);

		virtual ~IValue() //
			noexcept(std::is_nothrow_destructible_v<value_type>) = default;

		[[nodiscard]] virtual auto GetValue() const noexcept
			-> std::optional<std::reference_wrapper<const value_type>> = 0;

		[[nodiscard]] virtual value_type GetValueOrDefault() const //
			noexcept(std::is_nothrow_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>) = 0;
	};

	template <class T, Runtime R0 = Runtime::LATEST, Runtime... R>
	class Value final
		: public IValue<T>
	{
	public:
		using value_type = T;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		static_assert(std::is_default_constructible_v<value_type>);
		static_assert(std::is_destructible_v<value_type>);

		inline static constexpr auto RUNTIMES = std::array{ R0, R... };

		constexpr Value() //
			noexcept(std::is_nothrow_default_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type>)
		= default;

		constexpr ~Value()										 //
			noexcept(std::is_nothrow_destructible_v<value_type>) //
			override = default;

		template <class... V>
		constexpr explicit Value(V&&... a_values) //
			noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) &&
					 (sizeof...(V) == sizeof...(R) + 1))
			: _values{ static_cast<value_type>(std::forward<V>(a_values))... }
		{
		}

		template <class V>
		constexpr Value(const Value<V, R0, R...>& a_rhs) //
			noexcept((std::is_nothrow_copy_constructible_v<value_type> |
						 std::is_nothrow_move_constructible_v<value_type>) &&
					 std::is_nothrow_convertible_v<V, value_type>)
			requires((std::is_copy_constructible_v<value_type> ||
						 std::is_move_constructible_v<value_type>) &&
					 std::is_convertible_v<V, value_type>)
		{
			for (auto i = static_cast<std::size_t>(0); i < RUNTIMES.size(); i++) {
				_values[i] = static_cast<value_type>(a_rhs.GetValues()[i]);
			}
		}

		constexpr Value(const Value&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		= default;

		constexpr Value(Value&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		template <class V>
		constexpr Value& operator=(const Value<V, R0, R...>& a_rhs) //
			noexcept((std::is_nothrow_copy_assignable_v<value_type> ||
						 std::is_nothrow_move_assignable_v<value_type>) &&
					 std::is_nothrow_convertible_v<V, value_type>)
			requires((std::is_copy_assignable_v<value_type> ||
						 std::is_move_assignable_v<value_type>) &&
					 std::is_convertible_v<V, value_type>)
		{
			for (auto i = static_cast<std::size_t>(0); i < RUNTIMES.size(); i++) {
				_values[i] = static_cast<value_type>(a_rhs.GetValues()[i]);
			}

			return *this;
		}

		constexpr Value& operator=(const Value&) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
			requires(std::is_copy_assignable_v<value_type>)
		= default;

		constexpr Value& operator=(Value&&) //
			noexcept(std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]] constexpr bool operator==(const Value&) const //
			noexcept(REX::nothrow_equality_comparable<value_type>)
			requires(REX::equality_comparable<value_type>)
		= default;

		[[nodiscard]] constexpr bool operator!=(const Value&) const //
			noexcept(REX::nothrow_equality_comparable<value_type>)
			requires(REX::equality_comparable<value_type>)
		= default;

		[[nodiscard]] constexpr auto operator<=>(const Value&) const //
			noexcept(REX::nothrow_three_way_comparable<value_type>)
			requires(REX::three_way_comparable<value_type>)
		= default;

		[[nodiscard]] constexpr const auto& GetValues() const noexcept { return _values; }

		[[nodiscard]] constexpr auto GetValue(Runtime a_runtime) const noexcept
			-> std::optional<std::reference_wrapper<const value_type>>
		{
			if constexpr (RUNTIMES.size() == 1) {
				if (a_runtime > RUNTIMES.front()) {
					return std::nullopt;
				}

				return std::cref(_values.front());
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) {
					return std::nullopt;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), runtimeIt - 1));
				return std::ref(_values[index]);
			}
		}

		[[nodiscard]] auto GetValue() const noexcept
			-> std::optional<std::reference_wrapper<const value_type>> override
		{
			const auto currentRuntime = REL::Module::GetSingleton()->GetRuntime();
			return GetValue(currentRuntime);
		}

		[[nodiscard]] constexpr value_type GetValueOrDefault(Runtime a_runtime) const //
			noexcept(std::is_nothrow_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type> &&
					 std::is_copy_constructible_v<value_type>)
		{
			if constexpr (RUNTIMES.size() == 1) {
				if (a_runtime > RUNTIMES.front()) {
					return {};
				}

				return _values.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) {
					return {};
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), runtimeIt - 1));
				return _values[index];
			}
		}

		[[nodiscard]] value_type GetValueOrDefault() const //
			noexcept(std::is_nothrow_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>) override
		{
			const auto currentRuntime = REL::Module::GetSingleton()->GetRuntime();
			return GetValueOrDefault(currentRuntime);
		}

		constexpr void swap(Value& a_other) //
			noexcept(std::is_nothrow_swappable_v<value_type>)
			requires(std::is_swappable_v<value_type>)
		{
			std::swap(_values, a_other._values);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _values;
	};

	template <class T>
	Value(T) -> Value<T>;

	template <class T, Runtime R0 = Runtime::LATEST, Runtime... R>
	constexpr void swap(Value<T, R0, R...>& a_lhs, Value<T, R0, R...>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<Value<T, R0, R...>>)
		requires(std::is_swappable_v<Value<T, R0, R...>>)
	{
		a_lhs.swap(a_rhs);
	}

	template <class V>
	[[nodiscard]] constexpr auto CreateValue(V&& a_value) //
		noexcept(std::is_nothrow_constructible_v<Value<std::decay_t<V>>, V>)
		requires(std::is_constructible_v<Value<std::decay_t<V>>, V>)
	{
		return Value<std::decay_t<V>>{ std::forward<V>(a_value) };
	}

	template <Runtime R0, Runtime... R, class... V>
	[[nodiscard]] constexpr auto CreateValue(V&&... a_values) //
		noexcept(std::is_nothrow_constructible_v<Value<std::common_type_t<V...>, R0, R...>, V...>)
		requires(std::is_constructible_v<Value<std::common_type_t<V...>, R0, R...>, V...> &&
				 (sizeof...(V) == sizeof...(R) + 1))
	{
		return Value<std::common_type_t<V...>, R0, R...>{ std::forward<V>(a_values)... };
	}
}

namespace std
{
	template <REX::hashable T, REL::Runtime R0, REL::Runtime... R>
	struct hash<REL::Value<T, R0, R...>>
	{
		[[nodiscard]] std::size_t operator()(const REL::Value<T, R0, R...>& a_value) const //
			noexcept(REX::nothrow_hashable<T>)
		{
			return REX::HashRange(a_value.GetValues());
		}
	};
}
