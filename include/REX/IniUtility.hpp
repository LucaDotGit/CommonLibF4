#pragma once

#if COMMONLIB_OPTION_INI == 1

#include "REX/Concepts.hpp"
#include "REX/Convert.hpp"
#include "REX/Error.hpp"
#include "REX/ZString.hpp"

#include <SimpleIni.h>

namespace REX::Ini
{
	inline constexpr auto SETTING_SEPARATOR = ':';

	inline constexpr auto ALLOW_KEY_ONLY = true;
	inline constexpr auto USE_UNICODE = true;
	inline constexpr auto USE_QUOTES = true;
	inline constexpr auto PREPEND_BOM = false;

	using ErrorNumber = SI_Error;

	struct TypeConfig
	{
	public:
		using null_type = std::nullptr_t;
		using bool_type = bool;
		using int_type = std::int64_t;
		using uint_type = std::uint64_t;
		using float_type = REX::Float64;
		using string_type = REX::zstring_view;
	};

	template <class TypeConfig = Ini::TypeConfig>
	using VariantType = std::variant<
		typename TypeConfig::null_type,
		typename TypeConfig::bool_type,
		typename TypeConfig::int_type,
		typename TypeConfig::uint_type,
		typename TypeConfig::float_type,
		typename TypeConfig::string_type>;

	[[nodiscard]] bool IsValid(ErrorNumber a_errorCode) noexcept;

	[[nodiscard]] REX::PosixError CreatePosixErrorCode(ErrorNumber a_errorCode) noexcept;

	[[nodiscard]] auto CombineSetting(std::string_view a_section, std::string_view a_key)
		-> std::string;

	[[nodiscard]] auto SplitSetting(std::string_view a_setting)
		-> std::pair<std::string_view, std::string_view>;

	template <class T, class IniType>
	[[nodiscard]] auto GetValue(const IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key)
		-> std::optional<T>
		requires(REX::nullable<T>)
	{
		constexpr auto* DEFAULT_VALUE = static_cast<const char*>(nullptr);

		const auto* value = a_ini.GetValue(a_section.data(), a_key.data(), DEFAULT_VALUE);
		if (value == DEFAULT_VALUE) {
			return std::nullopt;
		}

		const auto stringView = REX::zstring_view(value);
		if (!stringView.empty()) {
			return std::nullopt;
		}

		return nullptr;
	}

	template <class T, class IniType>
	bool SetValue(IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key, [[maybe_unused]] T a_value)
		requires(REX::nullable<T>)
	{
		constexpr auto NULL_STRING = ""sv;
		return a_ini.SetValue(a_section.data(), a_key.data(), NULL_STRING.data()) >= SI_OK;
	}

	template <class T, class IniType>
	[[nodiscard]] auto GetValue(const IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key)
		-> std::optional<T>
		requires(REX::boolean<T>)
	{
		constexpr auto* DEFAULT_VALUE = static_cast<const char*>(nullptr);

		const auto* stringValue = a_ini.GetValue(a_section.data(), a_key.data(), DEFAULT_VALUE);
		if (stringValue == DEFAULT_VALUE) {
			return std::nullopt;
		}

		auto result = REX::FromString<bool>(stringValue, REX::BoolFormat::kAll);
		if (!result.has_value()) {
			return std::nullopt;
		}

		return result.value();
	}

	template <class T, class IniType>
	bool SetValue(IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key, T a_value)
		requires(REX::boolean<T>)
	{
		auto string = REX::ToString(a_value);
		if (!string.has_value()) {
			return false;
		}

		return a_ini.SetValue(a_section.data(), a_key.data(), string->data()) >= SI_OK;
	}

	template <class T, class IniType>
	[[nodiscard]] auto GetValue(const IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key)
		-> std::optional<T>
		requires(REX::number<T>)
	{
		constexpr auto* DEFAULT_VALUE = static_cast<const char*>(nullptr);

		const auto* stringValue = a_ini.GetValue(a_section.data(), a_key.data(), DEFAULT_VALUE);
		if (stringValue == DEFAULT_VALUE) {
			return std::nullopt;
		}

		auto result = REX::FromString<T>(stringValue);
		if (!result.has_value()) {
			return std::nullopt;
		}

		return result.value();
	}

	template <class T, class IniType>
	bool SetValue(IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key, T a_value)
		requires(REX::number<T>)
	{
		auto string = REX::ToString(a_value);
		if (!string.has_value()) {
			return false;
		}

		return a_ini.SetValue(a_section.data(), a_key.data(), string->data()) >= SI_OK;
	}

	template <class T, class IniType>
	[[nodiscard]] auto GetValue(const IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key)
		-> std::optional<T>
		requires(std::same_as<T, std::string> || std::same_as<T, std::string_view> || std::same_as<T, std::filesystem::path>)
	{
		constexpr auto* DEFAULT_VALUE = static_cast<const char*>(nullptr);

		const auto* value = a_ini.GetValue(a_section.data(), a_key.data(), DEFAULT_VALUE);
		if (value == DEFAULT_VALUE) {
			return std::nullopt;
		}

		return T(value);
	}

	template <class T, class IniType>
	bool SetValue(IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key, const T& a_value)
		requires(std::same_as<T, std::string> || std::same_as<T, std::string_view>)
	{
		return a_ini.SetValue(a_section.data(), a_key.data(), a_value.data()) >= SI_OK;
	}

	template <class T, class IniType>
	bool SetValue(IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key, const T& a_value)
		requires(std::same_as<T, std::filesystem::path>)
	{
		return a_ini.SetValue(a_section.data(), a_key.data(), a_value.generic_string().data()) >= SI_OK;
	}

	template <class IniType, class TypeConfig = Ini::TypeConfig>
	auto GetDetectedValue(const IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key)
		-> std::optional<VariantType<TypeConfig>>
	{
		constexpr auto* DEFAULT_VALUE = static_cast<const char*>(nullptr);

		const auto* stringValue = a_ini.GetValue(a_section.data(), a_key.data(), DEFAULT_VALUE);
		if (stringValue == DEFAULT_VALUE) {
			return std::nullopt;
		}

		const auto stringView = REX::zstring_view(stringValue);
		if (stringView.empty()) {
			return typename TypeConfig::null_type();
		}

		{
			constexpr auto BOOL_FORMAT = REX::EnumSet(REX::BoolFormat::kTrueFalse, REX::BoolFormat::kYesNo, REX::BoolFormat::kOnOff);

			auto boolValue = REX::FromString<typename TypeConfig::bool_type>(stringView, BOOL_FORMAT.get());
			if (boolValue.has_value()) {
				return boolValue.value();
			}
		}

		{
			auto intValue = REX::FromString<typename TypeConfig::int_type>(stringView);
			if (intValue.has_value()) {
				return intValue.value();
			}
		}

		{
			auto uintValue = REX::FromString<typename TypeConfig::uint_type>(stringView);
			if (uintValue.has_value()) {
				return uintValue.value();
			}
		}

		{
			auto floatValue = REX::FromString<typename TypeConfig::float_type>(stringView);
			if (floatValue.has_value()) {
				return floatValue.value();
			}
		}

		return typename TypeConfig::string_type(stringView);
	}

	template <class IniType, class TypeConfig = Ini::TypeConfig>
	bool SetDetectedValue(IniType& a_ini, REX::zstring_view a_section, REX::zstring_view a_key, const VariantType<TypeConfig>& a_value)
	{
		return std::visit(
			[&a_ini, a_section, a_key](auto&& a_arg) -> bool {
				return SetValue(a_ini, a_section, a_key, std::forward<decltype(a_arg)>(a_arg));
			},
			a_value);
	}

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::nullptr_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::nullptr_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<bool>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, bool);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int8_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int8_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint8_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint8_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int16_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int16_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint16_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint16_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int32_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int32_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint32_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint32_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int64_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int64_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint64_t>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint64_t);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<REX::Float32>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, REX::Float32);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<REX::Float64>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, REX::Float64);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<REX::Float128>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, REX::Float128);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::string>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const std::string&);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::string_view>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const REX::zstring_view&);

	extern template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::filesystem::path>;
	extern template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const std::filesystem::path&);

	extern template auto GetDetectedValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<VariantType<>>;
	extern template bool SetDetectedValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const VariantType<>&);
}

#endif
