#include "RE/B/BSGraphics_Utility.hpp"

namespace RE::BSGraphics::Utility
{
	void ConvertHALFToNiPoint3Stream(const std::uint16_t* a_src, NiPoint3* a_dst, std::uint32_t a_count, std::uint32_t a_stride)
	{
		using FuncType = decltype(&BSGraphics::Utility::ConvertHALFToNiPoint3Stream);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Utility::ConvertHALFToNiPoint3Stream };
		std::invoke(FUNC, a_src, a_dst, a_count, a_stride);
	}

	void ConvertNiPoint3ToHALFStream(const NiPoint3* a_src, std::uint16_t* a_dst, std::uint32_t a_count)
	{
		using FuncType = decltype(&BSGraphics::Utility::ConvertNiPoint3ToHALFStream);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Utility::ConvertNiPoint3ToHALFStream };
		std::invoke(FUNC, a_src, a_dst, a_count);
	}

	std::uint64_t PackVertexData(
		std::uint32_t a_numVertices,
		NiPoint3* a_positions,
		NiPoint2* a_texCoords0,
		NiColorA* a_texCoords1,
		NiPoint3* a_normals,
		NiPoint3* a_binormals,
		NiPoint3* a_tangents,
		NiColorA* a_colors,
		NiColorA* a_skinBoneWeights,
		std::uint8_t* a_skinBoneIndices,
		NiColorA* a_landscapeData1,
		NiColorA* a_landscapeData2,
		REX::Float32* a_eyeData,
		std::byte* a_buffer,
		std::uint32_t* a_bufferSize,
		std::uint16_t* a_vertexMap,
		std::uint32_t a_dynamicFlags,
		std::uint16_t* a_tangentXBuffer,
		std::uint32_t a_tangentXBufferStride)
	{
		using FuncType = decltype(&BSGraphics::Utility::PackVertexData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Utility::PackVertexData };
		return std::invoke(FUNC, a_numVertices, a_positions, a_texCoords0, a_texCoords1, a_normals, a_binormals, a_tangents, a_colors, a_skinBoneWeights, a_skinBoneIndices, a_landscapeData1, a_landscapeData2, a_eyeData, a_buffer, a_bufferSize, a_vertexMap, a_dynamicFlags, a_tangentXBuffer, a_tangentXBufferStride);
	}

	void UnpackVertexData(
		const std::uint8_t* a_vertices,
		std::uint16_t a_index,
		std::uint64_t a_vertexDesc,
		NiPoint3* a_position,
		NiPoint2* a_texCoord0,
		NiPoint2* a_texCoord1,
		NiPoint3* a_normal,
		NiPoint3* a_binormal,
		NiPoint3* a_tangent,
		NiColorA* a_color,
		NiColorA* a_skinBoneWeights,
		std::uint8_t* a_boneIndex0,
		std::uint8_t* a_boneIndex1,
		std::uint8_t* a_boneIndex2,
		std::uint8_t* a_boneIndex3)
	{
		using FuncType = decltype(&BSGraphics::Utility::UnpackVertexData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Utility::UnpackVertexData };
		std::invoke(FUNC, a_vertices, a_index, a_vertexDesc, a_position, a_texCoord0, a_texCoord1, a_normal, a_binormal, a_tangent, a_color, a_skinBoneWeights, a_boneIndex0, a_boneIndex1, a_boneIndex2, a_boneIndex3);
	}
}
