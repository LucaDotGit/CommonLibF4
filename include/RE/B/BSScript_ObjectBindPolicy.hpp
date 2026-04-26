#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::BSScript
{
	class BoundScript;
	class IHandleReaderWriter;
	class IVirtualMachine;
	class IVMObjectBindInterface;
	class MergedBoundScript;
	class Object;
	class Variable;

	class __declspec(novtable) ObjectBindPolicy
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ObjectBindPolicy };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ObjectBindPolicy };

		virtual ~ObjectBindPolicy(); // 00

		// add
		virtual void EnsureBaseDataLoaded(ObjectHandle a_objectHandle) = 0;																																											 // 01
		virtual void ObjectNoLongerNeeded(ObjectHandle a_objectHandle) = 0;																																											 // 02
		virtual void AddBoundInfoImpl(ObjectHandle a_objectHandle) = 0;																																												 // 03
		virtual void ClearBoundInfoImpl(ObjectHandle a_objectHandle) = 0;																																											 // 04
		virtual void ClearDiskLoadedBoundInfoImpl(ObjectHandle a_objectHandle) = 0;																																									 // 05
		virtual void ClearAllBoundInfoImpl() = 0;																																																	 // 06
		virtual void PostBindObject(ObjectHandle a_objectHandle) = 0;																																												 // 07
		virtual std::uint32_t GetExtraInfoSize(ObjectHandle) const = 0;																																												 // 08
		virtual void WriteExtraInfo(ObjectHandle a_objectHandle, const BSScript::IHandleReaderWriter& a_handleReaderWriter, BSStorage& a_storage) const = 0;																						 // 09
		virtual void ReadExtraInfo(ObjectHandle a_objectHandle, std::uint16_t a_handleVersion, const IHandleReaderWriter& a_handleReaderWriter, const BSStorage& a_storage) = 0;																	 // 0A
		virtual bool IsIgnoringClear() const = 0;																																																	 // 0B
		virtual void ResolveProperties(ObjectHandle a_objectTarget, const BSTSmartPointer<Object>& a_object, const BSTSmartPointer<BoundScript>& a_boundScript, bool a_postSaveConstOnly) = 0;														 // 0D
		virtual void ResolveProperties(ObjectHandle a_objectTarget, const BSTSmartPointer<Object>& a_object, const MergedBoundScript& a_boundScript, bool a_postSaveConstOnly) = 0;																	 // 0C
		virtual void ConvertProperties(ObjectHandle a_objectTarget, const BSTSmartPointer<BoundScript>& a_boundScript, bool a_constOnly, BSTScrapHashMap<BSFixedString, Variable>& a_properties, std::uint32_t& a_nonConvertedProperties) const = 0; // 0F
		virtual void ConvertProperties(ObjectHandle a_objectTarget, const MergedBoundScript& a_mergedScript, bool a_constOnly, BSTScrapHashMap<BSFixedString, Variable>& a_properties, std::uint32_t& a_nonConvertedProperties) const = 0;			 // 0E

		void BindObject(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle) const;
		void UnbindObject(const BSTSmartPointer<Object>& a_object) const;

		// members
		IVirtualMachine* vm;																		 // 10
		IVMObjectBindInterface* bindInterface;														 // 18
		mutable BSSpinLock attachedScriptsLock;														 // 20
		BSTHashMap<ObjectHandle, BSTSmallSharedArray<BSTSmartPointer<BoundScript>>> attachedScripts; // 50
	};
	static_assert(sizeof(ObjectBindPolicy) == 0x50);
}
