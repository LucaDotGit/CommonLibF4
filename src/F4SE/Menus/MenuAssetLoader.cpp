#include "F4SE/Menus/MenuAssetLoader.hpp"

#include "F4SE/Menus/MenuAssetInfo.hpp"
#include "RE/B/BSEventNotifyControl.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/M/MenuOpenCloseEvent.hpp"
#include "RE/U/UI.hpp"
#include "RE/U/UI_MENU_FLAGS.hpp"
#include "REX/Contract.hpp"
#include "REX/Exception.hpp"
#include "REX/NotNull.hpp"

namespace F4SE::Menus
{
	MenuAssetLoader::MenuAssetLoader(REX::NotNull<std::shared_ptr<const MenuAssetInfo>> a_assetInfo) :
		_assetInfo(std::move(a_assetInfo))
	{
	}

	MenuAssetLoader::~MenuAssetLoader() noexcept
	{
		REX::TryOrFail<std::exception>([this]() -> void {
			UnregisterLoader();
		});
	}

	auto MenuAssetLoader::RegisterLoader() -> bool
	{
		auto* eventSource = static_cast<RE::BSTEventSource<RE::MenuOpenCloseEvent>*>(RE::UI::GetSingleton());
		if (!eventSource) {
			return false;
		}

		if (!eventSource->RegisterSink(this)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto menuOpenCloseEvent =
			RE::MenuOpenCloseEvent{.menuName = RE::BSFixedString(_assetInfo->GetMenuName()), .opening = true};

		return ProcessEvent(menuOpenCloseEvent, eventSource) != RE::BSEventNotifyControl::Stop;
	}

	auto MenuAssetLoader::UnregisterLoader() -> bool
	{
		auto* eventSource = static_cast<RE::BSTEventSource<RE::MenuOpenCloseEvent>*>(RE::UI::GetSingleton());
		if (!eventSource) {
			return false;
		}

		return eventSource->UnregisterSink(this);
	}

	auto MenuAssetLoader::ProcessEvent(
		const RE::MenuOpenCloseEvent& a_event,
		RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl
	{
		if (!a_event.opening) {
			return RE::BSEventNotifyControl::Continue;
		}

		const auto& menuName = a_event.menuName;
		if (menuName != _assetInfo->GetMenuName()) {
			return RE::BSEventNotifyControl::Continue;
		}

		const auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return RE::BSEventNotifyControl::Continue;
		}

		const auto menuInstance = ui->GetMenu(menuName);
		if (!menuInstance) {
			return RE::BSEventNotifyControl::Continue;
		}

		if (_assetInfo->LoadAssetForMenu(*menuInstance)) {
			return RE::BSEventNotifyControl::Continue;
		}

		if (menuInstance->menuFlags.any(RE::UI_MENU_FLAGS::AlwaysOpen)) {
			a_eventSource->UnregisterSink(this);
		}

		return RE::BSEventNotifyControl::Continue;
	}
}
