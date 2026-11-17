#pragma once

namespace F4SE::Events
{
	class IOnDeleteGame
	{
	public:
		IOnDeleteGame() noexcept = default;
		virtual ~IOnDeleteGame() noexcept = default;

		IOnDeleteGame(const IOnDeleteGame&) noexcept = default;
		IOnDeleteGame(IOnDeleteGame&&) noexcept = default;

		auto operator=(const IOnDeleteGame&) noexcept -> IOnDeleteGame& = default;
		auto operator=(IOnDeleteGame&&) noexcept -> IOnDeleteGame& = default;

		virtual void OnDeleteGame(std::string_view a_saveName) = 0;
	};
}
