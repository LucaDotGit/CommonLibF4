#pragma once

#include "RE/B/BSFixedString.hpp"
#include "REX/NotNull.hpp"

namespace F4SE::Menus
{
	class MenuInfo;

	class IMenuInfoMap : public std::enable_shared_from_this<IMenuInfoMap>
	{
	public:
		IMenuInfoMap() = default;
		virtual ~IMenuInfoMap() noexcept = default;

		IMenuInfoMap(const IMenuInfoMap&) = delete;
		IMenuInfoMap(IMenuInfoMap&&) = delete;

		auto operator=(const IMenuInfoMap&) -> IMenuInfoMap& = delete;
		auto operator=(IMenuInfoMap&&) -> IMenuInfoMap& = delete;

		[[nodiscard]]
		virtual auto Contains(const RE::BSFixedString& a_menuName) const noexcept -> bool = 0;
		[[nodiscard]]
		virtual auto GetValue(const RE::BSFixedString& a_menuName) const noexcept -> std::shared_ptr<MenuInfo> = 0;
		virtual auto Add(REX::NotNull<std::shared_ptr<MenuInfo>> a_menu) -> bool = 0;
		virtual auto Remove(const RE::BSFixedString& a_menuName) noexcept -> bool = 0;
		virtual void Clear() noexcept = 0;

		[[nodiscard]]
		auto Contains(std::string_view a_menuName) const -> bool
		{
			const auto menuName = RE::BSFixedString(a_menuName);
			return Contains(menuName);
		}

		[[nodiscard]]
		auto GetValue(std::string_view a_menuName) const -> std::shared_ptr<MenuInfo>
		{
			const auto menuName = RE::BSFixedString(a_menuName);
			return GetValue(menuName);
		}

		auto Remove(std::string_view a_menuName) -> bool
		{
			const auto menuName = RE::BSFixedString(a_menuName);
			return Remove(menuName);
		}
	};
}
