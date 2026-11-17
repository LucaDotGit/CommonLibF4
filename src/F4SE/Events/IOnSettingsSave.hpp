#pragma once

namespace F4SE::Events
{
	class IOnSettingsSave
	{
	public:
		IOnSettingsSave() noexcept = default;
		virtual ~IOnSettingsSave() noexcept = default;

		IOnSettingsSave(const IOnSettingsSave&) noexcept = default;
		IOnSettingsSave(IOnSettingsSave&&) noexcept = default;

		auto operator=(const IOnSettingsSave&) noexcept -> IOnSettingsSave& = default;
		auto operator=(IOnSettingsSave&&) noexcept -> IOnSettingsSave& = default;

		virtual void OnSettingsSave() = 0;
	};
}
