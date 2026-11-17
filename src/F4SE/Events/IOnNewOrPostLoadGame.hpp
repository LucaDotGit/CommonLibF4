#pragma once

namespace F4SE::Events
{
	class IOnNewOrPostLoadGame
	{
	public:
		IOnNewOrPostLoadGame() noexcept = default;
		virtual ~IOnNewOrPostLoadGame() noexcept = default;

		IOnNewOrPostLoadGame(const IOnNewOrPostLoadGame&) noexcept = default;
		IOnNewOrPostLoadGame(IOnNewOrPostLoadGame&&) noexcept = default;

		auto operator=(const IOnNewOrPostLoadGame&) noexcept -> IOnNewOrPostLoadGame& = default;
		auto operator=(IOnNewOrPostLoadGame&&) noexcept -> IOnNewOrPostLoadGame& = default;

		virtual void OnNewOrPostLoadGame(bool a_isSuccessful) = 0;
	};
}
