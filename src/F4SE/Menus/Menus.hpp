#pragma once

#include "RE/B/BSFixedString.hpp"
#include "REX/NotNull.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	class IMenu;
}

namespace F4SE::Menus
{
	class MenuAssetLoader;
	class MenuInfo;

	[[nodiscard]]
	auto IsMenuRegistered(std::string_view a_menuName) -> bool;
	[[nodiscard]]
	auto IsMenuRegistered(const RE::BSFixedString& a_menuName) noexcept -> bool;

	auto RegisterMenu(REX::NotNull<std::shared_ptr<MenuInfo>> a_menuInfo) -> bool;

	auto UnregisterMenu(std::string_view a_menuName) -> bool;
	auto UnregisterMenu(const RE::BSFixedString& a_menuName) noexcept -> bool;

	[[nodiscard]]
	auto IsMenuOpen(std::string_view a_menuName) -> bool;
	[[nodiscard]]
	auto IsMenuOpen(const RE::BSFixedString& a_menuName) noexcept -> bool;

	[[nodiscard]]
	auto GetMenuInstance(std::string_view a_menuName) -> Scaleform::Ptr<RE::IMenu>;
	[[nodiscard]]
	auto GetMenuInstance(const RE::BSFixedString& a_menuName) noexcept -> Scaleform::Ptr<RE::IMenu>;

	auto OpenMenuAsync(std::string_view a_menuName) -> bool;
	auto OpenMenuAsync(const RE::BSFixedString& a_menuName) -> bool;

	auto CloseMenuAsync(std::string_view a_menuName) -> bool;
	auto CloseMenuAsync(const RE::BSFixedString& a_menuName) -> bool;

	auto ForceCloseMenuAsync(std::string_view a_menuName) -> bool;
	auto ForceCloseMenuAsync(const RE::BSFixedString& a_menuName) -> bool;

	void RegisterMenuAssetLoader(REX::NotNull<std::shared_ptr<MenuAssetLoader>> a_assetLoader);
	void UnregisterMenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_assetLoader) noexcept;
}
