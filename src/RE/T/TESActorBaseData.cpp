#include "RE/T/TESActorBaseData.hpp"

namespace RE
{
	static constexpr auto TEMPLATE_SIZE = static_cast<std::uint32_t>(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG::kTotal);

	std::span<TESForm*> TESActorBaseData::GetTemplates() noexcept
	{
		if (!templateForms.data()) {
			return {};
		}

		return { templateForms.data(), TEMPLATE_SIZE };
	}

	std::span<TESForm* const> TESActorBaseData::GetTemplates() const noexcept
	{
		if (!templateForms.data()) {
			return {};
		}

		return { templateForms.data(), TEMPLATE_SIZE };
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

		for (auto i = 0ui32; i < TEMPLATE_SIZE; i++) {
			if (i < a_templates.size()) {
				templateForms[i] = a_templates[i];
			}
		}
	}

	TESForm* TESActorBaseData::GetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag) const
	{
		if (!templateForms.data()) {
			return nullptr;
		}

		const auto index = ACTOR_BASE_DATA::GetTemplateUseFlagIndex(a_flag);
		if (!index) {
			return nullptr;
		}

		return templateForms[*index];
	}

	void TESActorBaseData::SetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag, TESForm* a_template)
	{
		const auto index = ACTOR_BASE_DATA::GetTemplateUseFlagIndex(a_flag);
		if (!index) {
			return;
		}

		actorData.templateUseFlags.set(a_flag);

		if (!templateForms.data()) {
			templateForms.allocate_bytes(TEMPLATE_SIZE);
		}

		templateForms[*index] = a_template;
	}
}
