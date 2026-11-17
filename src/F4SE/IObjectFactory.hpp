#pragma once

#include "F4SE/Core.hpp"
#include "REX/Concepts.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class IObject;
}

namespace F4SE::Impl
{
	template <class T>
	concept IObjectConstraint = std::derived_from<T, F4SE::IObject> &&
								!REX::pointer<T> &&
								!REX::reference<T> &&
								std::is_constructible_v<T, F4SE::SerializationTag> &&
								std::is_destructible_v<T> &&
								std::is_nothrow_destructible_v<T>;
}

namespace F4SE
{
	class IObjectFactory
	{
	public:
		IObjectFactory() noexcept = default;

		IObjectFactory(const IObjectFactory&) = delete;
		IObjectFactory(IObjectFactory&&) = delete;

		auto operator=(const IObjectFactory&) -> IObjectFactory& = delete;
		auto operator=(IObjectFactory&&) -> IObjectFactory& = delete;

		virtual ~IObjectFactory() noexcept = default; // 0x00

		// add
		[[nodiscard]]
		virtual auto Create() const -> REX::Owner<IObject*> = 0;			   // 0x01
		virtual void Delete(REX::Owner<IObject*> a_object) const noexcept = 0; // 0x02
		[[nodiscard]]
		virtual auto GetName() const noexcept -> const char* = 0; // 0x03
	};

	static_assert(sizeof(IObjectFactory) == 0x08);
}
