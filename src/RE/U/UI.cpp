#include "RE/U/UI.hpp"

#include "RE/B/BSReadWriteLock.hpp"
#include "RE/U/UI_MENU_FLAGS.hpp"

namespace RE
{
	auto UI::GetSingleton() noexcept -> UI*
	{
		static const auto SINGLETON = REL::Relocation<UI**>(ID::UI::Singleton);
		return *SINGLETON;
	}

	auto UI::GetMenuStackLock() noexcept -> BSReadWriteLock&
	{
		static const auto MENU_STACK_RW_LOCK = REL::Relocation<BSReadWriteLock*>(ID::UI::MenuStackLock);
		return *MENU_STACK_RW_LOCK;
	}

	auto UI::GetMenuMapLock() noexcept -> BSReadWriteLock&
	{
		static const auto MENU_MAP_RW_LOCK = REL::Relocation<BSReadWriteLock*>(ID::UI::MenuMapLock);
		return *MENU_MAP_RW_LOCK;
	}

	auto UI::GetGFxStateChangeLock() noexcept -> BSSpinLock&
	{
		static const auto GFx_STATE_CHANGE_LOCK = REL::Relocation<BSSpinLock*>(ID::UI::GFxStateChangeLock);
		return *GFx_STATE_CHANGE_LOCK;
	}

	auto UI::GetRuntimeData() noexcept -> UI::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::UI::RuntimeData, this);
	}

	auto UI::GetRuntimeData() const noexcept -> const UI::RuntimeData&
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::UI::RuntimeData, this);
	}

	auto UI::CustomRendererHasQuads(const BSFixedString& a_customRendererName) const -> bool
	{
		using FuncType = decltype(&UI::CustomRendererHasQuads);
		static const auto FUNC = REL::Relocation<FuncType>(ID::UI::CustomRendererHasQuads);
		return std::invoke(FUNC, this, a_customRendererName);
	}

	auto UI::GetMenu(const BSFixedString& a_menuName) const noexcept -> Scaleform::Ptr<IMenu>
	{
		const auto menuLock = BSAutoReadLock(GetMenuMapLock());

		const auto menuIt = menuMap.find(a_menuName);
		if (menuIt == menuMap.end()) {
			return nullptr;
		}

		return menuIt->second.menu;
	}

	auto UI::IsMenuOpen(const Scaleform::Ptr<IMenu>& a_menu) noexcept -> std::optional<bool>
	{
		if (!a_menu) {
			return std::nullopt;
		}

		return a_menu->menuFlags.any(UI_MENU_FLAGS::OnStack);
	}

	auto UI::IsMenuOpen(const BSFixedString& a_menuName) const noexcept -> std::optional<bool>
	{
		const auto menu = GetMenu(a_menuName);
		return IsMenuOpen(menu);
	}

	auto UI::IsMenuRegistered(const BSFixedString& a_menuName) const noexcept -> bool
	{
		const auto menuLock = BSAutoReadLock(GetMenuMapLock());
		return menuMap.contains(a_menuName);
	}

	void UI::RefreshCursor()
	{
		using FuncType = decltype(&UI::RefreshCursor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::UI::RefreshCursor);
		std::invoke(FUNC, this);
	}

	auto UI::RegisterMenu(const BSFixedString& a_menuName, CreateType* a_create, StaticUpdateType* a_staticUpdate)
		-> bool
	{
		if (!a_create) {
			return false;
		}

		const auto menuLock = BSAutoWriteLock(GetMenuMapLock());

		const auto&& [menuIt, hasInserted] = menuMap.try_emplace(a_menuName);
		if (!hasInserted) {
			return false;
		}

		auto& menuEntry = menuIt->second;
		menuEntry.create = a_create;
		menuEntry.staticUpdate = a_staticUpdate;
		return true;
	}

	auto UI::UnregisterMenu(const BSFixedString& a_menuName) noexcept -> bool
	{
		const auto menuLock = BSAutoWriteLock(GetMenuMapLock());

		const auto menuIt = menuMap.find(a_menuName);
		if (menuIt == menuMap.end()) {
			return false;
		}

		menuMap.erase(menuIt);
		return true;
	}

	void UI::UpdateControllerType()
	{
		using FuncType = decltype(&UI::UpdateControllerType);
		static const auto FUNC = REL::Relocation<FuncType>(ID::UI::UpdateControllerType);
		std::invoke(FUNC, this);
	}
}
