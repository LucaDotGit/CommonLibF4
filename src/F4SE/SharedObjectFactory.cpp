#include "F4SE/SharedObjectFactory.hpp"

#include "F4SE/Api.hpp"

namespace F4SE::Impl
{
	auto GetSharedObjectFactoryList() noexcept -> REX::NotNull<std::shared_ptr<F4SE::ISharedObjectFactoryList>>
	{
		return F4SE::GetSharedObjectFactoryList();
	}
}
