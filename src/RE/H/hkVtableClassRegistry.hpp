#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hkVtableClassRegistry : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkVtableClassRegistry;
		inline static constexpr const auto& VTABLE = VTABLE::hkVtableClassRegistry;

		~hkVtableClassRegistry() override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() -> hkVtableClassRegistry*
		{
			static const auto SINGLETON = REL::Relocation<hkVtableClassRegistry*>(ID::hkVtableClassRegistry::Singleton);
			return SINGLETON.get();
		}
	};

	static_assert(sizeof(hkVtableClassRegistry) == 0x10);
}
