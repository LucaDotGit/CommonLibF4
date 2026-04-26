#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSStringT.hpp"
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
		const char* input;										// 00
		std::uint32_t inputOffset;								// 08
		REX::Enum<COMPILER_NAME, std::int32_t> compilerIndex;	// 0C
		BSString scriptName;									// 10
		SCRIPT_ERROR lastError;									// 20
		bool isPartialScript;									// 24
		std::uint32_t lastLineNumber;							// 28
		char* output;											// 30
		std::uint32_t outputOffset;								// 38
		SCRIPT_HEADER header;									// 3C
		BSSimpleList<ScriptVariable*> listVariables;			// 50
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> listRefObjects; // 60
		Script* currentScript;									// 70
		BSSimpleList<SCRIPT_LINE*> listLines;					// 78
	};
	static_assert(sizeof(ScriptCompileData) == 0x88);
}
