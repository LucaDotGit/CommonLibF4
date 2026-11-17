#include "RE/G/GameMenuBase.hpp"

#include "RE/B/BSGFxShaderFXTarget.hpp"
#include "RE/B/ButtonHintBar.hpp" // IWYU pragma: keep
#include "RE/F/FlatScreenModel.hpp"
#include "RE/H/HUDColorTypes.hpp"
#include "RE/S/SendHUDMessage.hpp"
#include "RE/U/UI_MENU_FLAGS.hpp"

namespace RE
{
	GameMenuBase::GameMenuBase()
	{
		// REL::EmplaceVtable(this);

		const auto* flatScreenModel = FlatScreenModel::GetSingleton();
		if (!flatScreenModel) {
			return;
		}

		customRendererName = flatScreenModel->customRendererName;
	}

	GameMenuBase::~GameMenuBase() = default;

	void GameMenuBase::SetIsTopButtonBar(bool a_isTopButtonBar)
	{
		using FuncType = decltype(&GameMenuBase::SetIsTopButtonBar);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::SetIsTopButtonBar);
		std::invoke(FUNC, this, a_isTopButtonBar);
	}

	void GameMenuBase::OnMenuDisplayStateChanged()
	{
		using FuncType = decltype(&GameMenuBase::OnMenuDisplayStateChanged);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::OnMenuDisplayStateChanged);
		std::invoke(FUNC, this);
	}

	void GameMenuBase::OnAddedToMenuStack()
	{
		IMenu::OnAddedToMenuStack();

		if (menuHUDMode.has_value()) {
			SendHUDMessage::PushHUDMode(*menuHUDMode);
		}
	}

	void GameMenuBase::OnRemovedFromMenuStack()
	{
		IMenu::OnRemovedFromMenuStack();

		if (menuHUDMode.has_value()) {
			SendHUDMessage::PopHUDMode(*menuHUDMode);
		}
	}

	auto GameMenuBase::CacheShaderFXQuadsForRenderer_Impl() -> bool
	{
		using FuncType = decltype(&GameMenuBase::CacheShaderFXQuadsForRenderer_Impl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::CacheShaderFXQuadsForRenderer_Impl);
		return std::invoke(FUNC, this);
	}

	void GameMenuBase::TransferCachedShaderFXQuadsForRenderer(const BSFixedString& a_rendererName)
	{
		using FuncType = decltype(&GameMenuBase::TransferCachedShaderFXQuadsForRenderer);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::TransferCachedShaderFXQuadsForRenderer);
		std::invoke(FUNC, this, a_rendererName);
	}

	void GameMenuBase::SetViewportRect(const NiRectF& a_viewportRect)
	{
		using FuncType = decltype(&GameMenuBase::SetViewportRect);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::SetViewportRect);
		std::invoke(FUNC, this, a_viewportRect);
	}

	void GameMenuBase::AppendShaderFXInfos(
		BSTAlignedArray<UIShaderFXInfo>& a_colorFXInfos,
		BSTAlignedArray<UIShaderFXInfo>& a_backgroundFXInfos) const
	{
		using FuncType = decltype(&GameMenuBase::AppendShaderFXInfos);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::AppendShaderFXInfos);
		std::invoke(FUNC, this, a_colorFXInfos, a_backgroundFXInfos);
	}

	void GameMenuBase::SetUpButtonBar(
		BSGFxShaderFXTarget& a_parentObject,
		const char* a_buttonBarPath,
		HUDColorTypes a_colorType)
	{
		using FuncType = decltype(&GameMenuBase::SetUpButtonBar);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameMenuBase::SetUpButtonBar);
		std::invoke(FUNC, this, a_parentObject, a_buttonBarPath, a_colorType);
	}

	void GameMenuBase::SetupHUDShaderFXTargets(HUDColorTypes a_colorType, REX::Float32 a_scale)
	{
		if (filterHolder || !menuObj.IsAnyObject()) {
			return;
		}

		auto newFilterHolder = msvc::make_unique<BSGFxShaderFXTarget>(menuObj);
		newFilterHolder->CreateAndSetFiltersToHUD(a_colorType, a_scale);

		if (menuFlags.any(UI_MENU_FLAGS::CustomRendering)) {
			shaderFXObjects.push_back(newFilterHolder.get());
		}

		filterHolder = std::move(newFilterHolder);
	}

	void GameMenuBase::SetupCustomShaderFXTargets(const NiColor& a_color, REX::Float32 a_brightness)
	{
		if (filterHolder || !menuObj.IsAnyObject()) {
			return;
		}

		auto newFilterHolder = msvc::make_unique<BSGFxShaderFXTarget>(menuObj);
		newFilterHolder->CreateAndSetFiltersToColor(a_color, a_brightness);

		if (menuFlags.any(UI_MENU_FLAGS::CustomRendering)) {
			shaderFXObjects.push_back(newFilterHolder.get());
		}

		filterHolder = std::move(newFilterHolder);
	}

	void GameMenuBase::SetupCustomShaderFXTargets(
		std::uint8_t a_red,
		std::uint8_t a_green,
		std::uint8_t a_blue,
		REX::Float32 a_brightness)
	{
		if (filterHolder || !menuObj.IsAnyObject()) {
			return;
		}

		auto newFilterHolder = msvc::make_unique<BSGFxShaderFXTarget>(menuObj);
		newFilterHolder->CreateAndSetFiltersToColor(a_red, a_green, a_blue, a_brightness);

		if (menuFlags.any(UI_MENU_FLAGS::CustomRendering)) {
			shaderFXObjects.push_back(newFilterHolder.get());
		}

		filterHolder = std::move(newFilterHolder);
	}
}
