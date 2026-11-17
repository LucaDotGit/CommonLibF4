#pragma once

namespace F4SE::Events
{
	class IOnGameLoaded
	{
	public:
		IOnGameLoaded() noexcept = default;
		virtual ~IOnGameLoaded() noexcept = default;

		IOnGameLoaded(const IOnGameLoaded&) noexcept = default;
		IOnGameLoaded(IOnGameLoaded&&) noexcept = default;

		auto operator=(const IOnGameLoaded&) noexcept -> IOnGameLoaded& = default;
		auto operator=(IOnGameLoaded&&) noexcept -> IOnGameLoaded& = default;

		virtual void OnGameLoaded() = 0;
	};
}
