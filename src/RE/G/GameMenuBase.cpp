#include "RE/G/GameMenuBase.hpp"

#include "RE/F/FlatScreenModel.hpp"

namespace RE
{
	GameMenuBase::GameMenuBase()
	{
		REL::EmplaceVtable(this);

		auto* flatScreenModel = FlatScreenModel::GetSingleton();
		if (!flatScreenModel) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		customRendererName = flatScreenModel->customRendererName;
	}

	GameMenuBase::~GameMenuBase() = default;

	void GameMenuBase::SetIsTopButtonBar(bool a_isTopButtonBar)
	{
		using FuncType = decltype(&GameMenuBase::SetIsTopButtonBar);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::SetIsTopButtonBar };
		FUNC(this, a_isTopButtonBar);
	}

	void GameMenuBase::OnMenuDisplayStateChanged()
	{
		using FuncType = decltype(&GameMenuBase::OnMenuDisplayStateChanged);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::OnMenuDisplayStateChanged };
		FUNC(this);
	}

	void GameMenuBase::OnAddedToMenuStack()
	{
		IMenu::OnAddedToMenuStack();
		if (menuHUDMode) {
			SendHUDMessage::PushHUDMode(*menuHUDMode);
		}
	}

	void GameMenuBase::OnRemovedFromMenuStack()
	{
		IMenu::OnRemovedFromMenuStack();
		if (menuHUDMode) {
			SendHUDMessage::PopHUDMode(*menuHUDMode);
		}
	}

	bool GameMenuBase::CacheShaderFXQuadsForRenderer_Impl()
	{
		using FuncType = decltype(&GameMenuBase::CacheShaderFXQuadsForRenderer_Impl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::CacheShaderFXQuadsForRenderer_Impl };
		return std::invoke(FUNC, this);
	}

	void GameMenuBase::TransferCachedShaderFXQuadsForRenderer(const BSFixedString& a_rendererName)
	{
		using FuncType = decltype(&GameMenuBase::TransferCachedShaderFXQuadsForRenderer);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::TransferCachedShaderFXQuadsForRenderer };
		FUNC(this, a_rendererName);
	}

	void GameMenuBase::SetViewportRect(const NiRect<REX::Float32>& a_viewportRect)
	{
		using FuncType = decltype(&GameMenuBase::SetViewportRect);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::SetViewportRect };
		FUNC(this, a_viewportRect);
	}

	void GameMenuBase::AppendShaderFXInfos(BSTAlignedArray<UIShaderFXInfo>& a_colorFXInfos, BSTAlignedArray<UIShaderFXInfo>& a_backgroundFXInfos) const
	{
		using FuncType = decltype(&GameMenuBase::AppendShaderFXInfos);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::AppendShaderFXInfos };
		FUNC(this, a_colorFXInfos, a_backgroundFXInfos);
	}

	void GameMenuBase::SetUpButtonBar(BSGFxShaderFXTarget& a_parentObject, const char* a_buttonBarPath, HUDColorTypes a_colorType)
	{
		using FuncType = decltype(&GameMenuBase::SetUpButtonBar);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameMenuBase::SetUpButtonBar };
		FUNC(this, a_parentObject, a_buttonBarPath, a_colorType);
	}

	void GameMenuBase::SetupHUDShaderFXTargets(HUDColorTypes a_colorType, REX::Float32 a_scale)
	{
		if (filterHolder || !menuObj.IsAnyObject()) {
			return;
		}

		filterHolder = msvc::make_unique<BSGFxShaderFXTarget>(menuObj);
		if (!filterHolder) [[unlikely]] {
			REX::AllocationFail();
		}

		filterHolder->CreateAndSetFiltersToHUD(a_colorType, a_scale);

		if (menuFlags.any(UI_MENU_FLAGS::kCustomRendering)) {
			shaderFXObjects.push_back(filterHolder.get());
		}
	}
}
