#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_MergedBoundScript.hpp"
#include "RE/B/BSScript_ObjectBindPolicy.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
	class Variable;
}

namespace RE::GameScript
{
	class __declspec(novtable) ObjectBindPolicy
		: public BSScript::ObjectBindPolicy // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__ObjectBindPolicy };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__ObjectBindPolicy };

		class QueuedObject
		{
		public:
			// members
			BSTSmartPointer<BSScript::Object> createdObject; // 00
			BSScript::MergedBoundScript boundInfo;			 // 08
		};
		static_assert(sizeof(QueuedObject) == 0x18);

		// override (BSScript::ObjectBindPolicy)
		void EnsureBaseDataLoaded(BSScript::ObjectHandle a_objectHandle) override;																																																// 01
		void ObjectNoLongerNeeded(BSScript::ObjectHandle a_objectHandle) override;																																																// 02
		void AddBoundInfoImpl(BSScript::ObjectHandle a_objectHandle) override;																																																	// 03
		void ClearBoundInfoImpl(BSScript::ObjectHandle a_objectHandle) override;																																																// 04
		void ClearDiskLoadedBoundInfoImpl(BSScript::ObjectHandle a_objectHandle) override;																																														// 05
		void ClearAllBoundInfoImpl() override;																																																									// 06
		void PostBindObject(BSScript::ObjectHandle a_objectHandle) override;																																																	// 07
		std::uint32_t GetExtraInfoSize(BSScript::ObjectHandle a_objectHandle) const override;																																													// 08 - { return 0; }
		void WriteExtraInfo(BSScript::ObjectHandle a_objectHandle, const BSScript::IHandleReaderWriter& a_handleReaderWriter, BSStorage& a_storage) const override;																												// 09 - { return; }
		void ReadExtraInfo(BSScript::ObjectHandle a_objectHandle, std::uint16_t a_handleVersion, const BSScript::IHandleReaderWriter& a_handleReaderWriter, const BSStorage& a_storage) override;																				// 0A
		bool IsIgnoringClear() const override;																																																									// 0B
		void ResolveProperties(BSScript::ObjectHandle a_objectTarget, const BSTSmartPointer<BSScript::Object>& a_object, const BSTSmartPointer<BSScript::BoundScript>& a_boundScript, bool a_postSaveConstOnly) override;														// 0D
		void ResolveProperties(BSScript::ObjectHandle a_objectTarget, const BSTSmartPointer<BSScript::Object>& a_object, const BSScript::MergedBoundScript& a_boundScript, bool a_postSaveConstOnly) override;																	// 0C
		void ConvertProperties(BSScript::ObjectHandle a_objectTarget, const BSTSmartPointer<BSScript::BoundScript>& a_boundScript, bool a_constOnly, BSTScrapHashMap<BSFixedString, BSScript::Variable>& a_properties, std::uint32_t& a_nonConvertedProperties) const override; // 0F
		void ConvertProperties(BSScript::ObjectHandle a_objectTarget, const BSScript::MergedBoundScript& a_mergedScript, bool a_constOnly, BSTScrapHashMap<BSFixedString, BSScript::Variable>& a_properties, std::uint32_t& a_nonConvertedProperties) const override;			// 0E

		void EndSaveLoad()
		{
			using FuncType = decltype(&ObjectBindPolicy::EndSaveLoad);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::ObjectBindPolicy::EndSaveLoad };
			FUNC(this);
		}

		// members
		mutable BSSpinLock queueLock;														 // 50
		bool resolveCalled;																	 // 58
		bool ignoringClear;																	 // 59
		bool initialLoadDone;																 // 5A
		BSTHashMap<BSScript::ObjectHandle, BSTSmallSharedArray<QueuedObject>> queuedObjects; // 60
		BSTArray<BSScript::ObjectHandle> queuedAliases;										 // 90
		BSTSet<BSScript::ObjectHandle> initiallyLoadedObjects;								 // A8
	};
	static_assert(sizeof(ObjectBindPolicy) == 0xD8);
}
