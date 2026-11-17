#include "F4SE/Menus/MenuInfo.hpp"

#include "RE/B/BSScaleformManager.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/H/HUDColorTypes.hpp"
#include "RE/I/IMenu.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "RE/U/UI_MENU_FLAGS.hpp"
#include "RE/U/UserEvents.hpp"
#include "REX/Contract.hpp"
#include "REX/NotNull.hpp"

namespace F4SE::Menus
{
	MenuInfo::MenuInfo(std::string a_menuName, std::filesystem::path a_menuFilePath, std::string a_rootVarPath) :
		MenuInfo(std::move(a_menuName), std::move(a_menuFilePath), std::move(a_rootVarPath), RE::UI_MENU_FLAGS::None)
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		RE::UI_MENU_FLAGS a_menuFlags) :
		MenuInfo(
			std::move(a_menuName),
			std::move(a_menuFilePath),
			std::move(a_rootVarPath),
			a_menuFlags,
			RE::UI_DEPTH_PRIORITY::Standard)
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		RE::UI_MENU_FLAGS a_menuFlags,
		RE::UI_DEPTH_PRIORITY a_menuDepth) :
		MenuInfo(
			std::move(a_menuName),
			std::move(a_menuFilePath),
			std::move(a_rootVarPath),
			a_menuFlags,
			a_menuDepth,
			RE::UserEvents::INPUT_CONTEXT_ID::None)
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		RE::UI_MENU_FLAGS a_menuFlags,
		RE::UI_DEPTH_PRIORITY a_menuDepth,
		RE::UserEvents::INPUT_CONTEXT_ID a_inputContext) :
		MenuInfo(
			std::move(a_menuName),
			std::move(a_menuFilePath),
			std::move(a_rootVarPath),
			a_menuFlags,
			a_menuDepth,
			a_inputContext,
			RE::HUDColorTypes::GameplayHUDColor)
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		RE::UI_MENU_FLAGS a_menuFlags,
		RE::UI_DEPTH_PRIORITY a_menuDepth,
		RE::UserEvents::INPUT_CONTEXT_ID a_inputContext,
		RE::HUDColorTypes a_menuColorType) :
		MenuInfo(
			std::move(a_menuName),
			std::move(a_menuFilePath),
			std::move(a_rootVarPath),
			a_menuFlags,
			a_menuDepth,
			a_inputContext,
			a_menuColorType,
			REX::Color())
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		RE::UI_MENU_FLAGS a_menuFlags,
		RE::UI_DEPTH_PRIORITY a_menuDepth,
		RE::UserEvents::INPUT_CONTEXT_ID a_inputContext,
		REX::Color a_menuColor) :
		MenuInfo(
			std::move(a_menuName),
			std::move(a_menuFilePath),
			std::move(a_rootVarPath),
			a_menuFlags,
			a_menuDepth,
			a_inputContext,
			RE::HUDColorTypes::CustomColor,
			a_menuColor)
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		RE::UI_MENU_FLAGS a_menuFlags,
		RE::UI_DEPTH_PRIORITY a_menuDepth,
		RE::UserEvents::INPUT_CONTEXT_ID a_inputContext,
		RE::HUDColorTypes a_menuColorType,
		REX::Color a_menuColor) :
		_menuName(std::move(a_menuName)),
		_menuFilePath(std::move(a_menuFilePath)),
		_rootVarPath(std::move(a_rootVarPath)),
		_menuFlags(a_menuFlags),
		_menuDepth(a_menuDepth),
		_menuInputContext(a_inputContext),
		_menuColorType(a_menuColorType),
		_menuColor(a_menuColor)
	{
	}

	MenuInfo::~MenuInfo() noexcept = default;

	auto MenuInfo::LoadAssetForMenu(RE::IMenu& a_menu) const -> bool
	{
		auto* scaleformManager = RE::BSScaleformManager::GetSingleton();
		if (!scaleformManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto rawMenuFilePath = _menuFilePath;
		rawMenuFilePath.replace_extension();

		if (!scaleformManager->LoadMovie(a_menu, rawMenuFilePath.generic_string().data(), _rootVarPath.data())) {
			OnAssetLoadFailure(a_menu.uiMovie);
			return false;
		}

		OnAssetLoadSuccess(a_menu.uiMovie);
		return true;
	}

	auto MenuInfo::CreateMenuInstance() const -> REX::NotNull<std::unique_ptr<RE::GameMenuBase>>
	{
		return std::make_unique<RE::GameMenuBase>();
	}
}
