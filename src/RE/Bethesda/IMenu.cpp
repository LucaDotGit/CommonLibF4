#include "RE/Bethesda/IMenu.hpp"

#include "RE/Bethesda/PlayerCharacter.hpp"

namespace RE
{
	WorkbenchMenuBase::InitParams::InitParams()
	{
		workbenchFurniture.reset();
		inventorySource = RE::PlayerCharacter::GetPlayerHandle();
	}
}
