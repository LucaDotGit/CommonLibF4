#pragma once

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Conversion.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Error.hpp"
#include "REX/ZString.hpp"

namespace REX::INI
{
	class Options final
	{
	public:
		bool allowKeyOnly{true};
		bool allowMultiKey{false};
		bool prependBom{false};
		bool useQuotes{true};
		bool useSpaces{true};
		bool useUnicode{true};
	};

	using EntryType = std::pair<std::reference_wrapper<CSimpleIniCaseA>, std::string_view>;

	using ErrorNumber = SI_Error;

	class TypeConfig
	{
	public:
		using null_type = std::nullptr_t;
		using bool_type = bool;
		using int_type = std::int64_t;
		using uint_type = std::uint64_t;
		using float_type = REX::Float64;
		using string_type = REX::ZStringView;
	};

	template <class TypeConfig = INI::TypeConfig>
	using VariantType = std::variant<
		typename TypeConfig::null_type,
		typename TypeConfig::bool_type,
		typename TypeConfig::int_type,
		typename TypeConfig::uint_type,
		typename TypeConfig::float_type,
		typename TypeConfig::string_type>;

	template <class T>
	class ValueEntry final
	{
	public:
		using value_type = T;

		value_type value{};
		REX::ZStringView comment;
	};

	inline constexpr auto DEFAULT_OPTIONS = Options();

	inline constexpr auto KEY_SEPARATOR = ":"sv;

	[[nodiscard]]
	auto CreatePosixError(ErrorNumber a_errorCode) noexcept -> REX::PosixError;

	[[nodiscard]]
	constexpr auto SplitKey(std::string_view a_key) -> std::pair<std::string_view, std::string_view>
	{
		const auto separatorPos = a_key.find(KEY_SEPARATOR);
		if (separatorPos == std::string_view::npos) {
			return {""sv, a_key};
		}

		const auto sectionName = a_key.substr(0, separatorPos);
		const auto keyName = a_key.substr(separatorPos + KEY_SEPARATOR.size());

		return {sectionName, keyName};
	}

	[[nodiscard]]
	constexpr auto JoinKey(std::string_view a_section, std::string_view a_key) -> std::string
	{
		if (a_section.empty()) {
			return std::string(a_key);
		}

		auto result = std::string();
		result.reserve(a_section.size() + KEY_SEPARATOR.size() + a_key.size());

		result += a_section;
		result += KEY_SEPARATOR;
		result += a_key;

		return result;
	}

	template <class EntryType>
	void Setup(EntryType& a_entry, const Options& a_options)
	{
		a_entry.SetAllowKeyOnly(a_options.allowKeyOnly);
		a_entry.SetMultiKey(a_options.allowMultiKey);
		a_entry.SetQuotes(a_options.useQuotes);
		a_entry.SetSpaces(a_options.useSpaces);
		a_entry.SetUnicode(a_options.useUnicode);
	}

	template <class T, class EntryType>
	[[nodiscard]]
	auto GetValue(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key)
		-> std::expected<ValueEntry<T>, REX::PosixError>
		requires(REX::null_pointer<T>)
	{
		auto valueEntries = typename EntryType::TNamesDepend();
		if (!a_entry.GetAllValues(a_section.data(), a_key.data(), valueEntries) || valueEntries.empty()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::invalid_argument));
		}

		const auto& valueEntry = valueEntries.front();
		if (!valueEntry.pItem) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto commentView = valueEntry.pComment ? valueEntry.pComment : ""sv;
		return ValueEntry<T>{.value = nullptr, .comment = commentView};
	}

	template <class T, class EntryType>
	auto SetValue(
		EntryType& a_entry,
		REX::ZStringView a_section,
		REX::ZStringView a_key,
		[[maybe_unused]] T a_value,
		REX::ZStringView a_comment = {}) -> bool
		requires(REX::null_pointer<T>)
	{
		constexpr auto NULL_STRING = ""sv;
		return a_entry.SetValue(a_section.data(), a_key.data(), NULL_STRING.data(), a_comment.data()) >= SI_OK;
	}

	template <class T, class EntryType>
	[[nodiscard]]
	auto GetValue(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key)
		-> std::expected<ValueEntry<T>, REX::PosixError>
		requires(REX::boolean<T>)
	{
		auto valueEntries = typename EntryType::TNamesDepend();
		if (!a_entry.GetAllValues(a_section.data(), a_key.data(), valueEntries) || valueEntries.empty()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::invalid_argument));
		}

		const auto& valueEntry = valueEntries.front();
		if (!valueEntry.pItem) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto value = REX::FromString<T>(std::string_view(valueEntry.pItem), REX::BoolFormat::All);
		if (!value.has_value()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto commentView = valueEntry.pComment ? valueEntry.pComment : ""sv;
		return ValueEntry<T>{.value = value.value(), .comment = commentView};
	}

	template <class T, class EntryType>
	auto SetValue(
		EntryType& a_entry,
		REX::ZStringView a_section,
		REX::ZStringView a_key,
		T a_value,
		REX::ZStringView a_comment = {}) -> bool
		requires(REX::boolean<T>)
	{
		const auto stringValue = REX::ToString(a_value);
		if (!stringValue.has_value()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return a_entry.SetValue(a_section.data(), a_key.data(), stringValue->data(), a_comment.data()) >= SI_OK;
	}

	template <class T, class EntryType>
	[[nodiscard]]
	auto GetValue(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key)
		-> std::expected<ValueEntry<T>, REX::PosixError>
		requires(REX::number<T>)
	{
		auto valueEntries = typename EntryType::TNamesDepend();
		if (!a_entry.GetAllValues(a_section.data(), a_key.data(), valueEntries) || valueEntries.empty()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::invalid_argument));
		}

		const auto& valueEntry = valueEntries.front();
		if (!valueEntry.pItem) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto value = REX::FromString<T>(std::string_view(valueEntry.pItem));
		if (!value.has_value()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto commentView = valueEntry.pComment ? valueEntry.pComment : ""sv;
		return ValueEntry<T>{.value = value.value(), .comment = commentView};
	}

	template <class T, class EntryType>
	auto SetValue(
		EntryType& a_entry,
		REX::ZStringView a_section,
		REX::ZStringView a_key,
		T a_value,
		REX::ZStringView a_comment = {}) -> bool
		requires(REX::number<T>)
	{
		const auto stringValue = REX::ToString(a_value);
		if (!stringValue.has_value()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return a_entry.SetValue(a_section.data(), a_key.data(), stringValue->data(), a_comment.data()) >= SI_OK;
	}

	template <class T, class EntryType>
	[[nodiscard]]
	auto GetValue(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key)
		-> std::expected<ValueEntry<T>, REX::PosixError>
		requires(std::same_as<T, std::string> || std::same_as<T, std::string_view>)
	{
		auto valueEntries = typename EntryType::TNamesDepend();
		if (!a_entry.GetAllValues(a_section.data(), a_key.data(), valueEntries) || valueEntries.empty()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::invalid_argument));
		}

		const auto& valueEntry = valueEntries.front();
		if (!valueEntry.pItem) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto commentView = valueEntry.pComment ? valueEntry.pComment : ""sv;
		return ValueEntry<T>{.value = valueEntry.pItem, .comment = commentView};
	}

	template <class T, class EntryType>
	auto SetValue(
		EntryType& a_entry,
		REX::ZStringView a_section,
		REX::ZStringView a_key,
		const T& a_value,
		REX::ZStringView a_comment = {}) -> bool
		requires(std::same_as<T, std::string> || std::same_as<T, std::string_view>)
	{
		return a_entry.SetValue(a_section.data(), a_key.data(), a_value.data(), a_comment.data()) >= SI_OK;
	}

	template <class T, class EntryType>
	[[nodiscard]]
	auto GetValue(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key)
		-> std::expected<ValueEntry<T>, REX::PosixError>
		requires(std::same_as<T, std::filesystem::path>)
	{
		auto valueEntries = typename EntryType::TNamesDepend();
		if (!a_entry.GetAllValues(a_section.data(), a_key.data(), valueEntries) || valueEntries.empty()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::invalid_argument));
		}

		const auto& valueEntry = valueEntries.front();
		if (!valueEntry.pItem) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto commentView = valueEntry.pComment ? valueEntry.pComment : ""sv;
		return ValueEntry<T>{
			.value = std::filesystem::path(std::string_view(valueEntry.pItem), std::filesystem::path::generic_format),
			.comment = commentView
		};
	}

	template <class T, class EntryType>
	auto SetValue(
		EntryType& a_entry,
		REX::ZStringView a_section,
		REX::ZStringView a_key,
		const T& a_value,
		REX::ZStringView a_comment = {}) -> bool
		requires(std::same_as<T, std::filesystem::path>)
	{
		return a_entry.SetValue(a_section.data(), a_key.data(), a_value.generic_string().data(), a_comment.data()) >=
			   SI_OK;
	}

	template <class EntryType, class TypeConfig = INI::TypeConfig>
	auto GetDetectedValue(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key)
		-> std::expected<ValueEntry<VariantType<TypeConfig>>, REX::PosixError>
	{
		auto valueEntries = typename EntryType::TNamesDepend();
		if (!a_entry.GetAllValues(a_section.data(), a_key.data(), valueEntries) || valueEntries.empty()) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::invalid_argument));
		}

		const auto& valueEntry = valueEntries.front();
		if (!valueEntry.pItem) {
			return std::unexpected(REX::CreatePosixError(REX::PosixErrorCode::bad_message));
		}

		const auto valueView = std::string_view(valueEntry.pItem);
		const auto commentView = valueEntry.pComment ? valueEntry.pComment : ""sv;

		if (valueView.empty()) {
			return ValueEntry<VariantType<TypeConfig>>{
				.value = typename TypeConfig::null_type(),
				.comment = commentView
			};
		}

		{
			constexpr auto BOOL_FORMAT =
				REX::EnumSet(REX::BoolFormat::TrueFalse, REX::BoolFormat::YesNo, REX::BoolFormat::OnOff);

			const auto boolValue = REX::FromString<typename TypeConfig::bool_type>(valueView, BOOL_FORMAT.get());
			if (boolValue.has_value()) {
				return ValueEntry<VariantType<TypeConfig>>{.value = boolValue.value(), .comment = commentView};
			}
		}

		{
			const auto intValue = REX::FromString<typename TypeConfig::int_type>(valueView);
			if (intValue.has_value()) {
				return ValueEntry<VariantType<TypeConfig>>{.value = intValue.value(), .comment = commentView};
			}
		}

		{
			const auto uintValue = REX::FromString<typename TypeConfig::uint_type>(valueView);
			if (uintValue.has_value()) {
				return ValueEntry<VariantType<TypeConfig>>{.value = uintValue.value(), .comment = commentView};
			}
		}

		{
			const auto floatValue = REX::FromString<typename TypeConfig::float_type>(valueView);
			if (floatValue.has_value()) {
				return ValueEntry<VariantType<TypeConfig>>{.value = floatValue.value(), .comment = commentView};
			}
		}

		return ValueEntry<VariantType<TypeConfig>>{
			.value = typename TypeConfig::string_type(valueView),
			.comment = commentView
		};
	}

	template <class EntryType, class TypeConfig = INI::TypeConfig>
	auto SetDetectedValue(
		EntryType& a_entry,
		REX::ZStringView a_section,
		REX::ZStringView a_key,
		const VariantType<TypeConfig>& a_value,
		REX::ZStringView a_comment = {}) -> bool
	{
		return std::visit(
			[&a_entry, &a_section, &a_key, &a_comment](auto&& a_arg) -> bool {
				return SetValue(a_entry, a_section, a_key, std::forward<decltype(a_arg)>(a_arg), a_comment);
			},
			a_value);
	}

	template <class T, class EntryType>
	concept ReadWritable = requires(const EntryType& a_entry, REX::ZStringView a_section, REX::ZStringView a_key) {
		{
			GetValue<T>(a_entry, a_section, a_key)
		} -> std::same_as<std::expected<ValueEntry<T>, REX::PosixError>>;
		{
			SetValue(a_entry, a_section, a_key, std::declval<T>())
		} -> std::same_as<bool>;
	};
}

#endif
