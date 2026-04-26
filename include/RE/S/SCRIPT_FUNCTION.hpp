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
		using ConditionFunctionType = bool(ConditionCheckParams& a_data, void* a_param2, void* a_param1, REX::Float32& a_returnValue);
		using CompileFunctionType = bool(std::uint16_t a_paramCount, const SCRIPT_PARAMETER* a_parameters, SCRIPT_LINE* a_scriptLine, ScriptCompileData* a_compileData);
		using ExecuteFunctionType = bool(const SCRIPT_PARAMETER* a_parameters, const char* a_compiledParams, TESObjectREFR* a_refObject, TESObjectREFR* a_container, Script* a_script, ScriptLocals* a_scriptLocals, REX::Float32& a_returnValue, std::uint32_t& a_offset);

		class StringChunk;
		class IntegerChunk;

		class Chunk
		{
		public:
			[[nodiscard]] IntegerChunk* AsInteger() noexcept { return reinterpret_cast<IntegerChunk*>(this); }
			[[nodiscard]] StringChunk* AsString() noexcept { return reinterpret_cast<StringChunk*>(this); }

			[[nodiscard]] const IntegerChunk* AsInteger() const noexcept { return reinterpret_cast<const IntegerChunk*>(this); }
			[[nodiscard]] const StringChunk* AsString() const noexcept { return reinterpret_cast<const StringChunk*>(this); }
		};

		class IntegerChunk
			: public Chunk // 00
		{
		public:
			[[nodiscard]] SCRIPT_FUNCTION::Chunk* GetNext() { return static_cast<Chunk*>(this + 1); }
			[[nodiscard]] const SCRIPT_FUNCTION::Chunk* GetNext() const { return static_cast<const Chunk*>(this + 1); }

			[[nodiscard]] std::int32_t GetInteger() const { return *std::bit_cast<std::int32_t*>(std::bit_cast<std::uintptr_t>(this) + 1); }

			// members
			char magic;			// 00
			std::int32_t value; // 01
		};
		static_assert(sizeof(IntegerChunk) == 0x08);

		class StringChunk
			: public Chunk // 00
		{
		public:
			[[nodiscard]] SCRIPT_FUNCTION::Chunk* GetNext() { return reinterpret_cast<Chunk*>(static_cast<char*>(str) + length); }
			[[nodiscard]] const SCRIPT_FUNCTION::Chunk* GetNext() const { return reinterpret_cast<const Chunk*>(static_cast<const char*>(str) + length); }

			[[nodiscard]] std::string_view GetString() const { return length ? std::string_view{ static_cast<const char*>(str), length } : ""sv; }

			// members
			std::uint16_t length; // 00
			char str[0];		  // 02 - NOLINT(modernize-avoid-c-arrays)
		};
		static_assert(sizeof(StringChunk) == 0x02);

		class ScriptData
		{
		public:
			[[nodiscard]] SCRIPT_FUNCTION::Chunk* GetChunk() { return reinterpret_cast<Chunk*>(this + 1); }
			[[nodiscard]] const SCRIPT_FUNCTION::Chunk* GetChunk() const { return reinterpret_cast<const Chunk*>(this + 1); }

			[[nodiscard]] SCRIPT_FUNCTION::IntegerChunk* GetIntegerChunk() { return GetChunk()->AsInteger(); }
			[[nodiscard]] const SCRIPT_FUNCTION::IntegerChunk* GetIntegerChunk() const { return GetChunk()->AsInteger(); }

			[[nodiscard]] SCRIPT_FUNCTION::StringChunk* GetStringChunk() { return GetChunk()->AsString(); }
			[[nodiscard]] const SCRIPT_FUNCTION::StringChunk* GetStringChunk() const { return GetChunk()->AsString(); }

			// members
			std::uint16_t opcode;	 // 00
			std::uint16_t chunkSize; // 02
			std::uint16_t numParams; // 04
		};
		static_assert(sizeof(ScriptData) == 0x06);

		[[nodiscard]] static auto GetConsoleFunctions() -> std::span<SCRIPT_FUNCTION>;
		[[nodiscard]] static auto GetScriptFunctions() -> std::span<SCRIPT_FUNCTION>;

		[[nodiscard]] static SCRIPT_FUNCTION* GetConsoleFunctionByName(std::string_view a_name);
		[[nodiscard]] static SCRIPT_FUNCTION* GetScriptFunctionByName(std::string_view a_name);

		[[nodiscard]] static SCRIPT_FUNCTION* GetConsoleFunctionByShortName(std::string_view a_name);
		[[nodiscard]] static SCRIPT_FUNCTION* GetScriptFunctionByShortName(std::string_view a_name);

		// members
		const char* functionName{ "" };				   // 00
		const char* shortName{ "" };				   // 08
		REX::Enum<SCRIPT_OUTPUT, std::int32_t> output; // 10
		const char* helpString{ "" };				   // 18
		bool referenceFunction;						   // 20
		std::uint16_t paramCount;					   // 22
		SCRIPT_PARAMETER* parameters;				   // 28
		ExecuteFunctionType* executeFunction;		   // 30
		CompileFunctionType* compileFunction;		   // 38
		ConditionFunctionType* conditionFunction;	   // 40
		bool editorFilter;							   // 48
		bool invalidatesCellList;					   // 49
	};
	static_assert(sizeof(SCRIPT_FUNCTION) == 0x50);
}
