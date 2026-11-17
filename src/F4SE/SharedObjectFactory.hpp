#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/IObject.hpp"
#include "F4SE/IObjectFactory.hpp"
#include "F4SE/ISharedObjectFactoryList.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"
#include "REX/StaticString.hpp"

namespace F4SE::Impl
{
	[[nodiscard]]
	auto GetSharedObjectFactoryList() noexcept -> REX::NotNull<std::shared_ptr<F4SE::ISharedObjectFactoryList>>;
}

namespace F4SE
{
	template <F4SE::Impl::IObjectConstraint T, REX::StaticString ObjectName>
	class SharedObjectFactory final : public IObjectFactory
	{
	public:
		using value_type = T;

		inline static constexpr auto OBJECT_NAME = ObjectName;

		constexpr SharedObjectFactory() = default;
		constexpr ~SharedObjectFactory() noexcept override = default;

		constexpr SharedObjectFactory(const SharedObjectFactory&) = delete;
		constexpr SharedObjectFactory(SharedObjectFactory&&) = delete;

		constexpr auto operator=(const SharedObjectFactory&) -> SharedObjectFactory& = delete;
		constexpr auto operator=(SharedObjectFactory&&) -> SharedObjectFactory& = delete;

		[[nodiscard]]
		auto Create() const -> REX::Owner<IObject*> override
		{
			return CreateObject(DEFAULT_SERIALIZATION_TAG).get().get();
		}

		void Delete(REX::Owner<IObject*> a_object) const noexcept override
		{
			DeleteObject(a_object);
		}

		[[nodiscard]]
		constexpr auto GetName() const noexcept -> const char* override
		{
			return OBJECT_NAME.data();
		}

		[[nodiscard]]
		constexpr auto GetObjectName() const noexcept -> std::string_view
		{
			return std::string_view(OBJECT_NAME);
		}

		[[nodiscard]]
		auto GetObject(REX::Observer<const IObject*> a_object) const -> std::shared_ptr<value_type>
		{
			return Impl::GetSharedObjectFactoryList()->GetObject(a_object);
		}

		template <class... Args>
		[[nodiscard]]
		auto CreateObject(Args&&... a_args) const -> REX::NotNull<std::shared_ptr<value_type>>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			auto object = REX::NotNull(std::make_shared<value_type>(std::forward<Args>(a_args)...));
			Impl::GetSharedObjectFactoryList()->AddObject(object);
			return object;
		}

		auto DeleteObject(REX::Owner<IObject*> a_object) const noexcept -> bool
		{
			return Impl::GetSharedObjectFactoryList()->DeleteObject(a_object);
		}
	};
}
