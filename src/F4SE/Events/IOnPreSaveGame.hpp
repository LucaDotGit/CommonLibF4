#pragma once

namespace F4SE::Events
{
	class IOnPreSaveGame
	{
	public:
		IOnPreSaveGame() noexcept = default;
		virtual ~IOnPreSaveGame() noexcept = default;

		IOnPreSaveGame(const IOnPreSaveGame&) noexcept = default;
		IOnPreSaveGame(IOnPreSaveGame&&) noexcept = default;

		auto operator=(const IOnPreSaveGame&) noexcept -> IOnPreSaveGame& = default;
		auto operator=(IOnPreSaveGame&&) noexcept -> IOnPreSaveGame& = default;

		virtual void OnPreSaveGame(std::string_view a_saveName) = 0;
	};
}
