#pragma once

namespace REL
{
	class HookList;
}

namespace F4SE
{
	class LoadInterface;
}

namespace F4SE::Events
{
	class IOnPluginLoad
	{
	public:
		IOnPluginLoad() noexcept = default;
		virtual ~IOnPluginLoad() noexcept = default;

		IOnPluginLoad(const IOnPluginLoad&) noexcept = default;
		IOnPluginLoad(IOnPluginLoad&&) noexcept = default;

		auto operator=(const IOnPluginLoad&) noexcept -> IOnPluginLoad& = default;
		auto operator=(IOnPluginLoad&&) noexcept -> IOnPluginLoad& = default;

		virtual void OnPluginLoad(const LoadInterface* a_interface) = 0;
	};
}
