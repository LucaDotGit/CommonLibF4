#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSTAtomicValue.hpp"
#include "RE/N/NiRect.hpp"
#include "RE/S/SWFToCodeFunctionHandler.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	enum class MENU_RENDER_CONTEXT : std::int32_t;
	enum class UI_DEPTH_PRIORITY : std::int32_t;
	enum class UI_MENU_FLAGS : std::uint32_t;
	enum class UI_MESSAGE_RESULTS : std::int32_t;

	class ButtonEvent;
	class UIMessage;
	class IUIMessageData;
}

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t;
}

namespace RE
{
	class /*__declspec(novtable)*/ IMenu :
		public SWFToCodeFunctionHandler, // 0x00
		public BSInputEventUser			 // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMenu;
		inline static constexpr const auto& VTABLE = VTABLE::IMenu;

		// Has to be an instance of `MovieClip`.
		inline static constexpr auto ROOT_VAR_NAME = "root1"sv;

		// `function get BGSCodeObj():Object;`, `function set BGSCodeObj(value:Object):void;`
		inline static constexpr auto CODE_OBJECT_VAR_NAME = "BGSCodeObj"sv;

		// `function get f4se():Object;`, `function set f4se(value:Object):void;`
		inline static constexpr auto F4SE_CODE_OBJECT_VAR_NAME = "f4se"sv;

		// `function onCodeObjCreate();`
		inline static constexpr auto ON_CODE_OBJECT_CREATED_FUNC_NAME = "onCodeObjCreate"sv;

		// `function onCodeObjDestruction();`
		inline static constexpr auto ON_CODE_OBJECT_DESTROYED_FUNC_NAME = "onCodeObjDestruction"sv;

		// `function onApplyColorChange(red:Number, green:Number, blue:Number, multiplier:Number):Array;`
		inline static constexpr auto F4SE_ON_APPLY_COLOR_CHANGE_FUNC_NAME = "onApplyColorChange"sv;

		// `function ProcessUserEvent(eventName:String, isPressed:Boolean):void;`
		inline static constexpr auto PROCESS_USER_EVENT_FUNC_NAME = "ProcessUserEvent"sv;

		// `function SetSafeRect(safeX:Number, safeY:Number):void;`
		inline static constexpr auto SET_SAFE_RECT_FUNC_NAME = "SetSafeRect"sv;

		// `function SetPlatform(platformType:uint, ps3Switch:Boolean):void;`
		inline static constexpr auto SET_PLATFORM_FUNC_NAME = "SetPlatform"sv;

		using DeltaTime = REX::Float32;

		IMenu();

		IMenu(const IMenu&) = delete;
		IMenu(IMenu&&) = delete;

		auto operator=(const IMenu&) -> IMenu& = delete;
		auto operator=(IMenu&&) -> IMenu& = delete;

		~IMenu() override; // 0x00

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		// add
		virtual auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS; // 0x03
		virtual void AdvanceMovie(DeltaTime a_deltaTime, std::time_t a_time);	 // 0x04
		virtual void PreDisplay();												 // 0x05
		virtual void PostDisplay();												 // 0x06
		virtual auto PassesRenderConditionText(MENU_RENDER_CONTEXT a_reason, const BSFixedString& a_customRendererName)
			const -> bool;																			   // 0x07
		virtual void SetIsTopButtonBar([[maybe_unused]] bool a_isTopButtonBar);						   // 0x08
		virtual void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest); // 0x09
		virtual void OnMenuDisplayStateChanged();													   // 0x0A
		virtual void OnAddedToMenuStack();															   // 0x0B
		virtual void OnRemovedFromMenuStack();														   // 0x0C
		virtual auto CanAdvanceMovie(bool a_pauseMenuShowing) -> bool;								   // 0x0D
		virtual auto CanHandleWhenDisabled([[maybe_unused]] const ButtonEvent* a_event) -> bool;	   // 0x0E
		virtual auto OnButtonEventRelease([[maybe_unused]] const BSFixedString& a_eventName) -> bool;  // 0x0F
		virtual auto CacheShaderFXQuadsForRenderer_Impl() -> bool;									   // 0x10
		virtual void TransferCachedShaderFXQuadsForRenderer(
			[[maybe_unused]] const BSFixedString& a_rendererName);					  // 0x11
		virtual void SetViewportRect([[maybe_unused]] const NiRectF& a_viewportRect); // 0x12

		SCALEFORM_HEAP_REDEFINE_NEW(IMenu);

		void DoAdvanceMovie(DeltaTime a_deltaTime);
		[[nodiscard]]
		auto GetNativeCodeObject() const -> Scaleform::GFx::Value;
		[[nodiscard]]
		auto IsMenuDisplayEnabled() const noexcept -> bool;
		void OnSetSafeRect();
		auto ProcessScaleformEvent(Scaleform::GFx::Movie* a_movie, const IUIMessageData* a_data) -> UI_MESSAGE_RESULTS;
		void RefreshPlatform();
		void SetMenuCodeObject(Scaleform::GFx::Movie& a_movie, const char* a_menuObjPath);

		// members
		Scaleform::GFx::Value menuObj;										// 0x20
		Scaleform::Ptr<Scaleform::GFx::Movie> uiMovie;						// 0x40
		BSFixedString customRendererName;									// 0x48
		BSFixedString menuName;												// 0x50
		REX::EnumSet<UI_MENU_FLAGS, std::uint32_t> menuFlags;				// 0x58
		BSTAtomicValue<std::uint32_t> advanceWithoutRenderCount{0};			// 0x5C
		bool passesTopMenuTest{true};										// 0x60
		bool menuCanBeVisible{true};										// 0x61
		bool hasQuadsForCustomRenderer{false};								// 0x62
		bool hasDoneFirstAdvanceMovie{false};								// 0x63
		REX::Enum<UI_DEPTH_PRIORITY, std::uint8_t> depthPriority;			// 0x64
		REX::Enum<UserEvents::INPUT_CONTEXT_ID, std::int32_t> inputContext; // 0x68
	};

	static_assert(sizeof(IMenu) == 0x70);
}
