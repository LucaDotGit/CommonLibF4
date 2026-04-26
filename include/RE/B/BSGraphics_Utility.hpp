#pragma once

namespace RE
{
	class NiColorA;
	class NiPoint2;
	class NiPoint3;
}

namespace RE::BSGraphics::Utility
{
	void ConvertHALFToNiPoint3Stream(const std::uint16_t* a_src, NiPoint3* a_dst, std::uint32_t a_count, std::uint32_t a_stride);
	void ConvertNiPoint3ToHALFStream(const NiPoint3* a_src, std::uint16_t* a_dst, std::uint32_t a_count);

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
		std::uint32_t a_tangentXBufferStride);

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
		std::uint8_t* a_boneIndex3);
}
