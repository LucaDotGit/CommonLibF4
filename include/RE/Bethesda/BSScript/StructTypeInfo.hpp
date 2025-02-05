#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/IComplexType.hpp"
#include "RE/Bethesda/BSScript/ObjectTypeInfo.hpp"
#include "RE/Bethesda/BSScript/TypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTObjectArena.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/BSTTuple.hpp"
#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	namespace BSScript
	{
		class IComplexType;
		class ObjectTypeInfo;
		class TypeInfo;
		class Variable;

		class __declspec(novtable) StructTypeInfo
			: public IComplexType // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BSScript__StructTypeInfo };
			inline static constexpr auto VTABLE{ VTABLE::BSScript__StructTypeInfo };

			enum class LinkValidState
			{
				kNotLinked,
				kCurrentlyLinking,
				kLinkedInvalid,
				kLinkedValid
			};

			struct StructVar
			{
			public:
				// members
				Variable initialValue;	 // 00
				TypeInfo varType;		 // 10
				BSFixedString docString; // 18
				std::uint32_t userFlags; // 20
				bool isConst;			 // 24
			};
			static_assert(sizeof(StructVar) == 0x28);

			const char* GetName() const
			{
				return name.c_str();
			}

			virtual TypeInfo::RawType GetRawType() const override;

			// members
			BSFixedString name;										  // 10
			BSTSmartPointer<ObjectTypeInfo> containingObjTypeInfo;	  // 18
			BSTArray<StructVar> variables;							  // 20
			BSTHashMap<BSFixedString, std::uint32_t> varNameIndexMap; // 38
			REX::Enum<LinkValidState, std::uint32_t> linkedValid;	  // 68
		};
		static_assert(sizeof(StructTypeInfo) == 0x70);
	}
}
