#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	class ISetting
		: public std::enable_shared_from_this<ISetting>
	{
	public:
		virtual ~ISetting() noexcept = default;

		virtual bool Load(const std::any& a_data, bool a_isMain) = 0;
		virtual bool Save(const std::any& a_data) = 0;
	};

	template <class T, class Store>
	class Setting
		: public ISetting
	{
	public:
		using value_type = T;
		using store_type = Store;

	protected:
		using reference = value_type&;
		using const_reference = const value_type&;

	public:
		Setting() = default;
		~Setting() noexcept override = default;

		template <class U = std::conditional_t<REX::trivially_writable<value_type>, value_type, const_reference>>
		explicit Setting(U a_defaultValue)
			: _value(a_defaultValue),
			  _defaultValue(a_defaultValue)
		{
		}

		Setting(const Setting&) = default;
		Setting(Setting&&) noexcept = default;

		Setting& operator=(const Setting&) = default;
		Setting& operator=(Setting&&) noexcept = default;

		template <class U = std::conditional_t<REX::trivially_writable<value_type>, value_type, const_reference>>
		[[nodiscard]] explicit operator U() const //
			noexcept(std::is_nothrow_copy_constructible_v<U>)
		{
			return _value;
		}

		template <class U = std::conditional_t<REX::trivially_writable<value_type>, value_type, const_reference>>
		[[nodiscard]] U GetValue() const //
			noexcept(std::is_nothrow_copy_constructible_v<U>)
		{
			return _value;
		}

		template <class U = std::conditional_t<REX::trivially_writable<value_type>, value_type, const_reference>>
		[[nodiscard]] U GetDefaultValue() const //
			noexcept(std::is_nothrow_copy_constructible_v<U>)
		{
			return _defaultValue;
		}

		template <class U>
		[[nodiscard]] U GetValueAs() const //
			noexcept(std::is_nothrow_convertible_v<value_type, U>)
			requires(std::is_convertible_v<value_type, U>)
		{
			return static_cast<U>(_value);
		}

		template <class U>
		[[nodiscard]] U GetDefaultValueAs() const //
			noexcept(std::is_nothrow_convertible_v<value_type, U>)
			requires(std::is_convertible_v<value_type, U>)
		{
			return static_cast<U>(_defaultValue);
		}

		template <class U = std::conditional_t<REX::trivially_writable<value_type>, value_type, const_reference>>
		void SetValue(U a_value) //
			noexcept(std::is_nothrow_assignable_v<U, value_type>)
		{
			_value = a_value;
		}

	protected:
		value_type _value;
		value_type _defaultValue;
	};
}
