#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
	class Variable;

	class __declspec(novtable) IVMObjectBindInterface
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IVMObjectBindInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IVMObjectBindInterface };

		virtual ~IVMObjectBindInterface() = default; // 00

		// add
		virtual ObjectHandle GetBoundHandle(const BSTSmartPointer<Object>& a_object) const = 0;																  // 01
		virtual void TypeCanBeBound(const BSFixedString& a_scriptName, ObjectHandle a_objectHandle) = 0;													  // 02
		virtual void BindObject(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle, bool a_conditional) = 0;									  // 03
		virtual void HandleLoadedBinding(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle, bool a_conditional) = 0;							  // 04
		virtual void RemoveAllBoundObjects(ObjectHandle a_objectHandle) = 0;																				  // 05
		virtual void RemoveAllDiskLoadedBoundObjects(ObjectHandle a_objectHandle) = 0;																		  // 06
		virtual void HandleCObjectDeletion(ObjectHandle a_objectHandle) = 0;																				  // 07
		virtual void UnbindObject(const BSTSmartPointer<Object>& a_object) = 0;																				  // 08
		virtual bool CreateObjectWithProperties(const BSFixedString& a_scriptName, std::uint32_t a_numProperties, BSTSmartPointer<Object>& a_object) = 0;	  // 09
		virtual bool InitObjectProperties(BSTSmartPointer<Object>& a_object, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, bool a_unk01) = 0; // 0A
	};
	static_assert(sizeof(IVMObjectBindInterface) == 0x08);
}
