#include "RE/B/BSGFxShaderFXTarget.hpp"

namespace RE
{
	BSGFxShaderFXTarget::BSGFxShaderFXTarget(const ::Scaleform::GFx::Value& a_flashObject)
		: BSGFxDisplayObject(a_flashObject)
	{
		ctor_shared();
	}

	BSGFxShaderFXTarget::BSGFxShaderFXTarget(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember)
		: BSGFxDisplayObject(a_flashObject, a_relativePathToMember)
	{
		ctor_shared();
	}

	BSGFxShaderFXTarget::BSGFxShaderFXTarget(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject)
		: BSGFxDisplayObject(a_parentMovie, a_pathToObject)
	{
		ctor_shared();
	}

	BSGFxShaderFXTarget::~BSGFxShaderFXTarget()
	{
		auto* eventSource = ApplyColorUpdateEvent::GetEventSource();
		if (eventSource) {
			eventSource->UnregisterSink(this);
		}
	}

	BSEventNotifyControl BSGFxShaderFXTarget::ProcessEvent(const ApplyColorUpdateEvent& a_event, BSTEventSource<ApplyColorUpdateEvent>* a_eventSource)
	{
		using FuncType = decltype(&BSGFxShaderFXTarget::ProcessEvent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxShaderFXTarget::ProcessEvent };
		return std::invoke(FUNC, this, a_event, a_eventSource);
	}

	void BSGFxShaderFXTarget::AppendShaderFXInfos(BSTArray<UIShaderFXInfo>& a_colorFXInfo, BSTArray<UIShaderFXInfo>& a_backgroundFXInfo)
	{
		using FuncType = decltype(&BSGFxShaderFXTarget::AppendShaderFXInfos);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxShaderFXTarget::AppendShaderFXInfos };
		FUNC(this, a_colorFXInfo, a_backgroundFXInfo);
	}

	void BSGFxShaderFXTarget::CreateAndSetFiltersToColor(const NiColor& a_color, REX::Float32 a_brightness)
	{
		using FuncType = void (BSGFxShaderFXTarget::*)(const NiColor&, REX::Float32);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxShaderFXTarget::CreateAndSetFiltersToColor01 };
		FUNC(this, a_color, a_brightness);
	}

	void BSGFxShaderFXTarget::CreateAndSetFiltersToColor(std::uint8_t a_r, std::uint8_t a_g, std::uint8_t a_b, REX::Float32 a_brightness)
	{
		using FuncType = void (BSGFxShaderFXTarget::*)(std::uint8_t, std::uint8_t, std::uint8_t, REX::Float32);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxShaderFXTarget::CreateAndSetFiltersToColor02 };
		FUNC(this, a_r, a_g, a_b, a_brightness);
	}

	void BSGFxShaderFXTarget::CreateAndSetFiltersToHUD(HUDColorTypes a_colorType, REX::Float32 a_scale)
	{
		using FuncType = decltype(&BSGFxShaderFXTarget::CreateAndSetFiltersToHUD);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxShaderFXTarget::CreateAndSetFiltersToHUD };
		FUNC(this, a_colorType, a_scale);
	}

	void BSGFxShaderFXTarget::EnableShadedBackground(HUDColorTypes a_colorType, REX::Float32 a_scale)
	{
		using FuncType = decltype(&BSGFxShaderFXTarget::EnableShadedBackground);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxShaderFXTarget::EnableShadedBackground };
		FUNC(this, a_colorType, a_scale);
	}

	void BSGFxShaderFXTarget::SetToHUDColor(bool a_useWarningColor)
	{
		auto colorType = a_useWarningColor ? HUDColorTypes::kWarningColor : HUDColorTypes::kGameplayHUDColor;
		CreateAndSetFiltersToHUD(colorType, 1.0_f32);
	}

	void BSGFxShaderFXTarget::ctor_shared()
	{
		REL::EmplaceVtable(this);

		auto useShadedBackground = ::Scaleform::GFx::Value();
		if (GetMember(USE_SHADED_BACKGROUND_VAR_NAME.data(), std::addressof(useShadedBackground)) && useShadedBackground.IsBoolean() && useShadedBackground.GetBoolean()) {
			EnableShadedBackground(HUDColorTypes::kMenuNoColorBackground);
		}

		auto* eventSource = ApplyColorUpdateEvent::GetEventSource();
		if (eventSource) {
			eventSource->RegisterSink(this);
		}
	}
}
