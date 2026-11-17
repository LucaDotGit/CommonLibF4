#pragma once

#include "F4SE/Menus/ILoadableMenuAsset.hpp"
#include "REX/Enum.hpp"
#include "REX/EnumSet.hpp"
#include "REX/NotNull.hpp"

namespace RE
{
	enum class HUDColorTypes : std::int32_t;
	enum class UI_DEPTH_PRIORITY : std::int32_t;
	enum class UI_MENU_FLAGS : std::uint32_t;

	class GameMenuBase;
	class IMenu;
}

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t;
}

namespace REX
{
	class Color;
}

namespace Scaleform::GFx
{
	class Movie;
}

namespace F4SE::Menus
{
	class MenuInfo : public ILoadableMenuAsset
	{
	public:
		MenuInfo(std::string a_menuName, std::filesystem::path a_menuFilePath, std::string a_rootVarPath);

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath,
			RE::UI_MENU_FLAGS a_menuFlags);

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath,
			RE::UI_MENU_FLAGS a_menuFlags,
			RE::UI_DEPTH_PRIORITY a_menuDepth);

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath,
			RE::UI_MENU_FLAGS a_menuFlags,
			RE::UI_DEPTH_PRIORITY a_menuDepth,
			RE::UserEvents::INPUT_CONTEXT_ID a_inputContext);

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath,
			RE::UI_MENU_FLAGS a_menuFlags,
			RE::UI_DEPTH_PRIORITY a_menuDepth,
			RE::UserEvents::INPUT_CONTEXT_ID a_inputContext,
			RE::HUDColorTypes a_menuColorType);

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath,
			RE::UI_MENU_FLAGS a_menuFlags,
			RE::UI_DEPTH_PRIORITY a_menuDepth,
			RE::UserEvents::INPUT_CONTEXT_ID a_inputContext,
			REX::Color a_menuColor);

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath,
			RE::UI_MENU_FLAGS a_menuFlags,
			RE::UI_DEPTH_PRIORITY a_menuDepth,
			RE::UserEvents::INPUT_CONTEXT_ID a_inputContext,
			RE::HUDColorTypes a_menuColorType,
			REX::Color a_menuColor);

		~MenuInfo() noexcept override;

		MenuInfo(const MenuInfo&) = default;
		MenuInfo(MenuInfo&&) noexcept = default;

		auto operator=(const MenuInfo&) -> MenuInfo& = default;
		auto operator=(MenuInfo&&) noexcept -> MenuInfo& = default;

		[[nodiscard]]
		auto GetMenuName() const noexcept
		{
			return std::string_view(_menuName);
		}

		[[nodiscard]]
		auto GetMenuFilePath() const noexcept -> const auto&
		{
			return _menuFilePath;
		}

		[[nodiscard]]
		auto GetRootVarPath() const noexcept
		{
			return std::string_view(_rootVarPath);
		}

		[[nodiscard]]
		auto GetMenuFlags() const noexcept
		{
			return _menuFlags.get();
		}

		[[nodiscard]]
		auto GetMenuDepth() const noexcept
		{
			return _menuDepth.get();
		}

		[[nodiscard]]
		auto GetMenuInputContext() const noexcept
		{
			return _menuInputContext.get();
		}

		[[nodiscard]]
		auto GetMenuColorType() const noexcept
		{
			return _menuColorType.get();
		}

		[[nodiscard]]
		auto GetMenuColor() const noexcept
		{
			return _menuColor;
		}

		auto LoadAssetForMenu(RE::IMenu& a_menu) const -> bool override;

		[[nodiscard]]
		virtual auto CreateMenuInstance() const -> REX::NotNull<std::unique_ptr<RE::GameMenuBase>>;

	protected:
		std::string _menuName;
		std::filesystem::path _menuFilePath;
		std::string _rootVarPath;
		REX::EnumSet<RE::UI_MENU_FLAGS> _menuFlags;
		REX::Enum<RE::UI_DEPTH_PRIORITY> _menuDepth;
		REX::Enum<RE::UserEvents::INPUT_CONTEXT_ID> _menuInputContext;
		REX::Enum<RE::HUDColorTypes> _menuColorType;
		REX::Color _menuColor;
	};
}
