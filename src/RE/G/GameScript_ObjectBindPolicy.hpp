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
	class __declspec(novtable) ObjectBindPolicy : public BSScript::ObjectBindPolicy // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__ObjectBindPolicy;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__ObjectBindPolicy;

		class QueuedObject
		{
		public:
			// members
			BSTSmartPointer<BSScript::Object> createdObject; // 0x00
			BSScript::MergedBoundScript boundInfo;			 // 0x08
		};

		static_assert(sizeof(QueuedObject) == 0x18);

		// override (BSScript::ObjectBindPolicy)
		void EnsureBaseDataLoaded(BSScript::ObjectHandle a_objectHandle) override;		   // 0x01
		void ObjectNoLongerNeeded(BSScript::ObjectHandle a_objectHandle) override;		   // 0x02
		void AddBoundInfoImpl(BSScript::ObjectHandle a_objectHandle) override;			   // 0x03
		void ClearBoundInfoImpl(BSScript::ObjectHandle a_objectHandle) override;		   // 0x04
		void ClearDiskLoadedBoundInfoImpl(BSScript::ObjectHandle a_objectHandle) override; // 0x05
		void ClearAllBoundInfoImpl() override;											   // 0x06
		void PostBindObject(BSScript::ObjectHandle a_objectHandle) override;			   // 0x07
		auto GetExtraInfoSize(BSScript::ObjectHandle a_objectHandle) const
			-> std::uint32_t override; // 0x08 - { return 0; }
		void WriteExtraInfo(
			BSScript::ObjectHandle a_objectHandle,
			const BSScript::IHandleReaderWriter& a_handleReaderWriter,
			BSStorage& a_storage) const override; // 0x09 - { return; }
		void ReadExtraInfo(
			BSScript::ObjectHandle a_objectHandle,
			std::uint16_t a_handleVersion,
			const BSScript::IHandleReaderWriter& a_handleReaderWriter,
			const BSStorage& a_storage) override;	   // 0x0A
		auto IsIgnoringClear() const -> bool override; // 0x0B
		void ResolveProperties(
			BSScript::ObjectHandle a_objectTarget,
			const BSTSmartPointer<BSScript::Object>& a_object,
			const BSTSmartPointer<BSScript::BoundScript>& a_boundScript,
			bool a_postSaveConstOnly) override; // 0x0D
		void ResolveProperties(
			BSScript::ObjectHandle a_objectTarget,
			const BSTSmartPointer<BSScript::Object>& a_object,
			const BSScript::MergedBoundScript& a_boundScript,
			bool a_postSaveConstOnly) override; // 0x0C
		void ConvertProperties(
			BSScript::ObjectHandle a_objectTarget,
			const BSTSmartPointer<BSScript::BoundScript>& a_boundScript,
			bool a_constOnly,
			BSTScrapHashMap<BSFixedString, BSScript::Variable>& a_properties,
			std::uint32_t& a_nonConvertedProperties) const override; // 0x0F
		void ConvertProperties(
			BSScript::ObjectHandle a_objectTarget,
			const BSScript::MergedBoundScript& a_mergedScript,
			bool a_constOnly,
			BSTScrapHashMap<BSFixedString, BSScript::Variable>& a_properties,
			std::uint32_t& a_nonConvertedProperties) const override; // 0x0E

		void EndSaveLoad()
		{
			using FuncType = decltype(&ObjectBindPolicy::EndSaveLoad);
			static const auto FUNC = REL::Relocation<FuncType>(ID::GameScript::ObjectBindPolicy::EndSaveLoad);
			std::invoke(FUNC, this);
		}

		// members
		mutable BSSpinLock queueLock;														 // 0x50
		bool resolveCalled;																	 // 0x58
		bool ignoringClear;																	 // 0x59
		bool initialLoadDone;																 // 0x5A
		BSTHashMap<BSScript::ObjectHandle, BSTSmallSharedArray<QueuedObject>> queuedObjects; // 0x60
		BSTArray<BSScript::ObjectHandle> queuedAliases;										 // 0x90
		BSTSet<BSScript::ObjectHandle> initiallyLoadedObjects;								 // 0xA8
	};

	static_assert(sizeof(ObjectBindPolicy) == 0xD8);
}
