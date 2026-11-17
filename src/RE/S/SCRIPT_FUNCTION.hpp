#pragma once

namespace RE
{
	enum class SCRIPT_OUTPUT : std::int32_t;

	class ConditionCheckParams;
	class SCRIPT_LINE;
	class SCRIPT_PARAMETER;
	class ScriptCompileData;
	class ScriptLocals;

	class SCRIPT_FUNCTION
	{
	public:
		using ConditionFunctionType =
			bool(ConditionCheckParams& a_data, void* a_param2, void* a_param1, REX::Float32& a_returnValue);
		using CompileFunctionType = bool(
			std::uint16_t a_paramCount,
			const SCRIPT_PARAMETER* a_parameters,
			SCRIPT_LINE* a_scriptLine,
			ScriptCompileData* a_compileData);
		using ExecuteFunctionType = bool(
			const SCRIPT_PARAMETER* a_parameters,
			const char* a_compiledParams,
			TESObjectREFR* a_refObject,
			TESObjectREFR* a_container,
			Script* a_script,
			ScriptLocals* a_scriptLocals,
			REX::Float32& a_returnValue,
			std::uint32_t& a_offset);

		class StringChunk;
		class IntegerChunk;

		class Chunk
		{
		public:
			[[nodiscard]]
			auto AsInteger() noexcept -> IntegerChunk*;
			[[nodiscard]]
			auto AsString() noexcept -> StringChunk*;

			[[nodiscard]]
			auto AsInteger() const noexcept -> const IntegerChunk*;
			[[nodiscard]]
			auto AsString() const noexcept -> const StringChunk*;
		};

		class IntegerChunk : public Chunk // 0x00
		{
		public:
			[[nodiscard]]
			auto GetNext() noexcept -> SCRIPT_FUNCTION::Chunk*;
			[[nodiscard]]
			auto GetNext() const noexcept -> const SCRIPT_FUNCTION::Chunk*;

			[[nodiscard]]
			auto GetValue() const noexcept -> std::int32_t;

			// members
			std::int8_t magic;	// 0x00
			std::int32_t value; // 0x01
		};

		static_assert(sizeof(IntegerChunk) == 0x08);

		class StringChunk : public Chunk // 0x00
		{
		public:
			[[nodiscard]]
			auto GetNext() noexcept -> SCRIPT_FUNCTION::Chunk*;
			[[nodiscard]]
			auto GetNext() const noexcept -> const SCRIPT_FUNCTION::Chunk*;

			[[nodiscard]]
			auto GetValue() const noexcept -> std::string_view;

			// members
			std::uint16_t length; // 0x00
			char str[0];		  // 0x02 - NOLINT(modernize-avoid-c-arrays)
		};

		static_assert(sizeof(StringChunk) == 0x02);

		class ScriptData
		{
		public:
			[[nodiscard]]
			auto GetChunk() noexcept -> SCRIPT_FUNCTION::Chunk*;
			[[nodiscard]]
			auto GetChunk() const noexcept -> const SCRIPT_FUNCTION::Chunk*;

			[[nodiscard]]
			auto GetIntegerChunk() noexcept -> SCRIPT_FUNCTION::IntegerChunk*;
			[[nodiscard]]
			auto GetIntegerChunk() const noexcept -> const SCRIPT_FUNCTION::IntegerChunk*;

			[[nodiscard]]
			auto GetStringChunk() noexcept -> SCRIPT_FUNCTION::StringChunk*;
			[[nodiscard]]
			auto GetStringChunk() const noexcept -> const SCRIPT_FUNCTION::StringChunk*;

			// members
			std::uint16_t opcode;	 // 0x00
			std::uint16_t chunkSize; // 0x02
			std::uint16_t numParams; // 0x04
		};

		static_assert(sizeof(ScriptData) == 0x06);

		[[nodiscard]]
		static auto GetConsoleFunctions() -> std::span<SCRIPT_FUNCTION>;
		[[nodiscard]]
		static auto GetScriptFunctions() -> std::span<SCRIPT_FUNCTION>;

		[[nodiscard]]
		static auto GetConsoleFunctionByName(std::string_view a_name) -> SCRIPT_FUNCTION*;
		[[nodiscard]]
		static auto GetScriptFunctionByName(std::string_view a_name) -> SCRIPT_FUNCTION*;

		[[nodiscard]]
		static auto GetConsoleFunctionByShortName(std::string_view a_name) -> SCRIPT_FUNCTION*;
		[[nodiscard]]
		static auto GetScriptFunctionByShortName(std::string_view a_name) -> SCRIPT_FUNCTION*;

		// members
		const char* functionName{""};				   // 0x00
		const char* shortName{""};					   // 0x08
		REX::Enum<SCRIPT_OUTPUT, std::int32_t> output; // 0x10
		const char* helpString{""};					   // 0x18
		bool referenceFunction;						   // 0x20
		std::uint16_t paramCount;					   // 0x22
		SCRIPT_PARAMETER* parameters;				   // 0x28
		ExecuteFunctionType* executeFunction;		   // 0x30
		CompileFunctionType* compileFunction;		   // 0x38
		ConditionFunctionType* conditionFunction;	   // 0x40
		bool editorFilter;							   // 0x48
		bool invalidatesCellList;					   // 0x49
	};

	static_assert(sizeof(SCRIPT_FUNCTION) == 0x50);
}
