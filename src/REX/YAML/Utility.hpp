#pragma once

#if (COMMONLIB_FEATURE_YAML == 1)

#include "REX/Glaze/Utility.hpp"

namespace REX::YAML
{
	class Options final
	{
	public:
		// NOLINTBEGIN(readability-identifier-naming)
		std::uint32_t format{glz::YAML};
		std::uint32_t internal{0};
		bool comments{true};
		bool error_on_const_read{true};
		bool error_on_missing_array_elements{true};
		bool error_on_missing_keys{true};
		bool error_on_unknown_keys{false};
		bool escape_control_characters{true};
		bool minified{false};
		bool null_terminated{true};
		bool partial_read{false};
		bool shrink_to_fit{true};
		bool skip_null_members{true};
		bool validate_skipped{true};
		bool validate_trailing_whitespace{true};
		std::uint8_t indent_width{4};
		// NOLINTEND(readability-identifier-naming)
	};

	inline constexpr auto DEFAULT_OPTIONS = Options();

	inline constexpr auto KEY_SEPARATOR = REX::Glaze::KEY_SEPARATOR;

	template <glz::num_mode NumberMode, template <class> class MapType>
	[[nodiscard]]
	auto Flatten(const glz::generic_json<NumberMode, MapType>& a_root) -> glz::generic_json<NumberMode, MapType>
	{
		return REX::Glaze::Flatten<NumberMode, MapType>(a_root);
	}
}

#endif
