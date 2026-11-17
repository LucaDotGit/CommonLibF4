#pragma once

namespace F4SE::Events
{
	class IOnInputLoaded
	{
	public:
		IOnInputLoaded() noexcept = default;
		virtual ~IOnInputLoaded() noexcept = default;

		IOnInputLoaded(const IOnInputLoaded&) noexcept = default;
		IOnInputLoaded(IOnInputLoaded&&) noexcept = default;

		auto operator=(const IOnInputLoaded&) noexcept -> IOnInputLoaded& = default;
		auto operator=(IOnInputLoaded&&) noexcept -> IOnInputLoaded& = default;

		virtual void OnInputLoaded() = 0;
	};
}
