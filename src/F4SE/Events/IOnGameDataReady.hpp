#pragma once

namespace F4SE::Events
{
	class IOnGameDataReady
	{
	public:
		IOnGameDataReady() noexcept = default;
		virtual ~IOnGameDataReady() noexcept = default;

		IOnGameDataReady(const IOnGameDataReady&) noexcept = default;
		IOnGameDataReady(IOnGameDataReady&&) noexcept = default;

		auto operator=(const IOnGameDataReady&) noexcept -> IOnGameDataReady& = default;
		auto operator=(IOnGameDataReady&&) noexcept -> IOnGameDataReady& = default;

		virtual void OnGameDataReady(bool a_isReady) = 0;
	};
}
