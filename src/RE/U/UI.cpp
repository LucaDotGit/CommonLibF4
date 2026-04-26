#include "RE/U/UI.hpp"

namespace RE
{
	UI* UI::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<UI**>{ ID::UI::Singleton };
		return *SINGLETON;
	}

	BSReadWriteLock& UI::GetMenuMapRWLock()
	{
		static const auto MENU_MAP_RW_LOCK = REL::Relocation<BSReadWriteLock*>{ ID::UI::MenuMapRWLock };
		return *MENU_MAP_RW_LOCK;
	}

	UI::RuntimeData& UI::GetRuntimeData() noexcept
	{
		return REL::GetMemberAt<RuntimeData>(Offset::UI::RuntimeData, this);
	}

	const UI::RuntimeData& UI::GetRuntimeData() const noexcept
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::UI::RuntimeData, this);
	}

	bool UI::CustomRendererHasQuads(const BSFixedString& a_customRendererName) const
	{
		using FuncType = decltype(&UI::CustomRendererHasQuads);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UI::CustomRendererHasQuads };
		return std::invoke(FUNC, this, a_customRendererName);
	}

	::Scaleform::Ptr<IMenu> UI::GetMenu(const BSFixedString& a_menuName) const
	{
		const auto menuLock = BSAutoReadLock(GetMenuMapRWLock());
		const auto menuIt = menuMap.find(a_menuName);
		return menuIt != menuMap.end() ? menuIt->second.menu : nullptr;
	}

	auto UI::IsMenuOpen(const ::Scaleform::Ptr<IMenu>& a_menu) -> std::optional<bool>
	{
		if (!a_menu) {
			return std::nullopt;
		}

		return a_menu->menuFlags.any(UI_MENU_FLAGS::kOnStack);
	}

	auto UI::IsMenuOpen(const BSFixedString& a_menuName) const -> std::optional<bool>
	{
		const auto menu = GetMenu(a_menuName);
		return IsMenuOpen(menu);
	}

	bool UI::IsMenuRegistered(const BSFixedString& a_menuName) const
	{
		const auto menuLock = BSAutoReadLock(GetMenuMapRWLock());
		return menuMap.contains(a_menuName);
	}

	void UI::RefreshCursor()
	{
		using FuncType = decltype(&UI::RefreshCursor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UI::RefreshCursor };
		FUNC(this);
	}

	bool UI::RegisterMenu(const BSFixedString& a_menuName, CreateType* a_create, StaticUpdateType* a_staticUpdate)
	{
		if (!a_create) {
			return false;
		}

		const auto menuLock = BSAutoWriteLock(GetMenuMapRWLock());

		const auto&& [menuIt, hasInserted] = menuMap.try_emplace(a_menuName);
		if (!hasInserted) {
			return false;
		}

		auto& menuEntry = menuIt->second;
		menuEntry.create = a_create;
		menuEntry.staticUpdate = a_staticUpdate;
		return true;
	}

	bool UI::UnregisterMenu(const BSFixedString& a_menuName)
	{
		const auto menuLock = BSAutoWriteLock(GetMenuMapRWLock());

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
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UI::UpdateControllerType };
		FUNC(this);
	}
}
