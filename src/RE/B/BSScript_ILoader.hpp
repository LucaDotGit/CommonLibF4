#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class IStore;
}

namespace RE::BSScript::UnlinkedTypes
{
	class Object;
}

namespace RE::BSScript
{
	class __declspec(novtable) ILoader
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__ILoader;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__ILoader;

		virtual ~ILoader() = default; // 0x00

		// add
		virtual auto Clone() const -> ILoader* = 0;													   // 0x01
		virtual void SetScriptStore(const BSTSmartPointer<IStore>& a_newStore) = 0;					   // 0x02
		virtual auto GetClass(const char* a_name, UnlinkedTypes::Object& a_unlinkedClass) -> bool = 0; // 0x03

		GAME_HEAP_REDEFINE_NEW(ILoader);
	};

	static_assert(sizeof(ILoader) == 0x08);
}
