#pragma once

namespace F4SE::Events
{
	class IOnSettingsLoad
	{
	public:
		IOnSettingsLoad() noexcept = default;
		virtual ~IOnSettingsLoad() noexcept = default;

		IOnSettingsLoad(const IOnSettingsLoad&) noexcept = default;
		IOnSettingsLoad(IOnSettingsLoad&&) noexcept = default;

		auto operator=(const IOnSettingsLoad&) noexcept -> IOnSettingsLoad& = default;
		auto operator=(IOnSettingsLoad&&) noexcept -> IOnSettingsLoad& = default;

		virtual void OnSettingsLoad() = 0;
	};
}
