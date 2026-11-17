#include "F4SE/Menus/Menus.hpp"

#include "F4SE/Api.hpp"
#include "F4SE/Menus/IMenuAssetLoaderMap.hpp"
#include "F4SE/Menus/IMenuInfoMap.hpp"
#include "F4SE/Menus/MenuAssetInfo.hpp"
#include "F4SE/Menus/MenuAssetLoader.hpp"
#include "F4SE/Menus/MenuInfo.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScaleformManager.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/H/HUDColorTypes.hpp"
#include "RE/I/IMenu.hpp"
#include "RE/U/UI.hpp"
#include "RE/U/UIMessageQueue.hpp"
#include "RE/U/UI_MESSAGE_TYPE.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace F4SE::Menus::Impl
{
	namespace
	{
		[[nodiscard]]
		auto CreateMenu(const RE::UIMessage& a_message) -> RE::IMenu*
		{
			const auto& menuName = a_message.menuName;

			const auto* scaleformManager = RE::BSScaleformManager::GetSingleton();
			if (!scaleformManager) [[unlikely]] {
				REX::Fail("Failed to get the game's Scaleform manager."sv);
			}

			const auto menuInfo = F4SE::GetMenuInfoMap()->GetValue(menuName);
			if (!menuInfo) [[unlikely]] {
				REX::Fail(R"(Failed to find menu info for name "{}".)"sv, menuName);
			}

			auto menuInstance = menuInfo->CreateMenuInstance();

			menuInstance->menuName = menuName;
			menuInstance->menuFlags = menuInfo->GetMenuFlags();
			menuInstance->depthPriority = menuInfo->GetMenuDepth();
			menuInstance->inputContext = menuInfo->GetMenuInputContext();

			if (!menuInfo->LoadAssetForMenu(*(menuInstance.get()))) [[unlikely]] {
				ForceCloseMenuAsync(menuName);
				return (*menuInstance).release();
			}

			const auto menuColorType = menuInfo->GetMenuColorType();
			if (menuColorType != RE::HUDColorTypes::CustomColor) {
				menuInstance->SetupHUDShaderFXTargets(menuColorType);
				return (*menuInstance).release();
			}

			const auto menuColor = menuInfo->GetMenuColor();
			menuInstance->SetupCustomShaderFXTargets(menuColor.GetRed(), menuColor.GetGreen(), menuColor.GetBlue());
			return (*menuInstance).release();
		}
	}
}

namespace F4SE::Menus
{
	auto IsMenuRegistered(std::string_view a_menuName) -> bool
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return IsMenuRegistered(menuName);
	}

	auto IsMenuRegistered(const RE::BSFixedString& a_menuName) noexcept -> bool
	{
		const auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return false;
		}

		return ui->IsMenuRegistered(a_menuName);
	}

	auto RegisterMenu(REX::NotNull<std::shared_ptr<MenuInfo>> a_menuInfo) -> bool
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return false;
		}

		const auto menuName = RE::BSFixedString(a_menuInfo->GetMenuName());
		if (!ui->RegisterMenu(menuName, Impl::CreateMenu)) {
			return false;
		}

		return F4SE::GetMenuInfoMap()->Add(std::move(a_menuInfo));
	}

	auto UnregisterMenu(std::string_view a_menuName) -> bool
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return UnregisterMenu(menuName);
	}

	auto UnregisterMenu(const RE::BSFixedString& a_menuName) noexcept -> bool
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return false;
		}

		if (!ui->UnregisterMenu(a_menuName)) {
			return false;
		}

		F4SE::GetMenuInfoMap()->Remove(a_menuName);
		return true;
	}

	auto IsMenuOpen(std::string_view a_menuName) -> bool
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return IsMenuOpen(menuName);
	}

	auto IsMenuOpen(const RE::BSFixedString& a_menuName) noexcept -> bool
	{
		const auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return false;
		}

		return ui->IsMenuOpen(a_menuName).value_or(false);
	}

	auto GetMenuInstance(std::string_view a_menuName) -> Scaleform::Ptr<RE::IMenu>
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return GetMenuInstance(menuName);
	}

	auto GetMenuInstance(const RE::BSFixedString& a_menuName) noexcept -> Scaleform::Ptr<RE::IMenu>
	{
		const auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return nullptr;
		}

		return ui->GetMenu(a_menuName);
	}

	auto OpenMenuAsync(std::string_view a_menuName) -> bool
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return OpenMenuAsync(menuName);
	}

	auto OpenMenuAsync(const RE::BSFixedString& a_menuName) -> bool
	{
		if (!IsMenuRegistered(a_menuName)) {
			return false;
		}

		auto* uiMessageQueue = RE::UIMessageQueue::GetSingleton();
		if (!uiMessageQueue) {
			return false;
		}

		uiMessageQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::Show);
		return true;
	}

	auto CloseMenuAsync(std::string_view a_menuName) -> bool
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return CloseMenuAsync(menuName);
	}

	auto CloseMenuAsync(const RE::BSFixedString& a_menuName) -> bool
	{
		if (!IsMenuRegistered(a_menuName)) {
			return false;
		}

		auto* uiMessageQueue = RE::UIMessageQueue::GetSingleton();
		if (!uiMessageQueue) {
			return false;
		}

		uiMessageQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::Hide);
		return true;
	}

	auto ForceCloseMenuAsync(std::string_view a_menuName) -> bool
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return ForceCloseMenuAsync(menuName);
	}

	auto ForceCloseMenuAsync(const RE::BSFixedString& a_menuName) -> bool
	{
		if (!IsMenuRegistered(a_menuName)) {
			return false;
		}

		auto* uiMessageQueue = RE::UIMessageQueue::GetSingleton();
		if (!uiMessageQueue) {
			return false;
		}

		uiMessageQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::ForceHide);
		return true;
	}

	void RegisterMenuAssetLoader(REX::NotNull<std::shared_ptr<MenuAssetLoader>> a_assetLoader)
	{
		a_assetLoader->RegisterLoader();

		F4SE::GetMenuAssetLoaderMap()->Add(std::move(a_assetLoader));
	}

	void UnregisterMenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_assetLoader) noexcept
	{
		a_assetLoader->UnregisterLoader();

		F4SE::GetMenuAssetLoaderMap()->Remove(a_assetLoader);
	}
}
