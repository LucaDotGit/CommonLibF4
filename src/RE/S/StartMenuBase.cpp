#include "RE/S/StartMenuBase.hpp"

#include "RE/D/DifficultyLevel.hpp"
#include "RE/P/PlayerCharacter.hpp"

namespace RE
{
	auto StartMenuBase::GetMenuDifficultyLevel() -> DifficultyLevel
	{
		if (currentDisplayDifficultyLevel.has_value()) {
			return currentDisplayDifficultyLevel.value();
		}

		const auto* player = PlayerCharacter::GetSingleton();
		if (!player) [[unlikely]] {
			REX::Assert(false);
			return DifficultyLevel::Normal;
		}

		return player->GetDifficultyLevel();
	}
}
