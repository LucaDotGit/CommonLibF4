#pragma once

#include "REX/W32/D3D.hpp"

namespace REX::W32
{
	struct ID3DBlob;
	struct ID3DInclude;
	struct ID3D10Effect;
	struct ID3D11FunctionLinkingGraph;
	struct ID3D11Linker;
	struct ID3D11Module;
}

namespace REX::W32
{
	enum D3D_BLOB_PART : std::int32_t
	{
		D3D_BLOB_INPUT_SIGNATURE_BLOB,
		D3D_BLOB_OUTPUT_SIGNATURE_BLOB,
		D3D_BLOB_INPUT_AND_OUTPUT_SIGNATURE_BLOB,
		D3D_BLOB_PATCH_CONSTANT_SIGNATURE_BLOB,
		D3D_BLOB_ALL_SIGNATURE_BLOB,
		D3D_BLOB_DEBUG_INFO,
		D3D_BLOB_LEGACY_SHADER,
		D3D_BLOB_XNA_PREPASS_SHADER,
		D3D_BLOB_XNA_SHADER,
		D3D_BLOB_PDB,
		D3D_BLOB_PRIVATE_DATA,
		D3D_BLOB_ROOT_SIGNATURE,
		D3D_BLOB_DEBUG_NAME,
		D3D_BLOB_TEST_ALTERNATE_SHADER = 0x8000,
		D3D_BLOB_TEST_COMPILE_DETAILS,
		D3D_BLOB_TEST_COMPILE_PERF,
		D3D_BLOB_TEST_COMPILE_REPORT
	};

	enum D3D_DISASM_FLAGS : std::uint32_t
	{
		D3D_DISASM_ENABLE_COLOR_CODE = 0x1,
		D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS = 0x2,
		D3D_DISASM_ENABLE_INSTRUCTION_NUMBERING = 0x4,
		D3D_DISASM_ENABLE_INSTRUCTION_CYCLE = 0x8,
		D3D_DISASM_DISABLE_DEBUG_INFO = 0x10,
		D3D_DISASM_ENABLE_INSTRUCTION_OFFSET = 0x20,
		D3D_DISASM_INSTRUCTION_ONLY = 0x40,
		D3D_DISASM_PRINT_HEX_LITERALS = 0x80
	};

	enum D3DCOMPILE_EFFECT : std::int32_t
	{
		D3DCOMPILE_EFFECT_CHILD_EFFECT = 0x1,
		D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS = 0x2
	};

	enum D3DCOMPILE_FLAGS : std::uint32_t
	{
		D3DCOMPILE_DEBUG = 0x1,
		D3DCOMPILE_SKIP_VALIDATION = 0x2,
		D3DCOMPILE_SKIP_OPTIMIZATION = 0x4,
		D3DCOMPILE_PACK_MATRIX_ROW_MAJOR = 0x8,
		D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR = 0x10,
		D3DCOMPILE_PARTIAL_PRECISION = 0x20,
		D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT = 0x40,
		D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT = 0x80,
		D3DCOMPILE_NO_PRESHADER = 0x100,
		D3DCOMPILE_AVOID_FLOW_CONTROL = 0x200,
		D3DCOMPILE_PREFER_FLOW_CONTROL = 0x400,
		D3DCOMPILE_ENABLE_STRICTNESS = 0x800,
		D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY = 0x1000,
		D3DCOMPILE_IEEE_STRICTNESS = 0x2000,
		D3DCOMPILE_OPTIMIZATION_LEVEL0 = 0x4000,
		D3DCOMPILE_OPTIMIZATION_LEVEL1 = 0x0,
		D3DCOMPILE_OPTIMIZATION_LEVEL2 = 0xC000,
		D3DCOMPILE_OPTIMIZATION_LEVEL3 = 0x8000,
		D3DCOMPILE_RESERVED16 = 0x10000,
		D3DCOMPILE_RESERVED17 = 0x20000,
		D3DCOMPILE_WARNINGS_ARE_ERRORS = 0x40000,
		D3DCOMPILE_RESOURCES_MAY_ALIAS = 0x80000,
		D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES = 0x100000,
		D3DCOMPILE_ALL_RESOURCES_BOUND = 0x200000,
		D3DCOMPILE_DEBUG_NAME_FOR_SOURCE = 0x400000,
		D3DCOMPILE_DEBUG_NAME_FOR_BINARY = 0x800000
	};

	enum D3DCOMPILE_FLAGS2 : std::int32_t
	{
		D3DCOMPILE_FLAGS2_FORCE_ROOT_SIGNATURE_LATEST = 0x0,
		D3DCOMPILE_FLAGS2_FORCE_ROOT_SIGNATURE_1_0 = 0x10,
		D3DCOMPILE_FLAGS2_FORCE_ROOT_SIGNATURE_1_1 = 0x20
	};

	enum D3DCOMPILE_SECDATA_FLAGS : std::uint32_t
	{
		D3DCOMPILE_SECDATA_MERGE_UAV_SLOTS = 0x1,
		D3DCOMPILE_SECDATA_PRESERVE_TEMPLATE_SLOTS = 0x2,
		D3DCOMPILE_SECDATA_REQUIRE_TEMPLATE_MATCH = 0x4
	};

	enum D3DCOMPILER_STRIP_FLAGS : std::uint32_t
	{
		D3DCOMPILER_STRIP_REFLECTION_DATA = 0x1,
		D3DCOMPILER_STRIP_DEBUG_INFO = 0x2,
		D3DCOMPILER_STRIP_TEST_BLOBS = 0x4,
		D3DCOMPILER_STRIP_PRIVATE_DATA = 0x8,
		D3DCOMPILER_STRIP_ROOT_SIGNATURE = 0x10,
		D3DCOMPILER_STRIP_FORCE_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}

namespace REX::W32
{
	struct D3D_SHADER_DATA
	{
		const void* bytecode;
		std::size_t bytecodeLength;
	};
}

namespace REX::W32
{
	inline constexpr auto D3D_COMPILE_STANDARD_FILE_INCLUDE{ static_cast<HANDLE_WRAPPER<ID3DInclude*>>(1) };
	inline constexpr auto D3D_COMPRESS_SHADER_KEEP_ALL_PARTS{ 0x00000001ui32 };
	inline constexpr auto D3D_GET_INST_OFFSETS_INCLUDE_NON_EXECUTABLE{ 0x00000001ui32 };
}

namespace REX::W32
{
	HRESULT D3DCompile(const void* a_srcData, std::size_t a_srcDataSize, const char* a_sourceName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, const char* a_entrypoint, const char* a_target, std::uint32_t a_flags1, std::uint32_t a_flags2, ID3DBlob** a_code, ID3DBlob** a_errorMsgs) noexcept;
	HRESULT D3DCompile2(const void* a_srcData, std::size_t a_srcDataSize, const char* a_sourceName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, const char* a_entrypoint, const char* a_target, std::uint32_t a_flags1, std::uint32_t a_flags2, std::uint32_t a_secondaryDataFlags, const void* a_secondaryData, std::size_t a_secondaryDataSize, ID3DBlob** a_code, ID3DBlob** a_errorMsgs) noexcept;
	HRESULT D3DCompileFromFile(const wchar_t* a_fileName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, const char* a_entrypoint, const char* a_target, std::uint32_t a_flags1, std::uint32_t a_flags2, ID3DBlob** a_code, ID3DBlob** a_errorMsgs) noexcept;
	HRESULT D3DCompressShaders(std::uint32_t a_numShaders, D3D_SHADER_DATA* a_shaderData, std::uint32_t a_flags, ID3DBlob** a_compressedData) noexcept;
	HRESULT D3DCreateBlob(std::size_t a_size, ID3DBlob** a_blob) noexcept;
	HRESULT D3DCreateFunctionLinkingGraph(std::uint32_t a_flags, ID3D11FunctionLinkingGraph** a_functionLinkingGraph) noexcept;
	HRESULT D3DCreateLinker(ID3D11Linker** a_linker) noexcept;
	HRESULT D3DDecompressShaders(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_numShaders, std::uint32_t a_startIndex, std::uint32_t* a_indices, std::uint32_t a_flags, ID3DBlob** a_shaders, std::uint32_t* a_totalShaders) noexcept;
	HRESULT D3DDisassemble(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_flags, const char* a_comments, ID3DBlob** a_disassembly) noexcept;
	HRESULT D3DDisassemble10Effect(ID3D10Effect* a_effect, std::uint32_t a_flags, ID3DBlob** a_disassembly) noexcept;
	HRESULT D3DDisassembleRegion(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_flags, const char* a_comments, std::size_t a_startByteOffset, std::size_t a_numInsts, std::size_t* a_finishByteOffset, ID3DBlob** a_disassembly) noexcept;
	HRESULT D3DGetBlobPart(const void* a_srcData, std::size_t a_srcDataSize, D3D_BLOB_PART a_partType, std::uint32_t a_flags, ID3DBlob** a_part) noexcept;
	HRESULT D3DGetDebugInfo(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_debugInfo) noexcept;
	HRESULT D3DGetInputSignatureBlob(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_signatureBlob) noexcept;
	HRESULT D3DGetInputAndOutputSignatureBlob(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_signatureBlob) noexcept;
	HRESULT D3DGetOutputSignatureBlob(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_signatureBlob) noexcept;
	HRESULT D3DGetTraceInstructionOffsets(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_flags, std::size_t a_startInstIndex, std::size_t a_numInsts, std::size_t* a_offsets, std::size_t* a_totalInsts) noexcept;
	HRESULT D3DLoadModule(const void* a_srcData, std::size_t a_srcDataSize, ID3D11Module** a_module) noexcept;
	HRESULT D3DPreprocess(const void* a_srcData, std::size_t a_srcDataSize, const char* a_sourceName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, ID3DBlob** a_codeText, ID3DBlob** a_errorMsgs) noexcept;
	HRESULT D3DReadFileToBlob(const wchar_t* a_fileName, ID3DBlob** a_contents) noexcept;
	HRESULT D3DReflect(const void* a_srcData, std::size_t a_srcDataSize, const IID& a_iid, void** a_reflector) noexcept;
	HRESULT D3DReflectLibrary(const void* a_srcData, std::size_t a_srcDataSize, const IID& a_iid, void** a_reflector) noexcept;
	HRESULT D3DSetBlobPart(const void* a_srcData, std::size_t a_srcDataSize, D3D_BLOB_PART a_partType, std::uint32_t a_flags, const void* a_part, std::size_t a_partSize, ID3DBlob** a_newShader) noexcept;
	HRESULT D3DStripShader(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_stripFlags, ID3DBlob** a_strippedBlob) noexcept;
	HRESULT D3DWriteBlobToFile(ID3DBlob* a_blob, const wchar_t* a_fileName, bool a_overwrite) noexcept;
}
