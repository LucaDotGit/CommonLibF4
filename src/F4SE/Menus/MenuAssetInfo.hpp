#pragma once

#include "F4SE/Menus/ILoadableMenuAsset.hpp"

namespace RE
{
	class IMenu;
}

namespace F4SE::Menus
{
	class MenuAssetInfo : public ILoadableMenuAsset
	{
	public:
		MenuAssetInfo(std::string a_menuName, std::filesystem::path a_assetFilePath, std::string a_rootVarPath);
		~MenuAssetInfo() noexcept override;

		MenuAssetInfo(const MenuAssetInfo&) = default;
		MenuAssetInfo(MenuAssetInfo&&) noexcept = default;

		auto operator=(const MenuAssetInfo&) -> MenuAssetInfo& = default;
		auto operator=(MenuAssetInfo&&) noexcept -> MenuAssetInfo& = default;

		[[nodiscard]]
		auto GetMenuName() const noexcept
		{
			return std::string_view(_menuName);
		}

		[[nodiscard]]
		auto GetAssetFilePath() const noexcept -> const auto&
		{
			return _assetFilePath;
		}

		[[nodiscard]]
		auto GetRootVarPath() const noexcept
		{
			return std::string_view(_rootVarPath);
		}

		auto LoadAssetForMenu(RE::IMenu& a_menu) const -> bool override;

	protected:
		std::string _menuName;
		std::filesystem::path _assetFilePath;
		std::string _rootVarPath;
	};
}
