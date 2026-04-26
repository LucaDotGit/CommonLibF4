#include "RE/W/WorkbenchMenuBase.hpp"

#include "RE/P/PlayerCharacter.hpp"

namespace RE
{
	WorkbenchMenuBase::InitParams::InitParams()
	{
		inventorySource = RE::PlayerCharacter::GetPlayerHandle();
	}
}
