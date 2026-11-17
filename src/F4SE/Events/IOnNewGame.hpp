#pragma once

#include "REX/Ownership.hpp"

namespace RE
{
	class TESQuest;
}

namespace F4SE::Events
{
	class IOnNewGame
	{
	public:
		IOnNewGame() noexcept = default;
		virtual ~IOnNewGame() noexcept = default;

		IOnNewGame(const IOnNewGame&) noexcept = default;
		IOnNewGame(IOnNewGame&&) noexcept = default;

		auto operator=(const IOnNewGame&) noexcept -> IOnNewGame& = default;
		auto operator=(IOnNewGame&&) noexcept -> IOnNewGame& = default;

		virtual void OnNewGame(REX::Observer<RE::TESQuest*> a_charGenQuest) = 0;
	};
}
