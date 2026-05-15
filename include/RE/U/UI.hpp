#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTimer.hpp"
#include "RE/I/IMenu.hpp"
#include "RE/U/UIMenuEntry.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace RE::Impl
{
	template <class T>
	concept UIMenuConstraint =
		std::derived_from<T, IMenu> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::MENU_NAME)>, std::string_view>;
}

namespace RE
{
	class IMenu;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class MenuModeCounterChangedEvent;
	class TutorialEvent;

	class __declspec(novtable) UI
		: public BSInputEventReceiver,						  // 000
		  public BSTSingletonSDM<UI>,						  // 010
		  public BSTEventSource<MenuOpenCloseEvent>,		  // 018
		  public BSTEventSource<MenuModeChangeEvent>,		  // 070
		  public BSTEventSource<MenuModeCounterChangedEvent>, // 0C8
		  public BSTEventSource<TutorialEvent>				  // 120
	{
	public:
		inline static constexpr auto RTTI{ RTTI::UI };
		inline static constexpr auto VTABLE{ VTABLE::UI };

		// Be sure to never return a `nullptr` menu,
		// otherwise the game will crash when trying to update the menu stack.
		using CreateType = UIMenuEntry::CreateType;
		using StaticUpdateType = UIMenuEntry::StaticUpdateType;

#define RUNTIME_DATA_CONTENT                   \
	bool menuSystemVisible;			 /* 258 */ \
	bool closingAllMenus;			 /* 259 */ \
	bool freezeFrameScreenshotReady; /* 25A */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT;
		};

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 00

		// add
		virtual ~UI(); // 01

		[[nodiscard]] static UI* GetSingleton();

		[[nodiscard]] static BSReadWriteLock& GetMenuMapRWLock();

		[[nodiscard]] RuntimeData& GetRuntimeData() noexcept;
		[[nodiscard]] const RuntimeData& GetRuntimeData() const noexcept;

		[[nodiscard]] bool CustomRendererHasQuads(const BSFixedString& a_customRendererName) const;
		[[nodiscard]] ::Scaleform::Ptr<IMenu> GetMenu(const BSFixedString& a_menuName) const;
		[[nodiscard]] static auto IsMenuOpen(const ::Scaleform::Ptr<IMenu>& a_menu)
			-> std::optional<bool>;
		[[nodiscard]] auto IsMenuOpen(const BSFixedString& a_menuName) const
			-> std::optional<bool>;
		[[nodiscard]] bool IsMenuRegistered(const BSFixedString& a_menuName) const;
		void RefreshCursor();
		bool RegisterMenu(const BSFixedString& a_menuName, CreateType* a_create, StaticUpdateType* a_staticUpdate = nullptr);
		bool UnregisterMenu(const BSFixedString& a_menuName);
		void UpdateControllerType();

		template <Impl::UIMenuConstraint T>
		[[nodiscard]] ::Scaleform::Ptr<T> GetMenu() const
		{
			const auto menu = GetMenu(BSFixedString(T::MENU_NAME));
			return ::Scaleform::Ptr{ static_cast<T*>(menu.get()) };
		}

		template <Impl::UIMenuConstraint T>
		[[nodiscard]] auto IsMenuOpen() const
			-> std::optional<bool>
		{
			return IsMenuOpen(BSFixedString(T::MENU_NAME));
		}

		// members
		BSTArray<BSFixedString> releasedMovies;			  // 178
		BSTArray<::Scaleform::Ptr<IMenu>> menuStack;	  // 190
		BSTHashMap<BSFixedString, UIMenuEntry> menuMap;	  // 1A8
		mutable BSSpinLock processMessagesLock;			  // 1D8
		std::uint32_t menuMode;							  // 1E0
		BSTAtomicValue<std::uint32_t> itemMenuMode;		  // 1E4
		BSTAtomicValue<std::uint32_t> pauseMenuDisableCt; // 1E8
		std::uint32_t freezeFrameMenuBG;				  // 1EC
		std::uint32_t freezeFramePause;					  // 1F0
		std::uint32_t savingDisabled;					  // 1F4
		std::uint32_t disablesCompanion;				  // 1F8
		std::uint32_t largeCacheRenderModeCount;		  // 1FC
		std::uint32_t movementToDirectionalCount;		  // 200
		BSTimer timer;									  // 208
#if COMMONLIB_RUNTIME_AE == 0
		RUNTIME_DATA_CONTENT // 248
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0
		RUNTIME_DATA_CONTENT // 258
#endif
	};
#if COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(UI) == 0x250);
	static_assert(offsetof(UI, menuSystemVisible) == 0x248);
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0
	static_assert(sizeof(UI) == 0x260);
	static_assert(offsetof(UI, menuSystemVisible) == 0x258);
#else
	static_assert(sizeof(UI) == 0x228);
#endif
}

#undef RUNTIME_DATA_CONTENT
