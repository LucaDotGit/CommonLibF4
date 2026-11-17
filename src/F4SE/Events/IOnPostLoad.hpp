#pragma once

namespace F4SE::Events
{
	class IOnPostLoad
	{
	public:
		IOnPostLoad() noexcept = default;
		virtual ~IOnPostLoad() noexcept = default;

		IOnPostLoad(const IOnPostLoad&) noexcept = default;
		IOnPostLoad(IOnPostLoad&&) noexcept = default;

		auto operator=(const IOnPostLoad&) noexcept -> IOnPostLoad& = default;
		auto operator=(IOnPostLoad&&) noexcept -> IOnPostLoad& = default;

		virtual void OnPostLoad() = 0;
	};
}
