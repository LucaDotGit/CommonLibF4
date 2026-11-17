#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventReceiver.hpp"
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
	concept UIMenuConstraint = std::derived_from<T, IMenu> &&
							   !REX::pointer<T> &&
							   !REX::reference<T> &&
							   std::same_as<std::remove_cv_t<decltype(T::MENU_NAME)>, std::string_view>;
}

namespace RE
{
	class BSReadWriteLock;
	class BSSpinLock;
	class IMenu;
	class MenuModeChangeEvent;
	class MenuModeCounterChangedEvent;
	class MenuOpenCloseEvent;
	class TutorialEvent;

	class __declspec(novtable) UI :
		public BSInputEventReceiver,						// 0x000
		public BSTSingletonSDM<UI>,							// 0x010
		public BSTEventSource<MenuOpenCloseEvent>,			// 0x018
		public BSTEventSource<MenuModeChangeEvent>,			// 0x070
		public BSTEventSource<MenuModeCounterChangedEvent>, // 0x0C8
		public BSTEventSource<TutorialEvent>				// 0x120
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::UI;
		inline static constexpr const auto& VTABLE = VTABLE::UI;

		// Be sure to never return a `nullptr` menu,
		// otherwise the game will crash when trying to update the menu stack.
		using CreateType = UIMenuEntry::CreateType;
		using StaticUpdateType = UIMenuEntry::StaticUpdateType;

#define RUNTIME_DATA_CONTENT                  \
	bool menuSystemVisible;			 /* 00 */ \
	bool closingAllMenus;			 /* 01 */ \
	bool freezeFrameScreenshotReady; /* 02 */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT; // 0x00
		};

		static_assert(sizeof(RuntimeData) == 0x03);

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 0x00

		// add
		virtual ~UI(); // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> UI*;

		[[nodiscard]]
		static auto GetMenuStackLock() noexcept -> BSReadWriteLock&;
		[[nodiscard]]
		static auto GetMenuMapLock() noexcept -> BSReadWriteLock&;
		[[nodiscard]]
		static auto GetGFxStateChangeLock() noexcept -> BSSpinLock&;

		[[nodiscard]]
		auto GetRuntimeData() noexcept -> RuntimeData&;
		[[nodiscard]]
		auto GetRuntimeData() const noexcept -> const RuntimeData&;

		[[nodiscard]]
		auto CustomRendererHasQuads(const BSFixedString& a_customRendererName) const -> bool;
		[[nodiscard]]
		auto GetMenu(const BSFixedString& a_menuName) const noexcept -> Scaleform::Ptr<IMenu>;
		[[nodiscard]]
		static auto IsMenuOpen(const Scaleform::Ptr<IMenu>& a_menu) noexcept -> std::optional<bool>;
		[[nodiscard]]
		auto IsMenuOpen(const BSFixedString& a_menuName) const noexcept -> std::optional<bool>;
		[[nodiscard]]
		auto IsMenuRegistered(const BSFixedString& a_menuName) const noexcept -> bool;
		void RefreshCursor();
		auto RegisterMenu(
			const BSFixedString& a_menuName,
			CreateType* a_create,
			StaticUpdateType* a_staticUpdate = nullptr) -> bool;
		auto UnregisterMenu(const BSFixedString& a_menuName) noexcept -> bool;
		void UpdateControllerType();

		template <Impl::UIMenuConstraint T>
		[[nodiscard]]
		auto GetMenu() const -> Scaleform::Ptr<T>
		{
			const auto menu = GetMenu(BSFixedString(T::MENU_NAME));
			return Scaleform::Ptr{static_cast<T*>(menu.get())};
		}

		template <Impl::UIMenuConstraint T>
		[[nodiscard]]
		auto IsMenuOpen() const -> std::optional<bool>
		{
			return IsMenuOpen(BSFixedString(T::MENU_NAME));
		}

		// members
		BSTArray<BSFixedString> releasedMovies;			  // 0x178
		BSTArray<Scaleform::Ptr<IMenu>> menuStack;		  // 0x190
		BSTHashMap<BSFixedString, UIMenuEntry> menuMap;	  // 0x1A8
		mutable BSSpinLock processMessagesLock;			  // 0x1D8
		std::uint32_t menuMode;							  // 0x1E0
		BSTAtomicValue<std::uint32_t> itemMenuMode;		  // 0x1E4
		BSTAtomicValue<std::uint32_t> pauseMenuDisableCt; // 0x1E8
		std::uint32_t freezeFrameMenuBG;				  // 0x1EC
		std::uint32_t freezeFramePause;					  // 0x1F0
		std::uint32_t savingDisabled;					  // 0x1F4
		std::uint32_t disablesCompanion;				  // 0x1F8
		std::uint32_t largeCacheRenderModeCount;		  // 0x1FC
		std::uint32_t movementToDirectionalCount;		  // 0x200
		BSTimer timer;									  // 0x208
#if (COMMONLIB_RUNTIME_AE == 0)
		RUNTIME_DATA_CONTENT; // 0x248
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		RUNTIME_DATA_CONTENT; // 0x258
#endif
	};

#if (COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(UI) == 0x230);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
	static_assert(sizeof(UI) == 0x230);
#else
	static_assert(sizeof(UI) == 0x228);
#endif
}

#undef RUNTIME_DATA_CONTENT
