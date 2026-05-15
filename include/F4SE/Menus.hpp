#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"

#include "REX/Enum.hpp"
#include "REX/EnumSet.hpp"
#include "REX/NotNull.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	enum class UI_DEPTH_PRIORITY : std::int32_t;
	enum class UI_MENU_FLAGS : std::uint32_t;

	class GameMenuBase;
	class IMenu;
	class MenuOpenCloseEvent;
	class UIMessage;
}

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t;
}

namespace F4SE::Menus
{
	// This API should only be used after the game data is ready; it is also thread-safe.

	class MenuInfo
		: public std::enable_shared_from_this<MenuInfo>
	{
	public:
		MenuInfo();

		MenuInfo(
			std::string a_menuName,
			std::filesystem::path a_menuFilePath,
			std::string a_rootVarPath);

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

		virtual ~MenuInfo() noexcept;

		MenuInfo(const MenuInfo&) = default;
		MenuInfo(MenuInfo&&) noexcept = default;

		MenuInfo& operator=(const MenuInfo&) = default;
		MenuInfo& operator=(MenuInfo&&) noexcept = default;

		[[nodiscard]] auto GetMenuName() const noexcept { return std::string_view(_menuName); }
		[[nodiscard]] const auto& GetMenuFilePath() const noexcept { return _menuFilePath; }
		[[nodiscard]] auto GetRootVarPath() const noexcept { return std::string_view(_rootVarPath); }
		[[nodiscard]] auto GetMenuFlags() const noexcept { return _menuFlags.get(); }
		[[nodiscard]] auto GetMenuDepth() const noexcept { return _menuDepth.get(); }
		[[nodiscard]] auto GetMenuInputContext() const noexcept { return _menuInputContext.get(); }

		[[nodiscard]] virtual auto CreateMenuInstance() const
			-> REX::NotNull<std::unique_ptr<RE::GameMenuBase>>;

		virtual void OnMenuLoadSuccess(const REX::NotNull<std::unique_ptr<RE::GameMenuBase>>& a_menuInstance) const;
		virtual void OnMenuLoadFailure(const REX::NotNull<std::unique_ptr<RE::GameMenuBase>>& a_menuInstance) const;

	protected:
		std::string _menuName;
		std::filesystem::path _menuFilePath;
		std::string _rootVarPath;
		REX::EnumSet<RE::UI_MENU_FLAGS, std::uint32_t> _menuFlags;
		REX::Enum<RE::UI_DEPTH_PRIORITY, std::int32_t> _menuDepth;
		REX::Enum<RE::UserEvents::INPUT_CONTEXT_ID, std::int32_t> _menuInputContext;
	};

	class MenuAssetInfo
		: public std::enable_shared_from_this<MenuAssetInfo>
	{
	public:
		MenuAssetInfo();

		MenuAssetInfo(
			std::string a_menuName,
			std::filesystem::path a_assetFilePath,
			std::string a_rootVarPath);

		virtual ~MenuAssetInfo() noexcept;

		MenuAssetInfo(const MenuAssetInfo&) = default;
		MenuAssetInfo(MenuAssetInfo&&) noexcept = default;

		MenuAssetInfo& operator=(const MenuAssetInfo&) = default;
		MenuAssetInfo& operator=(MenuAssetInfo&&) noexcept = default;

		[[nodiscard]] auto GetMenuName() const noexcept { return std::string_view(_menuName); }
		[[nodiscard]] const auto& GetAssetFilePath() const noexcept { return _assetFilePath; }
		[[nodiscard]] auto GetRootVarPath() const noexcept { return std::string_view(_rootVarPath); }

		virtual void OnAssetLoadSuccess(const REX::NotNull<::Scaleform::Ptr<RE::IMenu>>& a_menuInstance) const;
		virtual void OnAssetLoadFailure(const REX::NotNull<::Scaleform::Ptr<RE::IMenu>>& a_menuInstance) const;

	protected:
		std::string _menuName;
		std::filesystem::path _assetFilePath;
		std::string _rootVarPath;
	};

	class MenuAssetLoader final
		: public std::enable_shared_from_this<MenuAssetLoader>,
		  public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		MenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetInfo>>& a_assetInfo);
		~MenuAssetLoader() noexcept override;

		MenuAssetLoader(const MenuAssetLoader&) = delete;
		MenuAssetLoader(MenuAssetLoader&&) = delete;

		MenuAssetLoader& operator=(const MenuAssetLoader&) = delete;
		MenuAssetLoader& operator=(MenuAssetLoader&&) = delete;

		[[nodiscard]] auto GetMenuAssetInfo() const noexcept { return _assetInfo; }

		RE::BSEventNotifyControl ProcessEvent(
			const RE::MenuOpenCloseEvent& a_event,
			RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

		void RegisterEvents();
		void UnregisterEvents();

	protected:
		REX::NotNull<std::shared_ptr<MenuAssetInfo>> _assetInfo;
	};

	[[nodiscard]] bool IsMenuRegistered(std::string_view a_menuName);
	[[nodiscard]] bool IsMenuRegistered(const RE::BSFixedString& a_menuName);

	bool RegisterMenu(const REX::NotNull<std::shared_ptr<MenuInfo>>& a_menuInfo);

	bool UnregisterMenu(std::string_view a_menuName);
	bool UnregisterMenu(const RE::BSFixedString& a_menuName);

	[[nodiscard]] bool IsMenuOpen(std::string_view a_menuName);
	[[nodiscard]] bool IsMenuOpen(const RE::BSFixedString& a_menuName);

	[[nodiscard]] auto GetMenuInstance(std::string_view a_menuName)
		-> ::Scaleform::Ptr<RE::IMenu>;
	[[nodiscard]] auto GetMenuInstance(const RE::BSFixedString& a_menuName)
		-> ::Scaleform::Ptr<RE::IMenu>;

	bool OpenMenuAsync(std::string_view a_menuName);
	bool OpenMenuAsync(const RE::BSFixedString& a_menuName);

	bool CloseMenuAsync(std::string_view a_menuName);
	bool CloseMenuAsync(const RE::BSFixedString& a_menuName);

	bool ForceCloseMenuAsync(std::string_view a_menuName);
	bool ForceCloseMenuAsync(const RE::BSFixedString& a_menuName);

	auto CreateMenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetInfo>>& a_assetInfo)
		-> REX::NotNull<std::shared_ptr<MenuAssetLoader>>;
	void RegisterMenuAssetLoader(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_assetLoader);
}

namespace F4SE::Menus::Impl
{
	class MenuInfoMap final
	{
	public:
		MenuInfoMap() = default;
		~MenuInfoMap() noexcept = default;

		MenuInfoMap(const MenuInfoMap&) = delete;
		MenuInfoMap(MenuInfoMap&&) = delete;

		MenuInfoMap& operator=(const MenuInfoMap&) = delete;
		MenuInfoMap& operator=(MenuInfoMap&&) = delete;

		[[nodiscard]] bool Contains(std::string_view a_menuName);
		[[nodiscard]] bool Contains(const RE::BSFixedString& a_menuName);

		[[nodiscard]] auto GetValue(std::string_view a_menuName) noexcept
			-> std::shared_ptr<MenuInfo>;
		[[nodiscard]] auto GetValue(const RE::BSFixedString& a_menuName) noexcept
			-> std::shared_ptr<MenuInfo>;

		bool Add(const REX::NotNull<std::shared_ptr<MenuInfo>>& a_menu);

		bool Remove(std::string_view a_menuName) noexcept;
		bool Remove(const RE::BSFixedString& a_menuName) noexcept;

		void Clear() noexcept;

	private:
		mutable std::shared_mutex _mapMutex;
		std::unordered_map<RE::BSFixedString, REX::NotNull<std::shared_ptr<MenuInfo>>> _menuMap;
	};

	class MenuAssetLoaderMap final
	{
	public:
		MenuAssetLoaderMap() = default;
		~MenuAssetLoaderMap() noexcept = default;

		MenuAssetLoaderMap(const MenuAssetLoaderMap&) = delete;
		MenuAssetLoaderMap(MenuAssetLoaderMap&&) = delete;

		MenuAssetLoaderMap& operator=(const MenuAssetLoaderMap&) = delete;
		MenuAssetLoaderMap& operator=(MenuAssetLoaderMap&&) = delete;

		void Add(const REX::NotNull<std::shared_ptr<MenuAssetLoader>>& a_loader);

		void Clear() noexcept;

	private:
		mutable std::shared_mutex _mapMutex;
		std::unordered_multimap<RE::BSFixedString, REX::NotNull<std::shared_ptr<MenuAssetLoader>>> _loaderMap;
	};

	[[nodiscard]] auto GetMenuInfoMap()
		-> const REX::NotNull<std::unique_ptr<MenuInfoMap>>&;
	[[nodiscard]] auto GetMenuAssetLoaderMap()
		-> const REX::NotNull<std::unique_ptr<MenuAssetLoaderMap>>&;

	[[nodiscard]] RE::IMenu* CreateMenu(const RE::UIMessage& a_message);
}
