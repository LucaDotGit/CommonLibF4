#pragma once

#include "RE/B/BSScript_ILoader.hpp"
#include "RE/B/BSScript_Internal_ReadableStringTable.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ErrorLogger;

	class __declspec(novtable) CompiledScriptLoader : public ILoader // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__CompiledScriptLoader;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__CompiledScriptLoader;

		// override (ILoader)
		auto Clone() const -> ILoader* override;													// 0x01
		void SetScriptStore(const BSTSmartPointer<IStore>& a_newStore) override;					// 0x02
		auto GetClass(const char* a_name, UnlinkedTypes::Object& a_unlinkedClass) -> bool override; // 0x03

		// members
		ErrorLogger* errorHandler;				   // 0x08
		BSTSmartPointer<IStore> scriptStore;	   // 0x10
		Internal::ReadableStringTable stringTable; // 0x18
		std::int8_t fileMajorVersion;			   // 0x30
		std::int8_t fileMinorVersion;			   // 0x31
		std::int8_t loadFlags;					   // 0x32
	};

	static_assert(sizeof(CompiledScriptLoader) == 0x38);
}
