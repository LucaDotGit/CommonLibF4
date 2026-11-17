#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSString.hpp"
#include "RE/S/SCRIPT_HEADER.hpp"

namespace RE
{
	enum class COMPILER_NAME : std::int32_t;
	enum class SCRIPT_ERROR : std::int32_t;

	class SCRIPT_LINE;
	class SCRIPT_REFERENCED_OBJECT;
	class ScriptVariable;

	class ScriptCompileData
	{
	public:
		// members
		const char* input;										// 0x00
		std::uint32_t inputOffset;								// 0x08
		REX::Enum<COMPILER_NAME, std::int32_t> compilerIndex;	// 0x0C
		BSString scriptName;									// 0x10
		SCRIPT_ERROR lastError;									// 0x20
		bool isPartialScript;									// 0x24
		std::uint32_t lastLineNumber;							// 0x28
		char* output;											// 0x30
		std::uint32_t outputOffset;								// 0x38
		SCRIPT_HEADER header;									// 0x3C
		BSSimpleList<ScriptVariable*> listVariables;			// 0x50
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> listRefObjects; // 0x60
		Script* currentScript;									// 0x70
		BSSimpleList<SCRIPT_LINE*> listLines;					// 0x78
	};

	static_assert(sizeof(ScriptCompileData) == 0x88);
}
