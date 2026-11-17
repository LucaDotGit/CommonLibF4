#pragma once

#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class IObjectFactory;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class ObjectRegistry // final
	{
	public:
		ObjectRegistry() = delete;
		~ObjectRegistry() = delete;

		ObjectRegistry(const ObjectRegistry&) = delete;
		ObjectRegistry(ObjectRegistry&&) = delete;

		auto operator=(const ObjectRegistry&) -> ObjectRegistry& = delete;
		auto operator=(ObjectRegistry&&) -> ObjectRegistry& = delete;

		// add
		virtual auto RegisterFactory(
			[[maybe_unused]] REX::NotNull<REX::Observer<const IObjectFactory*>> a_factory) const -> bool // 0x00
		{
			return false;
		}

		[[nodiscard]]
		virtual auto GetFactoryByName([[maybe_unused]] const char* a_name) const
			-> REX::Observer<const IObjectFactory*> // 0x01
		{
			return nullptr;
		}
	};

	static_assert(sizeof(ObjectRegistry) == 0x08);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
