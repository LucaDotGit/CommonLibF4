#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/IObject.hpp"
#include "F4SE/IObjectFactory.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"
#include "REX/StaticString.hpp"

namespace F4SE
{
	template <F4SE::Impl::IObjectConstraint T, REX::StaticString ObjectName>
	class UniqueObjectFactory final : public IObjectFactory
	{
	public:
		using value_type = T;

		inline static constexpr auto OBJECT_NAME = ObjectName;

		constexpr UniqueObjectFactory() = default;
		constexpr ~UniqueObjectFactory() noexcept override = default;

		constexpr UniqueObjectFactory(const UniqueObjectFactory&) = delete;
		constexpr UniqueObjectFactory(UniqueObjectFactory&&) = delete;

		constexpr auto operator=(const UniqueObjectFactory&) -> UniqueObjectFactory& = delete;
		constexpr auto operator=(UniqueObjectFactory&&) -> UniqueObjectFactory& = delete;

		[[nodiscard]]
		constexpr auto Create() const -> REX::Owner<IObject*> override
		{
			return CreateObject(DEFAULT_SERIALIZATION_TAG).get().release();
		}

		constexpr void Delete(REX::Owner<IObject*> a_object) const noexcept override
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

		template <class... Args>
		[[nodiscard]]
		constexpr auto CreateObject(Args&&... a_args) const -> REX::NotNull<std::unique_ptr<value_type>>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return std::make_unique<value_type>(std::forward<Args>(a_args)...);
		}

		constexpr void DeleteObject(REX::Owner<IObject*> a_object) const noexcept
		{
			delete a_object;
		}
	};
}
