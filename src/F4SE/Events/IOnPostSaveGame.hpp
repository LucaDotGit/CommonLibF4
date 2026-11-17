#pragma once

namespace F4SE::Events
{
	class IOnPostSaveGame
	{
	public:
		IOnPostSaveGame() noexcept = default;
		virtual ~IOnPostSaveGame() noexcept = default;

		IOnPostSaveGame(const IOnPostSaveGame&) noexcept = default;
		IOnPostSaveGame(IOnPostSaveGame&&) noexcept = default;

		auto operator=(const IOnPostSaveGame&) noexcept -> IOnPostSaveGame& = default;
		auto operator=(IOnPostSaveGame&&) noexcept -> IOnPostSaveGame& = default;

		virtual void OnPostSaveGame(std::string_view a_saveName) = 0;
	};
}
