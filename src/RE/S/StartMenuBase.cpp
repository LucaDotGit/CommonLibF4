#include "RE/S/StartMenuBase.hpp"

#include "RE/D/DifficultyLevel.hpp"
#include "RE/P/PlayerCharacter.hpp"

namespace RE
{
	DifficultyLevel StartMenuBase::GetMenuDifficultyLevel()
	{
		if (currentDisplayDifficultyLevel) {
			return *currentDisplayDifficultyLevel;
		}

		const auto* player = PlayerCharacter::GetSingleton();
		if (!player) [[unlikely]] {
			REX::Assert(false);
			return DifficultyLevel::kNormal;
		}

		return player->GetDifficultyLevel();
	}
}
