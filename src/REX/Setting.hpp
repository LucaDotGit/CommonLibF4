#pragma once

#include "REX/ISetting.hpp"

namespace REX
{
	template <class T, class Entry>
	class Setting : public ISetting<Entry>
	{
	public:
		using value_type = T;
		using entry_type = Entry;

		Setting() noexcept(std::is_nothrow_default_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type>)
			:
			_value(),
			_defaultValue()
		{
		}

		explicit Setting(const value_type& a_defaultValue) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
			:
			_value(a_defaultValue),
			_defaultValue(a_defaultValue)
		{
		}

		~Setting() noexcept(std::is_nothrow_destructible_v<value_type>) override = default;

		Setting(const Setting&) = delete;

		Setting(Setting&&) noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		auto operator=(const Setting&) -> Setting& = delete;

		auto operator=(Setting&&) noexcept(std::is_nothrow_move_assignable_v<value_type>) -> Setting&
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]]
		explicit operator value_type() const //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_trivially_copy_constructible_v<value_type>)
		{
			return _value;
		}

		[[nodiscard]]
		auto GetValue() & noexcept -> value_type&
		{
			return _value;
		}

		[[nodiscard]]
		auto GetValue() const& noexcept -> const value_type&
		{
			return _value;
		}

		[[nodiscard]]
		auto GetValue() && //
			noexcept(std::is_nothrow_move_constructible_v<value_type>) -> value_type&&
			requires(std::is_move_constructible_v<value_type>)
		{
			return std::move(_value);
		}

		[[nodiscard]]
		auto GetValue() const&& //
			noexcept(std::is_nothrow_move_constructible_v<value_type>) -> const value_type&&
			requires(std::is_move_constructible_v<value_type>)
		{
			return std::move(_value);
		}

		[[nodiscard]]
		auto GetDefaultValue() noexcept -> const value_type&
		{
			return _defaultValue;
		}

		void SetValue(const value_type& a_value) noexcept(std::is_nothrow_copy_assignable_v<value_type>)
			requires(std::is_copy_assignable_v<value_type>)
		{
			_value = a_value;
		}

		void SetValue(value_type&& a_value) noexcept(std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_move_assignable_v<value_type>)
		{
			_value = std::move(a_value);
		}

		void ResetValue() noexcept(std::is_nothrow_copy_assignable_v<value_type>)
			requires(std::is_copy_assignable_v<value_type>)
		{
			_value = _defaultValue;
		}

	protected:
		value_type _value;
		value_type _defaultValue;
	};
}
