#include "RE/B/BGSPropertySheet.hpp"

namespace RE
{
	auto BGSPropertySheet::GetProperties() const noexcept -> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>
	{
		if (!properties) {
			return std::nullopt;
		}

		return { *properties };
	}

	void BGSPropertySheet::SetProperties(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_properties)
	{
		if (properties) {
			delete properties;
			properties = nullptr;
		}

		if (a_properties.empty()) {
			return;
		}

		properties = new BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>();
		properties->reserve(static_cast<std::uint32_t>(a_properties.size()));
		properties->insert(properties->end(), a_properties.begin(), a_properties.end());
	}
}
