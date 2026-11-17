#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class hkProcess;
	class hkProcessContext;

	class __declspec(novtable) hkProcessFactory : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkProcessFactory;
		inline static constexpr const auto& VTABLE = VTABLE::hkProcessFactory;

		~hkProcessFactory() override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() -> hkProcessFactory*
		{
			static const auto SINGLETON = REL::Relocation<hkProcessFactory*>(ID::hkProcessFactory::Singleton);
			return SINGLETON.get();
		}

		[[nodiscard]]
		auto CreateProcess(const char* a_name, hkArray<hkProcessContext*>& a_contexts) -> hkProcess*
		{
			using FuncType = decltype(&hkProcessFactory::CreateProcess);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hkProcessFactory::CreateProcess);
			return std::invoke(FUNC, this, a_name, a_contexts);
		}
	};

	static_assert(sizeof(hkProcessFactory) == 0x10);
}
