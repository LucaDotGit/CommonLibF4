#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hkVtableClassRegistry
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkVtableClassRegistry };
		inline static constexpr auto VTABLE{ VTABLE::hkVtableClassRegistry };

		~hkVtableClassRegistry() override; // 00

		[[nodiscard]] static hkVtableClassRegistry* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<hkVtableClassRegistry*>{ ID::hkVtableClassRegistry::Singleton };
			return SINGLETON.get();
		}
	};
	static_assert(sizeof(hkVtableClassRegistry) == 0x10);
}
