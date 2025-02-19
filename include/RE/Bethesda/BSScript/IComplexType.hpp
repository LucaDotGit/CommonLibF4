#pragma once

#include "RE/Bethesda/BSScript/TypeInfo.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class TypeInfo;

	class __declspec(novtable) IComplexType
		: public BSIntrusiveRefCounted // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IComplexType };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IComplexType };

		// To-Do: Verify that setting this to default doesn't fuck everything up
		virtual ~IComplexType() = default; // 00

		// add
		virtual TypeInfo::RawType GetRawType() const = 0; // 01

		[[nodiscard]] bool IsObject() const { return GetRawType() == TypeInfo::RawType::kObject; }
	};
	static_assert(sizeof(IComplexType) == 0x10);
}
