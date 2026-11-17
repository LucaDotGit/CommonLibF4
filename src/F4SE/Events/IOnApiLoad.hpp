#pragma once

#include "REX/NotNull.hpp"

namespace REL
{
	class HookList;
}

namespace F4SE::Events
{
	class IOnApiLoad
	{
	public:
		IOnApiLoad() noexcept = default;
		virtual ~IOnApiLoad() noexcept = default;

		IOnApiLoad(const IOnApiLoad&) noexcept = default;
		IOnApiLoad(IOnApiLoad&&) noexcept = default;

		auto operator=(const IOnApiLoad&) noexcept -> IOnApiLoad& = default;
		auto operator=(IOnApiLoad&&) noexcept -> IOnApiLoad& = default;

		virtual void OnApiLoad(const REX::NotNull<std::shared_ptr<REL::HookList>>& a_hookList) = 0;
	};
}
