#pragma once

namespace F4SE::Events
{
	class IOnPostPostLoad
	{
	public:
		IOnPostPostLoad() noexcept = default;
		virtual ~IOnPostPostLoad() noexcept = default;

		IOnPostPostLoad(const IOnPostPostLoad&) noexcept = default;
		IOnPostPostLoad(IOnPostPostLoad&&) noexcept = default;

		auto operator=(const IOnPostPostLoad&) noexcept -> IOnPostPostLoad& = default;
		auto operator=(IOnPostPostLoad&&) noexcept -> IOnPostPostLoad& = default;

		virtual void OnPostPostLoad() = 0;
	};
}
