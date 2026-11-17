#pragma once

namespace REL
{
	class HookList;
}

namespace F4SE::Events
{
	class PreLoadInterface;
}

namespace F4SE::Events
{
	class IOnPluginPreLoad
	{
	public:
		IOnPluginPreLoad() noexcept = default;
		virtual ~IOnPluginPreLoad() noexcept = default;

		IOnPluginPreLoad(const IOnPluginPreLoad&) noexcept = default;
		IOnPluginPreLoad(IOnPluginPreLoad&&) noexcept = default;

		auto operator=(const IOnPluginPreLoad&) noexcept -> IOnPluginPreLoad& = default;
		auto operator=(IOnPluginPreLoad&&) noexcept -> IOnPluginPreLoad& = default;

		virtual void OnXsePreLoad(const PreLoadInterface& a_interface) = 0;
	};
}
