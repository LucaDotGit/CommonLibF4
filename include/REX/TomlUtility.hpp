#pragma once

#if COMMONLIB_OPTION_TOML == 1

#include <toml.hpp>

namespace REX::Toml
{
	inline constexpr auto TABLE_SEPARATOR = '.';
	inline constexpr auto KEY_SEPARATOR = ':';

	inline constexpr auto SPECIFICATION_VERSION = toml::spec::v(1, 1, 0);

	[[nodiscard]] auto SplitSetting(std::string_view a_setting) -> std::pair<std::string_view, std::string_view>;

	template <class TypeConfig>
	[[nodiscard]] auto GetPointer(toml::basic_value<TypeConfig>& a_toml, std::string_view a_tableName) -> toml::basic_value<TypeConfig>*
	{
		auto* currentValue = std::addressof(a_toml);
		if (!currentValue->is_table()) {
			return nullptr;
		}

		for (const auto sectionPart : std::ranges::views::split(a_tableName, TABLE_SEPARATOR)) {
			const auto sectionPartStr = std::string{ sectionPart.begin(), sectionPart.end() };
			if (sectionPartStr.empty()) {
				continue;
			}

			auto& currentTable = currentValue->as_table();

			const auto tableIt = currentTable.find(sectionPartStr);
			if (tableIt == currentTable.end()) {
				return nullptr;
			}

			auto& tableValue = tableIt->second;
			if (!tableValue.is_table()) {
				return nullptr;
			}

			currentValue = std::addressof(tableValue);
		}

		return currentValue;
	}

	extern template auto GetPointer(toml::basic_value<toml::type_config>&, std::string_view) -> toml::basic_value<toml::type_config>*;

	template <class TypeConfig>
	[[nodiscard]] auto GetPointer(const toml::basic_value<TypeConfig>& a_toml, std::string_view a_tableName) -> const toml::basic_value<TypeConfig>*
	{
		const auto* currentValue = std::addressof(a_toml);
		if (!currentValue->is_table()) {
			return nullptr;
		}

		for (const auto sectionPart : std::ranges::views::split(a_tableName, TABLE_SEPARATOR)) {
			const auto sectionPartStr = std::string{ sectionPart.begin(), sectionPart.end() };
			if (sectionPartStr.empty()) {
				continue;
			}

			const auto& currentTable = currentValue->as_table();

			const auto tableIt = currentTable.find(sectionPartStr);
			if (tableIt == currentTable.end()) {
				return nullptr;
			}

			const auto& tableValue = tableIt->second;
			if (!tableValue.is_table()) {
				return nullptr;
			}

			currentValue = std::addressof(tableValue);
		}

		return currentValue;
	}

	extern template auto GetPointer(const toml::basic_value<toml::type_config>&, std::string_view) -> const toml::basic_value<toml::type_config>*;

	template <class TypeConfig>
	[[nodiscard]] auto GetOrCreatePointer(toml::basic_value<TypeConfig>& a_toml, std::string_view a_tableName) -> toml::basic_value<TypeConfig>*
	{
		using value_type = toml::basic_value<TypeConfig>;

		if (!a_toml.is_table()) {
			a_toml = typename value_type::table_type();
		}

		auto* currentValue = std::addressof(a_toml);

		auto parts = std::ranges::views::split(a_tableName, TABLE_SEPARATOR);
		for (auto partIt = parts.begin(); partIt != parts.end(); partIt++) {
			const auto sectionPartStr = std::string{ (*partIt).begin(), (*partIt).end() };
			if (sectionPartStr.empty()) {
				continue;
			}

			auto& currentTable = currentValue->as_table();
			auto& nextValue = currentTable[sectionPartStr];

			if (!nextValue.is_table()) {
				nextValue = typename value_type::table_type();
			}

			if (std::next(partIt) != parts.end()) {
				nextValue.as_table_fmt().fmt = toml::table_format::implicit;
			}

			currentValue = std::addressof(nextValue);
		}

		return currentValue;
	}

	extern template auto GetOrCreatePointer(toml::basic_value<toml::type_config>&, std::string_view) -> toml::basic_value<toml::type_config>*;

	template <class TypeConfig>
	[[nodiscard]] auto Flatten(const toml::basic_value<TypeConfig>& a_toml) -> std::optional<toml::basic_value<TypeConfig>>
	{
		using value_type = toml::basic_value<TypeConfig>;

		if (!a_toml.is_table()) {
			return std::nullopt;
		}

		auto flatTable = typename value_type::table_type();

		auto& rootTable = a_toml.as_table();
		for (const auto& [key, value] : rootTable) {
			if (!value.is_table()) {
				flatTable.emplace(key, value);
				continue;
			}

			auto subTable = REX::Toml::Flatten(value);
			if (!subTable || !subTable->is_table()) {
				continue;
			}

			for (const auto& [subKey, subValue] : subTable->as_table()) {
				auto fullKey = std::string();
				fullKey.reserve(key.size() + 1 + subKey.size());
				fullKey.append(key);
				fullKey.push_back(REX::Toml::KEY_SEPARATOR);
				fullKey.append(subKey);

				flatTable.emplace(std::move(fullKey), subValue);
			}
		}

		return flatTable;
	}

	extern template auto Flatten(const toml::basic_value<toml::type_config>&) -> std::optional<toml::basic_value<toml::type_config>>;
}

#endif
