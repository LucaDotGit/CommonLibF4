#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/IObjectProcessor.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ErrorLogger;

	namespace Internal
	{
		class VirtualMachine;
	}

	class __declspec(novtable) LinkerProcessor
		: public IObjectProcessor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__LinkerProcessor };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__LinkerProcessor };

		virtual ~LinkerProcessor(); // 00

		// override (IObjectProcessor)
		virtual IObjectProcessor* Clone() override;						 // 01
		virtual void SetLoader(ILoader* a_loader) override;				 // 02 - { loader = a_loader; }
		virtual bool Process(const BSFixedString& a_className) override; // 03

		// members
		Internal::VirtualMachine* virtualMachine;		// 08
		ErrorLogger* errorLogger;						// 10
		ILoader* loader;								// 18
		std::uint64_t unk20;							// 20
		char* unk28;									// 28
		BSScrapArray<BSFixedString> loadedParents;		// 30
		BSScrapArray<BSFixedString> objectsToTypecheck; // 50
		BSScrapArray<BSFixedString> processQueue;		// 70

		BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* objectTypeInfoMap; // 90
		BSTHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>* structTypeInfoMap; // 98
	};
	static_assert(sizeof(LinkerProcessor) == 0xA0);
}
