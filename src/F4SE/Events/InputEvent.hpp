#pragma once

#include "REX/Ownership.hpp"

namespace RE
{
	class BSInputEventUser;
}

namespace F4SE::Events
{
	// These functions should only be used after the game data is ready;
	// they are also thread-safe.

	[[nodiscard]]
	auto IsRegisteredForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver) -> bool;
	auto RegisterForOnInput(REX::Owner<RE::BSInputEventUser*> a_inputReceiver) -> bool;
	auto UnregisterForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver) -> bool;
}
