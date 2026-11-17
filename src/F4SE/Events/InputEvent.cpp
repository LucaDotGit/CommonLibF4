#include "F4SE/Events/InputEvent.hpp"

#include "RE/B/BSInputEventUser.hpp"
#include "RE/M/MenuControls.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Events
{
	// Doing the same with `RE::PlayerControls` would cause the events to only fire in game mode,
	// so `RE::MenuControls` is used instead, which almost always processes input events.

	auto IsRegisteredForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver) -> bool
	{
		if (!a_inputReceiver) {
			return false;
		}

		auto* menuControls = RE::MenuControls::GetSingleton();
		if (!menuControls) {
			return false;
		}

		return menuControls->IsInputHandlerRegistered(a_inputReceiver);
	}

	auto RegisterForOnInput(REX::Owner<RE::BSInputEventUser*> a_inputReceiver) -> bool
	{
		if (!a_inputReceiver) {
			return false;
		}

		auto* menuControls = RE::MenuControls::GetSingleton();
		if (!menuControls) {
			return false;
		}

		return menuControls->RegisterInputHandler(a_inputReceiver);
	}

	auto UnregisterForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver) -> bool
	{
		if (!a_inputReceiver) {
			return false;
		}

		auto* menuControls = RE::MenuControls::GetSingleton();
		if (!menuControls) {
			return false;
		}

		return menuControls->UnregisterInputHandler(a_inputReceiver);
	}
}
