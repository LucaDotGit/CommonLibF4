#pragma once

#include "RE/B/BSEventNotifyControl.hpp"
#include "RE/B/BSTEvent.hpp"
#include "REX/NotNull.hpp"

namespace RE
{
	class MenuOpenCloseEvent;
}

namespace F4SE::Menus
{
	class MenuAssetInfo;

	class MenuAssetLoader final : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		explicit MenuAssetLoader(REX::NotNull<std::shared_ptr<const MenuAssetInfo>> a_assetInfo);
		~MenuAssetLoader() noexcept override;

		MenuAssetLoader(const MenuAssetLoader&) = delete;
		MenuAssetLoader(MenuAssetLoader&&) = delete;

		auto operator=(const MenuAssetLoader&) -> MenuAssetLoader& = delete;
		auto operator=(MenuAssetLoader&&) -> MenuAssetLoader& = delete;

		[[nodiscard]]
		auto GetMenuAssetInfo() const noexcept
		{
			return _assetInfo;
		}

		auto ProcessEvent(
			const RE::MenuOpenCloseEvent& a_event,
			RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl override;

		auto RegisterLoader() -> bool;
		auto UnregisterLoader() -> bool;

	private:
		REX::NotNull<std::shared_ptr<const MenuAssetInfo>> _assetInfo;
	};
}
