#include "RE/T/TESObjectMISC.hpp"

namespace RE
{
	auto TESObjectMISC::GetComponents() const noexcept
		-> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>
	{
		if (!componentData) {
			return std::nullopt;
		}

		return { *componentData };
	}

	void TESObjectMISC::SetComponents(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_components)
	{
		if (componentData) {
			delete componentData;
			componentData = nullptr;
		}

		if (a_components.empty()) {
			return;
		}

		componentData = new BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>{ a_components.begin(), a_components.end() };
	}

	auto TESObjectMISC::GetDisplayIndices() noexcept
		-> std::optional<std::span<std::uint8_t>>
	{
		if (!componentData || !displayIndices) {
			return std::nullopt;
		}

		return std::span{ displayIndices.data(), componentData->size() };
	}

	auto TESObjectMISC::GetDisplayIndices() const noexcept
		-> std::optional<std::span<const std::uint8_t>>
	{
		if (!componentData || !displayIndices) {
			return std::nullopt;
		}

		return std::span{ displayIndices.data(), componentData->size() };
	}

	void TESObjectMISC::SetDisplayIndices(std::span<const std::uint8_t> a_indices)
	{
		if (displayIndices) {
			displayIndices.deallocate_bytes();
		}

		if (a_indices.empty()) {
			return;
		}

		displayIndices.allocate_bytes(static_cast<std::uint32_t>(a_indices.size()));
		std::ranges::copy(a_indices, displayIndices.data());
	}
}
