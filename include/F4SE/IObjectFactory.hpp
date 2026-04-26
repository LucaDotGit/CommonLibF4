#pragma once

#include "F4SE/Core.hpp"

#include "REX/Own.hpp"

namespace F4SE
{
	class IObject;
}

namespace F4SE::Impl
{
	template <class T>
	concept IObjectConstraint =
		std::derived_from<T, F4SE::IObject> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::is_constructible_v<T, F4SE::SerializationTag> &&
		std::is_destructible_v<T>;
}

namespace F4SE
{
	class IObjectFactory
	{
	public:
		IObjectFactory() = default;

		IObjectFactory(const IObjectFactory&) = delete;
		IObjectFactory(IObjectFactory&&) = delete;

		IObjectFactory& operator=(const IObjectFactory&) = delete;
		IObjectFactory& operator=(IObjectFactory&&) = delete;

		virtual ~IObjectFactory() = default; // 00

		// add
		[[nodiscard]] virtual REX::Owner<IObject*> Create() const = 0; // 01
		virtual void Delete(REX::Owner<IObject*> a_object) const = 0;  // 02
		[[nodiscard]] virtual const char* GetObjectName() const = 0;   // 03
	};
	static_assert(sizeof(IObjectFactory) == 0x08);
}
