#pragma once

#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/StructTypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class StructTypeInfo;
	class Variable;

	class Struct
		: public BSIntrusiveRefCounted // 00
	{
	public:
		~Struct();

		[[nodiscard]] StructTypeInfo* GetTypeInfo() { return type.get(); }
		[[nodiscard]] const StructTypeInfo* GetTypeInfo() const { return type.get(); }
		[[nodiscard]] constexpr bool IsConstructed() const noexcept { return constructed; }
		[[nodiscard]] constexpr bool IsValid() const noexcept { return valid; }

		F4_HEAP_REDEFINE_NEW(Struct);

		// members
		mutable BSSpinLock structLock;		  // 04
		BSTSmartPointer<StructTypeInfo> type; // 10
		bool constructed{ true };			  // 18
		bool valid{ false };				  // 19
		Variable variables[0];				  // 20
	};
	static_assert(sizeof(Struct) == 0x20);
}
