#include "RE/W/WorkbenchMenuBase.hpp"

#include "RE/P/PlayerCharacter.hpp"

namespace RE
{
	WorkbenchMenuBase::InitParams::InitParams()
	{
		inventorySource = PlayerCharacter::GetPlayerHandle();
	}
}
