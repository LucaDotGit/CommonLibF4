#pragma once

namespace F4SE::Events
{
	class IOnPostLoadGame
	{
	public:
		IOnPostLoadGame() noexcept = default;
		virtual ~IOnPostLoadGame() noexcept = default;

		IOnPostLoadGame(const IOnPostLoadGame&) noexcept = default;
		IOnPostLoadGame(IOnPostLoadGame&&) noexcept = default;

		auto operator=(const IOnPostLoadGame&) noexcept -> IOnPostLoadGame& = default;
		auto operator=(IOnPostLoadGame&&) noexcept -> IOnPostLoadGame& = default;

		virtual void OnPostLoadGame(bool a_isSuccessful) = 0;
	};
}
