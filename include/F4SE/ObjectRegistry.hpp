#pragma once

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace F4SE
{
	class IObjectFactory;

#if _MSC_VER > 0l
#pragma warning(push)
#pragma warning(disable : 4265) // 'class': class has virtual functions, but destructor is not virtual
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class ObjectRegistry // final
	{
	public:
		ObjectRegistry() = delete;
		~ObjectRegistry() = delete;

		ObjectRegistry(const ObjectRegistry&) = delete;
		ObjectRegistry(ObjectRegistry&&) = delete;

		ObjectRegistry& operator=(const ObjectRegistry&) = delete;
		ObjectRegistry& operator=(ObjectRegistry&&) = delete;

		// add
		virtual bool RegisterFactory([[maybe_unused]] REX::NotNull<REX::Observer<IObjectFactory*>> a_factory) const { return false; }			   // 00
		[[nodiscard]] virtual REX::Observer<const IObjectFactory*> GetFactoryByName([[maybe_unused]] const char* a_name) const { return nullptr; } // 01
	};
	static_assert(sizeof(ObjectRegistry) == 0x08);

#if _MSC_VER > 0l
#pragma warning(pop)
#endif
}
