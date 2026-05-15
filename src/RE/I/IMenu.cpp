#include "RE/I/IMenu.hpp"

#include "RE/B/ButtonEvent.hpp"
#include "RE/I/IUIMessageData.hpp"
#include "RE/P/PauseMenu.hpp"
#include "RE/U/UIMessage.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "RE/U/UI_MENU_FLAGS.hpp"
#include "RE/U/UI_MESSAGE_RESULTS.hpp"
#include "RE/U/UserEvents.hpp"

#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	IMenu::IMenu()
		: menuFlags(UI_MENU_FLAGS::kNone),
		  depthPriority(UI_DEPTH_PRIORITY::kStandard),
		  inputContext(UserEvents::INPUT_CONTEXT_ID::kNone)
	{
		// REL::EmplaceVtable(this);
	}

	IMenu::~IMenu()
	{
		if (!uiMovie) {
			return;
		}

		auto threadId = Scaleform::GetCurrentThreadId();
		uiMovie->SetCaptureThread(threadId);

		auto* heap = uiMovie->GetHeap();
		if (heap) {
			heap->AssignToCurrentThread();
		}
	}

	bool IMenu::ShouldHandleEvent(const InputEvent* a_event)
	{
		using FuncType = decltype(&IMenu::ShouldHandleEvent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::IMenu::ShouldHandleEvent };
		return std::invoke(FUNC, this, a_event);
	}

	void IMenu::OnButtonEvent(const ButtonEvent* a_event)
	{
		if (!a_event || !inputEventHandlingEnabled || !menuObj.IsAnyObject()) {
			return;
		}

		if (!menuObj.HasMember(PROCESS_USER_EVENT_FUNC_NAME.data())) {
			return;
		}

		const auto userEventName =
			a_event->disabled && CanHandleWhenDisabled(a_event) ?
				a_event->QRawUserEvent() :
				a_event->QUserEvent();

		auto args = std::array<::Scaleform::GFx::Value, 2>();
		args[0] = userEventName.data();
		args[1] = a_event->QJustPressed();

		menuObj.Invoke(PROCESS_USER_EVENT_FUNC_NAME.data(), args);
	}

	UI_MESSAGE_RESULTS IMenu::ProcessMessage(UIMessage& a_message)
	{
		switch (a_message.type.get()) {
			case UI_MESSAGE_TYPE::kShow:
			case UI_MESSAGE_TYPE::kHide: {
				return UI_MESSAGE_RESULTS::kHandled;
			}
			case UI_MESSAGE_TYPE::kScaleformEvent: {
				return ProcessScaleformEvent(uiMovie.get(), a_message.QData());
			}
			case UI_MESSAGE_TYPE::kUpdateController: {
				RefreshPlatform();
				return UI_MESSAGE_RESULTS::kPassOn;
			}
			default: {
				return UI_MESSAGE_RESULTS::kPassOn;
			}
		}
	}

	void IMenu::AdvanceMovie(REX::Float32 a_timeDelta, [[maybe_unused]] std::uint64_t a_time)
	{
		if (!uiMovie) {
			return;
		}

		DoAdvanceMovie(a_timeDelta);
		hasDoneFirstAdvanceMovie = true;
	}

	bool IMenu::PassesRenderConditionText(MENU_RENDER_CONTEXT a_reason, const BSFixedString& a_customRendererName) const
	{
		using FuncType = decltype(&IMenu::PassesRenderConditionText);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::IMenu::PassesRenderConditionText };
		return std::invoke(FUNC, this, a_reason, a_customRendererName);
	}

	void IMenu::OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest)
	{
		const bool topMenuTest = a_passesTopMenuTest ||
								 (a_topMenuName == PauseMenu::MENU_NAME &&
									 menuFlags.any(UI_MENU_FLAGS::kAdvancesUnderPauseMenu));
		if (passesTopMenuTest != topMenuTest) {
			passesTopMenuTest = topMenuTest;
			OnMenuDisplayStateChanged();
		}
	}

	void IMenu::OnAddedToMenuStack()
	{
		menuFlags.set(UI_MENU_FLAGS::kOnStack);
		OnMenuDisplayStateChanged();
	}

	void IMenu::OnRemovedFromMenuStack()
	{
		menuFlags.reset(UI_MENU_FLAGS::kOnStack);
		OnMenuDisplayStateChanged();
	}

	bool IMenu::CanAdvanceMovie(bool a_pauseMenuShowing)
	{
		return !a_pauseMenuShowing ||
			   depthPriority > UI_DEPTH_PRIORITY::kGameMessage ||
			   menuFlags.any(UI_MENU_FLAGS::kAdvancesUnderPauseMenu);
	}

	void IMenu::DoAdvanceMovie(REX::Float32 a_timeDelta)
	{
		advanceWithoutRenderCount++;
		uiMovie->Advance(a_timeDelta);
	}

	bool IMenu::IsMenuDisplayEnabled() const noexcept
	{
		return passesTopMenuTest && menuCanBeVisible;
	}

	::Scaleform::GFx::Value IMenu::GetNativeCodeObject() const
	{
		if (!menuObj.IsAnyObject()) {
			return {};
		}

		auto nativeCodeObject = ::Scaleform::GFx::Value();
		if (!menuObj.GetMember(CODE_OBJECT_VAR_NAME.data(), std::addressof(nativeCodeObject)) || !nativeCodeObject.IsObject()) {
			return {};
		}

		return nativeCodeObject;
	}

	void IMenu::OnSetSafeRect()
	{
		using FuncType = decltype(&IMenu::OnSetSafeRect);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::IMenu::OnSetSafeRect };
		std::invoke(FUNC, this);
	}

	UI_MESSAGE_RESULTS IMenu::ProcessScaleformEvent(::Scaleform::GFx::Movie* a_movie, const IUIMessageData* a_data)
	{
		using FuncType = decltype(&IMenu::ProcessScaleformEvent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::IMenu::ProcessScaleformEvent };
		return std::invoke(FUNC, this, a_movie, a_data);
	}

	void IMenu::RefreshPlatform()
	{
		using FuncType = decltype(&IMenu::RefreshPlatform);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::IMenu::RefreshPlatform };
		std::invoke(FUNC, this);
	}

	void IMenu::SetMenuCodeObject(::Scaleform::GFx::Movie& a_movie, const char* a_menuObjPath)
	{
		auto newMenuObject = ::Scaleform::GFx::Value();
		if (!a_movie.GetVariable(std::addressof(newMenuObject), a_menuObjPath) || !newMenuObject.IsAnyObject()) {
			return;
		}

		menuObj = std::move(newMenuObject);
		RegisterCodeObject(a_movie, menuObj);
	}
}
