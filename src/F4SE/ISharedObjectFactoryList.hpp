#pragma once

#include "F4SE/IObject.hpp"
#include "F4SE/IObjectFactory.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class ISharedObjectFactoryList : public std::enable_shared_from_this<ISharedObjectFactoryList>
	{
	public:
		using value_type = IObject;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		ISharedObjectFactoryList() = default;
		virtual ~ISharedObjectFactoryList() noexcept = default;

		ISharedObjectFactoryList(const ISharedObjectFactoryList&) = delete;
		ISharedObjectFactoryList(ISharedObjectFactoryList&&) = delete;

		auto operator=(const ISharedObjectFactoryList&) -> ISharedObjectFactoryList& = delete;
		auto operator=(ISharedObjectFactoryList&&) -> ISharedObjectFactoryList& = delete;

		[[nodiscard]]
		virtual auto GetObject(REX::Observer<const_pointer> a_object) const -> std::shared_ptr<value_type> = 0;
		virtual void AddObject(REX::NotNull<std::shared_ptr<value_type>> a_object) = 0;
		virtual auto DeleteObject(REX::Owner<pointer> a_object) noexcept -> bool = 0;
	};
}
