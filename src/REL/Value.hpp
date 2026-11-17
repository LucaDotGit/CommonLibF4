#pragma once

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"
#include "REX/Concepts.hpp"
#include "REX/Hashing.hpp"

namespace REL
{
	template <class T>
	class IValue
	{
	public:
		using value_type = T;

		static_assert(std::is_default_constructible_v<value_type>);
		static_assert(std::is_destructible_v<value_type>);

		IValue() noexcept(std::is_nothrow_default_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type>)
		= default;

		virtual ~IValue() noexcept(std::is_nothrow_destructible_v<value_type>) = default;

		IValue(const IValue&) = delete;

		IValue(IValue&&) noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		auto operator=(const IValue&) -> IValue& = delete;

		auto operator=(IValue&&) noexcept(std::is_nothrow_move_assignable_v<value_type>) -> IValue&
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]]
		auto operator==(const IValue& a_rhs) const //
			noexcept(REX::nothrow_equality_comparable<value_type>) -> bool
			requires(REX::equality_comparable<value_type>)
		{
			return GetValue() == a_rhs.GetValue();
		}

		[[nodiscard]]
		auto operator<=>(const IValue& a_rhs) const //
			noexcept(REX::nothrow_three_way_comparable<value_type>)
			requires(REX::three_way_comparable<value_type>)
		{
			return GetValue() <=> a_rhs.GetValue();
		}

		[[nodiscard]]
		virtual auto GetValue() const noexcept -> std::optional<std::reference_wrapper<const value_type>> = 0;

		[[nodiscard]]
		virtual auto GetValueOrDefault() const //
			noexcept(
				std::is_nothrow_default_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<value_type>)
				-> value_type = 0;
	};

	template <class T, REL::Runtime R0 = REL::Runtime::LATEST, REL::Runtime... R>
	class Value final : public IValue<T>
	{
	public:
		using value_type = T;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{R0, R...};

		constexpr Value() noexcept(std::is_nothrow_default_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type>)
		= default;

		constexpr ~Value() noexcept(std::is_nothrow_destructible_v<value_type>) override = default;

		template <class T2>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr Value(const Value<T2, R0, R...>& a_rhs) noexcept(
			std::is_nothrow_default_constructible_v<value_type> &&
			(std::is_nothrow_copy_constructible_v<value_type> | std::is_nothrow_move_constructible_v<value_type>) &&
			std::is_nothrow_convertible_v<T2, value_type>)
			requires(
				std::is_default_constructible_v<value_type> &&
				(std::is_copy_constructible_v<value_type> || std::is_move_constructible_v<value_type>) &&
				std::is_convertible_v<T2, value_type>)
		{
			for (auto i = static_cast<std::size_t>(0); i < RUNTIMES.size(); i++) {
				_values[i] = static_cast<value_type>(a_rhs.GetValues()[i]);
			}
		}

		template <class... V>
		constexpr explicit Value(V&&... a_values) noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) && (sizeof...(V) == sizeof...(R) + 1))
			:
			_values{static_cast<value_type>(std::forward<V>(a_values))...}
		{
		}

		constexpr Value(const Value& a_rhs) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
			:
			_values(a_rhs._values)
		{
		}

		constexpr Value(Value&&) noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		template <class T2>
		constexpr auto operator=(const Value<T2, R0, R...>& a_rhs) noexcept(
			std::is_nothrow_default_constructible_v<value_type> &&
			(std::is_nothrow_copy_assignable_v<value_type> || std::is_nothrow_move_assignable_v<value_type>) &&
			std::is_nothrow_convertible_v<T2, value_type>) -> Value&
			requires(
				std::is_default_constructible_v<value_type> &&
				(std::is_copy_assignable_v<value_type> || std::is_move_assignable_v<value_type>) &&
				std::is_convertible_v<T2, value_type>)
		{
			for (auto i = static_cast<std::size_t>(0); i < RUNTIMES.size(); i++) {
				_values[i] = static_cast<value_type>(a_rhs.GetValues()[i]);
			}

			return *this;
		}

		constexpr auto operator=(const Value& a_rhs) noexcept(std::is_nothrow_copy_assignable_v<value_type>) -> Value&
			requires(std::is_copy_assignable_v<value_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_values = a_rhs._values;
			return *this;
		}

		constexpr auto operator=(Value&&) noexcept(std::is_nothrow_move_assignable_v<value_type>) -> Value&
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]]
		constexpr auto GetValues() const noexcept -> const auto&
		{
			return _values;
		}

		[[nodiscard]]
		constexpr auto GetValue(REL::Runtime a_runtime) const noexcept
			-> std::optional<std::reference_wrapper<const value_type>>
		{
			if (a_runtime == REL::Runtime::INVALID) [[unlikely]] {
				return std::nullopt;
			}

			if constexpr (RUNTIMES.front() == REL::Runtime::LATEST) {
				return std::cref(_values.front());
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) [[unlikely]] {
					return std::nullopt;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), std::prev(runtimeIt)));
				return std::ref(_values[index]);
			}
		}

		[[nodiscard]]
		auto GetValue() const noexcept -> std::optional<std::reference_wrapper<const value_type>> override
		{
			const auto currentRuntime = REL::Module::GetSingleton().GetRuntime();
			return GetValue(currentRuntime);
		}

		[[nodiscard]]
		constexpr auto GetValueOrDefault(REL::Runtime a_runtime) const //
			noexcept(
				std::is_nothrow_default_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<value_type>)
				-> value_type
			requires(std::is_default_constructible_v<value_type> && std::is_copy_constructible_v<value_type>)
		{
			if (a_runtime == REL::Runtime::INVALID) [[unlikely]] {
				return value_type{};
			}

			if constexpr (RUNTIMES.front() == REL::Runtime::LATEST) {
				return _values.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) [[unlikely]] {
					return {};
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), std::prev(runtimeIt)));
				return _values[index];
			}
		}

		[[nodiscard]]
		auto GetValueOrDefault() const //
			noexcept(
				std::is_nothrow_default_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<value_type>)
				-> value_type override
		{
			const auto currentRuntime = REL::Module::GetSingleton().GetRuntime();
			return GetValueOrDefault(currentRuntime);
		}

		constexpr void swap(Value& a_other) noexcept(std::is_nothrow_swappable_v<value_type>)
			requires(std::is_swappable_v<value_type>)
		{
			std::swap(_values, a_other._values);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _values;
	};

	template <class T>
	Value(T) -> Value<T>;

	template <class T>
	[[nodiscard]]
	constexpr auto CreateValue(T&& a_value) noexcept(std::is_nothrow_constructible_v<Value<std::decay_t<T>>, T>)
		requires(std::is_constructible_v<Value<std::decay_t<T>>, T>)
	{
		return Value<std::decay_t<T>>{std::forward<T>(a_value)};
	}

	template <REL::Runtime R0, REL::Runtime... R, class... Args>
	[[nodiscard]]
	constexpr auto CreateValue(Args&&... a_values)
		noexcept(std::is_nothrow_constructible_v<Value<std::common_type_t<Args...>, R0, R...>, Args...>)
		requires(
			std::is_constructible_v<Value<std::common_type_t<Args...>, R0, R...>, Args...> &&
			(sizeof...(Args) == sizeof...(R) + 1))
	{
		return Value<std::common_type_t<Args...>, R0, R...>{std::forward<Args>(a_values)...};
	}

	static_assert([]() consteval noexcept -> bool {
		constexpr auto TEST_RUNTIME_01 = REL::CreateRuntime(1, 0, 0, 0);
		constexpr auto TEST_RUNTIME_02 = REL::CreateRuntime(1, 0, 0, 1);

		constexpr auto TEST_VALUE_01 = CreateValue<TEST_RUNTIME_01, TEST_RUNTIME_02>(12'345'678, 23'456'789);
		constexpr auto TEST_VALUE_02 = CreateValue<TEST_RUNTIME_02>(34'567'890);
		constexpr auto TEST_VALUE_03 = CreateValue<>(45'678'901);

		return (TEST_VALUE_01.GetValue(TEST_RUNTIME_01) == 12'345'678) &&
			   (TEST_VALUE_01.GetValue(TEST_RUNTIME_02) == 23'456'789) &&
			   (TEST_VALUE_01.GetValue(Runtime::LATEST) == 23'456'789) &&
			   (TEST_VALUE_02.GetValue(TEST_RUNTIME_01) == std::nullopt) &&
			   (TEST_VALUE_02.GetValue(TEST_RUNTIME_02) == 34'567'890) &&
			   (TEST_VALUE_02.GetValue(Runtime::LATEST) == 34'567'890) &&
			   (TEST_VALUE_03.GetValue(TEST_RUNTIME_01) == 45'678'901) &&
			   (TEST_VALUE_03.GetValue(TEST_RUNTIME_02) == 45'678'901) &&
			   (TEST_VALUE_03.GetValue(Runtime::LATEST) == 45'678'901);
	}());
}

namespace std
{
	template <REX::hashable T, REL::Runtime R0, REL::Runtime... R>
	struct hash<REL::Value<T, R0, R...>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REL::Value<T, R0, R...>& a_value) const //
			noexcept(REX::nothrow_hashable<T>) -> std::size_t
		{
			return REX::HashRange(a_value.GetValues());
		}
	};
}
