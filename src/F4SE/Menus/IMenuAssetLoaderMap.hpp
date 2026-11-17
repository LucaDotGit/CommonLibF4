#pragma once

#include "RE/B/BSFixedString.hpp"
#include "REX/NotNull.hpp"

namespace F4SE::Menus
{
	class MenuAssetLoader;

	class IMenuAssetLoaderMap : public std::enable_shared_from_this<IMenuAssetLoaderMap>
	{
	public:
		IMenuAssetLoaderMap() = default;
		virtual ~IMenuAssetLoaderMap() noexcept = default;

		IMenuAssetLoaderMap(const IMenuAssetLoaderMap&) = delete;
		IMenuAssetLoaderMap(IMenuAssetLoaderMap&&) = delete;

		auto operator=(const IMenuAssetLoaderMap&) -> IMenuAssetLoaderMap& = delete;
		auto operator=(IMenuAssetLoaderMap&&) -> IMenuAssetLoaderMap& = delete;

		[[nodiscard]]
		virtual auto Contains(const RE::BSFixedString& a_menuName) const noexcept -> bool = 0;
		[[nodiscard]]
		virtual auto Contains(REX::NotNull<std::shared_ptr<MenuAssetLoader>> a_assetLoader) const noexcept -> bool = 0;
		virtual void Add(REX::NotNull<std::shared_ptr<MenuAssetLoader>> a_assetLoader) = 0;
		virtual auto Remove(const RE::BSFixedString& a_menuName) noexcept -> std::size_t = 0;
		virtual auto Remove(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_assetLoader) noexcept -> bool = 0;
		virtual void Clear() noexcept = 0;

		[[nodiscard]]
		auto Contains(std::string_view a_menuName) const -> bool
		{
			const auto menuName = RE::BSFixedString(a_menuName);
			return Contains(menuName);
		}

		auto Remove(std::string_view a_menuName) -> std::size_t
		{
			const auto menuName = RE::BSFixedString(a_menuName);
			return Remove(menuName);
		}
	};
}
