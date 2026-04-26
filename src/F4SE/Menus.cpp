#include "F4SE/Menus.hpp"

#include "RE/B/BSScaleformManager.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/H/HUDColorTypes.hpp"
#include "RE/I/IMenu.hpp"
#include "RE/M/MenuOpenCloseEvent.hpp"
#include "RE/U/UI.hpp"
#include "RE/U/UIMessageQueue.hpp"
#include "RE/U/UI_MESSAGE_TYPE.hpp"

#include "REX/Contract.hpp"
#include "REX/Log.hpp"
#include "REX/Message.hpp"
#include "REX/Try.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace F4SE::Menus
{
	MenuInfo::MenuInfo() = default;

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath)
		: menuName(std::move(a_menuName)),
		  menuFilePath(std::move(a_menuFilePath)),
		  rootVarPath(std::move(a_rootVarPath))
	{
	}

	MenuInfo::MenuInfo(
		std::string a_menuName,
		std::filesystem::path a_menuFilePath,
		std::string a_rootVarPath,
		REX::EnumSet<RE::UI_MENU_FLAGS, std::uint32_t> a_menuFlags,
		REX::Enum<RE::UI_DEPTH_PRIORITY, std::int32_t> a_menuDepth)
		: menuName(std::move(a_menuName)),
		  menuFilePath(std::move(a_menuFilePath)),
		  rootVarPath(std::move(a_rootVarPath)),
		  menuFlags(a_menuFlags),
		  menuDepth(a_menuDepth)
	{
	}

	MenuInfo::~MenuInfo() noexcept = default;

	auto MenuInfo::CreateMenuInstance() const -> REX::NotNull<std::unique_ptr<RE::GameMenuBase>>
	{
		auto menuImpl = std::make_unique<RE::GameMenuBase>();
		if (!menuImpl) [[unlikely]] {
			REX::AllocationFail();
		}

		return menuImpl;
	}

	void MenuInfo::OnMenuLoadSuccess([[maybe_unused]] const REX::NotNull<std::unique_ptr<RE::GameMenuBase>>& a_menuInstance) const
	{
	}

	void MenuInfo::OnMenuLoadFailure([[maybe_unused]] const REX::NotNull<std::unique_ptr<RE::GameMenuBase>>& a_menuInstance) const
	{
	}

	MenuAssetInfo::MenuAssetInfo() = default;

	MenuAssetInfo::MenuAssetInfo(
		std::string a_menuName,
		std::filesystem::path a_assetFilePath,
		std::string a_rootVarPath)
		: menuName(std::move(a_menuName)),
		  assetFilePath(std::move(a_assetFilePath)),
		  rootVarPath(std::move(a_rootVarPath))
	{
	}

	MenuAssetInfo::~MenuAssetInfo() noexcept = default;

	void MenuAssetInfo::OnAssetLoadSuccess([[maybe_unused]] const REX::NotNull<::Scaleform::Ptr<RE::IMenu>>& a_menuInstance) const
	{
	}

	void MenuAssetInfo::OnAssetLoadFailure([[maybe_unused]] const REX::NotNull<::Scaleform::Ptr<RE::IMenu>>& a_menuInstance) const
	{
	}

	MenuAssetLoader::MenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetInfo>>& a_assetInfo)
		: _assetInfo(a_assetInfo)
	{
	}

	MenuAssetLoader::~MenuAssetLoader() noexcept
	{
		REX::TryOrFail<std::exception>([this]() {
			UnregisterEvents();
		});
	}

	RE::BSEventNotifyControl MenuAssetLoader::ProcessEvent(
		const RE::MenuOpenCloseEvent& a_event,
		RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
	{
		if (!a_event.opening) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto& menuName = a_event.menuName;
		if (menuName != _assetInfo->menuName) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!a_eventSource) [[unlikely]] {
			REX::Assert(false);
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto menuInstance = F4SE::Menus::GetMenuInstance(menuName);
		if (!menuInstance) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto& assetFilePath = _assetInfo->assetFilePath;
		const auto& assetRootVarPath = _assetInfo->rootVarPath;

		if (RE::BSScaleformManager::LoadAsset(*menuInstance, assetFilePath.generic_string().data(), assetRootVarPath.data())) {
			if (menuInstance->menuFlags.any(RE::UI_MENU_FLAGS::kAlwaysOpen)) {
				a_eventSource->UnregisterSink(this);
			}

			_assetInfo->OnAssetLoadSuccess(menuInstance);
			return RE::BSEventNotifyControl::kContinue;
		}

		REX::LogError(R"(Failed to load asset "{}" into menu "{}" and root "{}")"sv,
			assetFilePath.generic_string(), menuName, assetRootVarPath);

		_assetInfo->OnAssetLoadFailure(menuInstance);
		return RE::BSEventNotifyControl::kContinue;
	}

	void MenuAssetLoader::RegisterEvents()
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return;
		}

		auto* eventSource = static_cast<RE::BSTEventSource<RE::MenuOpenCloseEvent>*>(ui);
		if (!eventSource) {
			return;
		}

		eventSource->RegisterSink(this);
	}

	void MenuAssetLoader::UnregisterEvents()
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) {
			return;
		}

		auto* eventSource = static_cast<RE::BSTEventSource<RE::MenuOpenCloseEvent>*>(ui);
		if (!eventSource) {
			return;
		}

		eventSource->UnregisterSink(this);
	}

	bool IsMenuRegistered(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return IsMenuRegistered(menuName);
	}

	bool IsMenuRegistered(const RE::BSFixedString& a_menuName)
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return ui->IsMenuRegistered(a_menuName);
	}

	bool RegisterMenu(const REX::NotNull<std::shared_ptr<MenuInfo>>& a_menuInfo)
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto menuName = RE::BSFixedString(a_menuInfo->menuName);
		if (!ui->RegisterMenu(menuName, Impl::CreateMenu)) {
			return false;
		}

		return Impl::GetMenuInfoMap()->Add(a_menuInfo);
	}

	bool UnregisterMenu(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return UnregisterMenu(menuName);
	}

	bool UnregisterMenu(const RE::BSFixedString& a_menuName)
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		if (!ui->UnregisterMenu(a_menuName)) {
			return false;
		}

		Impl::GetMenuInfoMap()->Remove(a_menuName);
		return true;
	}

	bool IsMenuOpen(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return IsMenuOpen(menuName);
	}

	bool IsMenuOpen(const RE::BSFixedString& a_menuName)
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return ui->IsMenuOpen(a_menuName).value_or(false);
	}

	auto GetMenuInstance(std::string_view a_menuName) -> ::Scaleform::Ptr<RE::IMenu>
	{
		const auto menuName = RE::BSFixedString(a_menuName);

		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return ui->GetMenu(menuName);
	}

	auto GetMenuInstance(const RE::BSFixedString& a_menuName) -> ::Scaleform::Ptr<RE::IMenu>
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return ui->GetMenu(a_menuName);
	}

	bool OpenMenu(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return OpenMenu(menuName);
	}

	bool OpenMenu(const RE::BSFixedString& a_menuName)
	{
		if (IsMenuOpen(a_menuName)) {
			return false;
		}

		auto* uiMessageQueue = RE::UIMessageQueue::GetSingleton();
		if (!uiMessageQueue) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		uiMessageQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kShow);
		return true;
	}

	bool CloseMenu(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return CloseMenu(menuName);
	}

	bool CloseMenu(const RE::BSFixedString& a_menuName)
	{
		if (!IsMenuOpen(a_menuName)) {
			return false;
		}

		auto* uiMessageQueue = RE::UIMessageQueue::GetSingleton();
		if (!uiMessageQueue) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		uiMessageQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kHide);
		return true;
	}

	bool ForceCloseMenu(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return ForceCloseMenu(menuName);
	}

	bool ForceCloseMenu(const RE::BSFixedString& a_menuName)
	{
		auto* ui = RE::UI::GetSingleton();
		if (!ui) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto* uiMessageQueue = RE::UIMessageQueue::GetSingleton();
		if (!uiMessageQueue) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		uiMessageQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kForceHide);
		return true;
	}

	auto CreateMenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetInfo>>& a_assetInfo) -> REX::NotNull<std::shared_ptr<MenuAssetLoader>>
	{
		auto assetLoader = REX::NotNull(std::make_shared<MenuAssetLoader>(a_assetInfo));
		RegisterMenuAssetLoader(assetLoader);
		return assetLoader;
	}

	void RegisterMenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_assetLoader)
	{
		a_assetLoader->RegisterEvents();
		Impl::GetMenuAssetLoaderMap()->Add(a_assetLoader);
	}
}

namespace F4SE::Menus::Impl
{
	bool MenuInfoMap::Contains(std::string_view a_menuName)
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return Contains(menuName);
	}

	bool MenuInfoMap::Contains(const RE::BSFixedString& a_menuName)
	{
		const auto mapLock = std::shared_lock(_mapMutex);
		return _menuMap.contains(a_menuName);
	}

	auto MenuInfoMap::GetValue(std::string_view a_menuName) noexcept -> std::shared_ptr<MenuInfo>
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return GetValue(menuName);
	}

	auto MenuInfoMap::GetValue(const RE::BSFixedString& a_menuName) noexcept -> std::shared_ptr<MenuInfo>
	{
		const auto mapLock = std::shared_lock(_mapMutex);

		const auto menuIt = _menuMap.find(a_menuName);
		if (menuIt == _menuMap.end()) {
			return nullptr;
		}

		return menuIt->second.get();
	}

	bool MenuInfoMap::Add(const REX::NotNull<std::shared_ptr<MenuInfo>>& a_menu)
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		const auto&& [_, inserted] = _menuMap.emplace(a_menu->menuName, a_menu);
		return inserted;
	}

	bool MenuInfoMap::Remove(std::string_view a_menuName) noexcept
	{
		const auto menuName = RE::BSFixedString(a_menuName);
		return Remove(menuName);
	}

	bool MenuInfoMap::Remove(const RE::BSFixedString& a_menuName) noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		const auto menuIt = _menuMap.find(a_menuName);
		if (menuIt == _menuMap.end()) {
			return false;
		}

		_menuMap.erase(menuIt);
		return true;
	}

	void MenuInfoMap::Clear() noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);
		_menuMap.clear();
	}

	void MenuAssetLoaderMap::Add(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_loader)
	{
		const auto mapLock = std::scoped_lock(_mapMutex);
		_loaderMap.emplace(a_loader->GetMenuAssetInfo()->menuName, a_loader);
	}

	auto GetMenuInfoMap() -> const REX::NotNull<std::unique_ptr<MenuInfoMap>>&
	{
		static const auto INSTANCE = REX::NotNull(std::make_unique<MenuInfoMap>());
		return INSTANCE;
	}

	auto GetMenuAssetLoaderMap() -> const REX::NotNull<std::unique_ptr<MenuAssetLoaderMap>>&
	{
		static const auto INSTANCE = REX::NotNull(std::make_unique<MenuAssetLoaderMap>());
		return INSTANCE;
	}

	RE::IMenu* CreateMenu(const RE::UIMessage& a_message)
	{
		const auto& menuName = a_message.menuName;

		auto* scaleformManager = RE::BSScaleformManager::GetSingleton();
		if (!scaleformManager) [[unlikely]] {
			REX::Fail("Failed to get the game's scaleform manager."sv);
		}

		const auto menuInfo = GetMenuInfoMap()->GetValue(menuName);
		if (!menuInfo) [[unlikely]] {
			REX::Fail(R"(Failed to find menu info "{}".)"sv,
				menuName);
		}

		auto menuInstance = menuInfo->CreateMenuInstance();

		menuInstance->menuName = menuName;
		menuInstance->menuFlags = menuInfo->menuFlags;
		menuInstance->depthPriority = menuInfo->menuDepth;

		const auto& menuFilePath = menuInfo->menuFilePath;
		const auto& menuRootVarPath = menuInfo->rootVarPath;

		auto rawMenuFilePath = menuFilePath;
		rawMenuFilePath.replace_extension();

		if (scaleformManager->LoadMovie(*(menuInstance.get()), rawMenuFilePath.generic_string().data(), menuRootVarPath.data())) [[likely]] {
			menuInstance->SetupHUDShaderFXTargets(RE::HUDColorTypes::kGameplayHUDColor);
			menuInfo->OnMenuLoadSuccess(menuInstance);
			return (*menuInstance).release();
		}

		REX::LogError(R"(Failed to load menu "{}" from file path "{}")"sv,
			menuName, menuFilePath.generic_string());

		ForceCloseMenu(menuName);
		menuInfo->OnMenuLoadFailure(menuInstance);
		return (*menuInstance).release();
	}
}
