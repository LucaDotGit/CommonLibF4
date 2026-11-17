#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class Object;
	class Variable;

	class __declspec(novtable) IVMObjectBindInterface
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IVMObjectBindInterface;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IVMObjectBindInterface;

		virtual ~IVMObjectBindInterface() = default; // 0x00

		// add
		virtual auto GetBoundHandle(const BSTSmartPointer<Object>& a_object) const -> ObjectHandle = 0;	 // 0x01
		virtual void TypeCanBeBound(const BSFixedString& a_scriptName, ObjectHandle a_objectHandle) = 0; // 0x02
		virtual void BindObject(
			BSTSmartPointer<Object>& a_object,
			ObjectHandle a_objectHandle,
			bool a_conditional) = 0; // 0x03
		virtual void HandleLoadedBinding(
			BSTSmartPointer<Object>& a_object,
			ObjectHandle a_objectHandle,
			bool a_conditional) = 0;												   // 0x04
		virtual void RemoveAllBoundObjects(ObjectHandle a_objectHandle) = 0;		   // 0x05
		virtual void RemoveAllDiskLoadedBoundObjects(ObjectHandle a_objectHandle) = 0; // 0x06
		virtual void HandleCObjectDeletion(ObjectHandle a_objectHandle) = 0;		   // 0x07
		virtual void UnbindObject(const BSTSmartPointer<Object>& a_object) = 0;		   // 0x08
		virtual auto CreateObject(
			const BSFixedString& a_scriptName,
			std::uint32_t a_numProperties,
			BSTSmartPointer<Object>& a_outObject) -> bool = 0; // 0x09
		virtual auto InitObjectProperties(
			const BSTSmartPointer<Object>& a_object,
			const BSTScrapHashMap<BSFixedString, Variable>& a_properties,
			std::uint32_t a_unk01,
			bool a_unk02) -> bool = 0; // 0x0A

		GAME_HEAP_REDEFINE_NEW(IVMObjectBindInterface);
	};

	static_assert(sizeof(IVMObjectBindInterface) == 0x08);
}
