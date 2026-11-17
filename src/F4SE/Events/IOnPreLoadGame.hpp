#pragma once

namespace F4SE::Events
{
	class IOnPreLoadGame
	{
	public:
		IOnPreLoadGame() noexcept = default;
		virtual ~IOnPreLoadGame() noexcept = default;

		IOnPreLoadGame(const IOnPreLoadGame&) noexcept = default;
		IOnPreLoadGame(IOnPreLoadGame&&) noexcept = default;

		auto operator=(const IOnPreLoadGame&) noexcept -> IOnPreLoadGame& = default;
		auto operator=(IOnPreLoadGame&&) noexcept -> IOnPreLoadGame& = default;

		virtual void OnPreLoadGame(std::string_view a_saveName) = 0;
	};
}
