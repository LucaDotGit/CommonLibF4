#pragma once

#if __has_include(<glaze/glaze.hpp>)

#include "REX/Contract.hpp"
#include "REX/Conversion.hpp"

namespace REX::Glaze
{
	template <class T, auto Options>
	concept ReadWritable = glz::read_supported<T, Options.format> && glz::write_supported<T, Options.format>;

	template <auto Options, glz::num_mode NumberMode, template <class> class MapType>
	concept GenericReadWritable = glz::read_supported<glz::generic_json<NumberMode, MapType>, Options.format> &&
								  glz::write_supported<glz::generic_json<NumberMode, MapType>, Options.format>;

	template <class T>
	using MapType = glz::ordered_small_map<T>;

	inline constexpr auto DEFAULT_NUMBER_MODE = glz::num_mode::u64;

	inline constexpr auto KEY_SEPARATOR = "/"sv;

	template <glz::num_mode NumberMode, template <class> class MapType>
	[[nodiscard]]
	auto Flatten(const glz::generic_json<NumberMode, MapType>& a_root) -> glz::generic_json<NumberMode, MapType>
	{
		using value_type = glz::generic_json<NumberMode, MapType>;

		const auto flattenPair =
			[](value_type::object_t& a_flatObject, const std::string& a_key, const value_type& a_value) -> void {
			const auto subFlatObject = Flatten(a_value);
			if (!subFlatObject.is_object()) {
				a_flatObject.emplace(a_key, subFlatObject);
				return;
			}

			for (auto&& [subKey, subValue] : subFlatObject.get_object()) {
				auto fullKey = std::string();
				fullKey.reserve(KEY_SEPARATOR.size() + a_key.size() + KEY_SEPARATOR.size() + subKey.size());

				fullKey += KEY_SEPARATOR;
				fullKey += a_key;
				fullKey += KEY_SEPARATOR;
				fullKey += subKey;

				a_flatObject.emplace(std::move(fullKey), subValue);
			}
		};

		if (a_root.is_object()) {
			auto flatObject = typename value_type::object_t();

			for (auto&& [key, value] : a_root.get_object()) {
				flattenPair(flatObject, key, value);
			}

			return flatObject;
		}

		if (a_root.is_array()) {
			auto flatObject = typename value_type::object_t();

			const auto& array = a_root.get_array();

			for (auto i = static_cast<std::size_t>(0); i < array.size(); i++) {
				const auto indexString = REX::ToString(i);
				if (!indexString.has_value()) [[unlikely]] {
					REX::Assert(false);
					continue;
				}

				flattenPair(flatObject, indexString.value(), array[i]);
			}

			return flatObject;
		}

		return a_root;
	}
}

#endif
