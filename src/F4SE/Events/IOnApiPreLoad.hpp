#pragma once

#include "REX/NotNull.hpp"

namespace REL
{
	class HookList;
}

namespace F4SE::Events
{
	class IOnApiPreLoad
	{
	public:
		IOnApiPreLoad() noexcept = default;
		virtual ~IOnApiPreLoad() noexcept = default;

		IOnApiPreLoad(const IOnApiPreLoad&) noexcept = default;
		IOnApiPreLoad(IOnApiPreLoad&&) noexcept = default;

		auto operator=(const IOnApiPreLoad&) noexcept -> IOnApiPreLoad& = default;
		auto operator=(IOnApiPreLoad&&) noexcept -> IOnApiPreLoad& = default;

		virtual void OnApiPreLoad(const REX::NotNull<std::shared_ptr<REL::HookList>>& a_hookList) = 0;
	};
}
