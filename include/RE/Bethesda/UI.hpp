#pragma once

#include "RE/Bethesda/Atomic.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSInputEventReceiver.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/BSTimer.hpp"
#include "RE/Bethesda/IMenu.hpp"
#include "RE/Scaleform/GFx/GFx_Player.hpp"

namespace RE
{
	enum class UI_MESSAGE_TYPE;

	class MenuModeChangeEvent;
	class MenuModeCounterChangedEvent;
	class MenuOpenCloseEvent;
	class TutorialEvent;
	class UIMessage;

	struct UIMenuEntry
	{
	public:
		using Create_t = IMenu*(const UIMessage&);
		using StaticUpdate_t = void();

		// members
		Scaleform::Ptr<IMenu> menu;				 // 00
		Create_t* create;						 // 08
		StaticUpdate_t* staticUpdate{ nullptr }; // 10
	};
	static_assert(sizeof(UIMenuEntry) == 0x18);

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

		using Create_t = typename UIMenuEntry::Create_t;
		using StaticUpdate_t = typename UIMenuEntry::StaticUpdate_t;

		// add
		virtual ~UI() = default; // 01

		[[nodiscard]] bool CustomRendererHasQuads(const BSFixedString& a_customRendererName)
		{
			using func_t = decltype(&UI::CustomRendererHasQuads);
			static REL::Relocation<func_t> func{ REL::ID(1401451) };
			return func(this, a_customRendererName);
		}

		template <class T>
		[[nodiscard]] BSTEventSource<T>* GetEventSource()
		{
			return static_cast<BSTEventSource<T>*>(this);
		}

		[[nodiscard]] static BSReadWriteLock& GetMenuMapRWLock()
		{
			static REL::Relocation<BSReadWriteLock*> menuMapRWLock{ REL::RelocationID(578487, 2707105) };
			return *menuMapRWLock;
		}

		[[nodiscard]] static UI* GetSingleton()
		{
			static REL::Relocation<UI**> singleton{ REL::RelocationID(548587, 2689028) };
			return *singleton;
		}

		[[nodiscard]] Scaleform::Ptr<IMenu> GetMenu(std::string_view a_name) const
		{
			auto lock = BSAutoReadLock{ GetMenuMapRWLock() };
			const auto it = menuMap.find(BSFixedString(a_name));
			return it != menuMap.end() ? it->second.menu : nullptr;
		}

		template <class T>
		[[nodiscard]] Scaleform::Ptr<T> GetMenu() const //
			requires(requires { T::MENU_NAME; })
		{
			const auto ptr = GetMenu(T::MENU_NAME);
			return Scaleform::Ptr{ static_cast<T*>(ptr.get()) };
		}

		[[nodiscard]] bool GetMenuOpen(std::string_view a_name) const
		{
			const auto menu = GetMenu(BSFixedString(a_name));
			return menu ? menu->OnStack() : false;
		}

		template <class T>
		[[nodiscard]] bool GetMenuOpen() const //
			requires(requires { T::MENU_NAME; })
		{
			return GetMenuOpen(T::MENU_NAME);
		}

		void RefreshCursor()
		{
			using func_t = decltype(&UI::RefreshCursor);
			static REL::Relocation<func_t> func{ REL::ID(1436639) };
			return func(this);
		}

		void RegisterMenu(const char* a_menu, Create_t* a_create, StaticUpdate_t* a_staticUpdate = nullptr)
		{
			using func_t = decltype(&UI::RegisterMenu);
			static REL::Relocation<func_t> func{ REL::ID(1519575) };
			return func(this, a_menu, a_create, a_staticUpdate);
		}

		template <class T>
		void RegisterSink(BSTEventSink<T>* a_sink)
		{
			GetEventSource<T>()->RegisterSink(a_sink);
		}

		void UpdateControllerType()
		{
			using func_t = decltype(&UI::UpdateControllerType);
			static REL::Relocation<func_t> func{ REL::ID(175796) };
			return func(this);
		}

		template <class T>
		void UnregisterSink(BSTEventSink<T>* a_sink)
		{
			GetEventSource<T>()->UnregisterSink(a_sink);
		}

		// members
		BSTArray<BSFixedString> releasedMovies;			  // 178
		BSTArray<Scaleform::Ptr<IMenu>> menuStack;		  // 190
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
		BSTimer uiTimer;								  // 208
		bool menuSystemVisible;							  // 248
		bool closingAllMenus;							  // 249
		bool freezeFrameScreenshotReady;				  // 24A
	};
	static_assert(sizeof(UI) == 0x250);

	namespace UIUtils
	{
		inline void UpdateGamepadDependentButtonCodes(bool a_usingGamepad)
		{
			using func_t = decltype(&UpdateGamepadDependentButtonCodes);
			static REL::Relocation<func_t> func{ REL::ID(190238) };
			return func(a_usingGamepad);
		}
	}
}
