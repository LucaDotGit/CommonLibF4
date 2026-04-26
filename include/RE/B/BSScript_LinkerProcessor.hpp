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

	class __declspec(novtable) LinkerProcessor
		: public IObjectProcessor // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__LinkerProcessor };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__LinkerProcessor };

		~LinkerProcessor() override; // 00

		// override (IObjectProcessor)
		IObjectProcessor* Clone() override;						 // 01
		void SetLoader(ILoader* a_loader) override;				 // 02
		bool Process(const BSFixedString& a_className) override; // 03

		// members
		Internal::VirtualMachine* vm;												   // 08
		ErrorLogger* errorLogger;													   // 10
		ILoader* loader;															   // 18
		ITypeLinkedCallback* typeLinkedCallback;									   // 20
		bool forceReload;															   // 28
		BSScrapArray<BSFixedString> loadedParents;									   // 30
		BSScrapArray<BSFixedString> typecheckedObjects;								   // 50
		BSScrapArray<BSFixedString> processQueue;									   // 70
		BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* objectTypeInfoMap; // 90
		BSTHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>* structTypeInfoMap; // 98
	};
	static_assert(sizeof(LinkerProcessor) == 0xA0);
}
