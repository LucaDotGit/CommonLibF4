#include "RE/T/TESActorBaseData.hpp"

namespace RE
{
	static constexpr auto TEMPLATE_SIZE = static_cast<std::uint32_t>(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG::_Count);

	auto TESActorBaseData::GetTemplates() noexcept -> std::span<TESForm*>
	{
		if (!templateForms.data()) {
			return {};
		}

		return {templateForms.data(), TEMPLATE_SIZE};
	}

	auto TESActorBaseData::GetTemplates() const noexcept -> std::span<TESForm* const>
	{
		if (!templateForms.data()) {
			return {};
		}

		return {templateForms.data(), TEMPLATE_SIZE};
	}

	void TESActorBaseData::SetTemplates(std::span<TESForm*> a_templates)
	{
		if (a_templates.empty()) {
			templateForms.deallocate_bytes();
			return;
		}

		if (!templateForms.data()) {
			templateForms.allocate_bytes(TEMPLATE_SIZE);
		}

		for (auto i = static_cast<std::uint32_t>(0); i < TEMPLATE_SIZE; i++) {
			if (i < a_templates.size()) {
				templateForms[i] = a_templates[i];
			}
		}
	}

	auto TESActorBaseData::GetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag) const -> TESForm*
	{
		if (!templateForms.data()) {
			return nullptr;
		}

		const auto index = ACTOR_BASE_DATA::GetTemplateUseFlagIndex(a_flag);
		if (!index.has_value()) {
			return nullptr;
		}

		return templateForms[index.value()];
	}

	void TESActorBaseData::SetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag, TESForm* a_template)
	{
		const auto index = ACTOR_BASE_DATA::GetTemplateUseFlagIndex(a_flag);
		if (!index.has_value()) {
			return;
		}

		actorData.templateUseFlags.set(a_flag);

		if (!templateForms.data()) {
			templateForms.allocate_bytes(TEMPLATE_SIZE);
		}

		templateForms[index.value()] = a_template;
	}
}
