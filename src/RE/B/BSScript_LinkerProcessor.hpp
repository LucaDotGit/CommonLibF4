#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IObjectProcessor.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ErrorLogger;
	class ObjectTypeInfo;
	class StructTypeInfo;
}

namespace RE::BSScript::Internal
{
	class VirtualMachine;
}

namespace RE::BSScript
{
	class ITypeLinkedCallback;

	class __declspec(novtable) LinkerProcessor : public IObjectProcessor // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__LinkerProcessor;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__LinkerProcessor;

		~LinkerProcessor() override; // 0x00

		// override (IObjectProcessor)
		auto Clone() -> IObjectProcessor* override;						 // 0x01
		void SetLoader(ILoader* a_loader) override;						 // 0x02
		auto Process(const BSFixedString& a_className) -> bool override; // 0x03

		// members
		Internal::VirtualMachine* vm;											   // 0x08
		ErrorLogger* errorLogger;												   // 0x10
		ILoader* loader;														   // 0x18
		ITypeLinkedCallback* typeLinkedCallback;								   // 0x20
		bool forceReload;														   // 0x28
		BSScrapArray<BSFixedString> loadedParents;								   // 0x30
		BSScrapArray<BSFixedString> objectsToTypecheck;							   // 0x50
		BSScrapArray<BSFixedString> processQueue;								   // 0x70
		BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* objectTypeMap; // 0x90
		BSTHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>* structTypeMap; // 0x98
	};

	static_assert(sizeof(LinkerProcessor) == 0xA0);
}
