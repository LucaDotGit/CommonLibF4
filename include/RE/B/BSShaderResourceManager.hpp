#pragma once

#include "RE/I/IRendererResourceManager.hpp"

namespace RE
{
	class __declspec(novtable) BSShaderResourceManager
		: public IRendererResourceManager // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShaderResourceManager };
		inline static constexpr auto VTABLE{ VTABLE::BSShaderResourceManager };

		~BSShaderResourceManager() override; // 00

		BSTriShape* CreateTriShape(std::uint32_t a_numTriangles, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords0, NiColorA* a_texCoords1, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_colors, NiColorA* a_skinBoneWeights, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData1, NiColorA* a_landscapeData2, REX::Float32* a_eyeData, bool a_generatePositionData) override;				   // 01
		BSTriShape* CreateTriShape(std::uint32_t a_numTriangles, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, std::uint16_t* a_indices) override;																																																																						   // 02
		void* CreateTriShape(NiStream* a_stream, std::uint64_t a_vertexDesc, std::uint32_t a_vertexCount, std::uint32_t a_indexCount, char** a_dynamicData) override;																																																																													   // 03
		void* CreateTriShapeRendererData(void* a_vertexBuffer, std::uint64_t a_vertexDesc, std::uint16_t* a_indices, std::uint32_t a_indexCount) override;																																																																																   // 04
		BSSubIndexTriShape* CreateSubIndexTriShape(std::uint32_t a_numTriangles, std::uint32_t a_numSegments, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords0, NiColorA* a_texCoords1, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_colors, NiColorA* a_skinBoneWeights, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData1, NiColorA* a_landscapeData2, REX::Float32* a_eyeData) override; // 05
		void IncRefTriShape(void* a_rendererData) override;																																																																																																								   // 06
		void DecRefTriShape(void* a_rendererData) override;																																																																																																								   // 07
		BSDynamicTriShape* CreateDynamicTriShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numTriangles, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords0, NiColorA* a_texCoords1, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_colors, NiColorA* a_skinBoneWeights, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData1, NiColorA* a_landscapeData2, REX::Float32* a_eyeData) override;  // 08
		BSDynamicTriShape* CreateDynamicTriShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numTriangles, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, std::uint16_t* a_indices) override;																																																											   // 09
		void IncRefDynamicTriShape(void* a_rendererData) override;																																																																																																						   // 10
		void DecRefDynamicTriShape(void* a_rendererData) override;																																																																																																						   // 11
		void ConvertBSTriShapeToBSDynamicTriShape(NiNode* a_root, NiDefaultAVObjectPalette* a_objectPalette) override;																																																																																									   // 12
		void ApplyMaterials(NiAVObject* a_root) override;																																																																																																								   // 13
		void SetTriShapeStreamDynamicFlags(std::uint32_t a_flags) override;																																																																																																				   // 14
		void* CreateParticleShape() override;																																																																																																											   // 15
		void IncRefParticleShape(void* a_rendererData) override;																																																																																																						   // 16
		void DecRefParticleShape(void* a_rendererData) override;																																																																																																						   // 17
		BSLines* CreateLineShape(std::uint32_t a_numLines, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_texCoords1, NiColorA* a_landscapeData1, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData2, NiColorA* a_skinBoneWeights, REX::Float32* a_eyeData) override;													   // 18
		BSDynamicLines* CreateDynamicLineShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numLines, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, std::uint16_t* a_indices) override;																																																												   // 19
		void* CreateDynamicLineShape(NiStream* a_stream, std::uint64_t a_vertexDesc, std::uint32_t a_vertexCount, std::uint32_t a_indexCount) override;																																																																																	   // 20
		BSDynamicLines* CreateDynamicLineShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numLines, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_texCoords1, NiColorA* a_landscapeData1, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData2, NiColorA* a_skinBoneWeights, REX::Float32* a_eyeData) override;		   // 21
		void IncRefLines(void* a_rendererData) override;																																																																																																								   // 22
		void DecRefLines(void* a_rendererData) override;																																																																																																								   // 23
		void IncRefDynamicLines(void* a_rendererData) override;																																																																																																							   // 24
		void DecRefDynamicLines(void* a_rendererData) override;																																																																																																							   // 25
		void LoadTexture(NiTexture* apTexture) override;																																																																																																								   // 26
		void CreateStreamingTexture(NiTexture* a_texture, const void* a_userDataIn, void* a_userDataOut) override;																																																																																										   // 27
		bool ReadStreamingTextureData(NiTexture* a_texture, void* a_userDataIn) override;																																																																																																   // 28
		bool CreateStreamingTextureArraySlice(NiTexture* a_texture, const void* a_userDataIn, void* a_userDataOut, std::uint32_t a_slice) override;																																																																																		   // 29
		bool ReadStreamingTextureDataToArraySlice(NiTexture* a_texture, void* a_userDataIn, std::uint32_t a_slice) override;																																																																																							   // 30
		void FinishStreamingTexture(NiTexture* a_texture) override;																																																																																																						   // 31
		void IncRefTexture(BSGraphics::Texture* a_texture) override;																																																																																																					   // 32
		void DecRefTexture(BSGraphics::Texture* a_texture) override;																																																																																																					   // 33
		void GetTextureWidthHeight(NiTexture* a_texture, std::uint32_t* a_width, std::uint32_t* a_height) override;																																																																																										   // 34
		std::uint32_t GetTextureFormat(NiTexture* a_texture) override;																																																																																																					   // 35
		bool UpdateTextureToDesiredMipLevel(NiTexture* a_texture, std::uint32_t* a_mipLevel) override;																																																																																													   // 36
		void LoadUpgradeTextureData(NiTexture* a_texture) override;																																																																																																						   // 37
		bool UpdateStreamingTextureToDesiredMipLevel(NiTexture* a_texture, std::uint32_t* a_mipLevel, void* a_userDataIn, void* a_userDataOut) override;																																																																																   // 38
		void FinishStreamingTextureUpgrade(NiTexture* a_texture) override;																																																																																																				   // 39
		void* CreateVertexBuffer(std::uint32_t* a_dataSize, void* a_data, std::uint32_t a_stride, std::uint64_t a_unk01) override;																																																																																						   // 40
		void DecRefVertexBuffer(void* a_rendererData) override;																																																																																																							   // 41
		NiShadeProperty* CreateDefaultEffectShaderProperty(bool a_vertexColors, bool a_skinned) override;																																																																																												   // 42
		BSMeshLODTriShape* CreateMeshLODTriShape(std::uint32_t* a_levels, std::uint32_t a_numLevels, std::uint64_t a_vertexDesc, std::uint32_t a_vertexCount, std::uint32_t a_triangleCount, void* a_rendererData) override;																																																															   // 43
		BSMeshLODTriShape* CreateMeshLODTriShape(BSTriShape* a_triShape, std::uint32_t* a_levels, std::uint32_t a_numLevels) override;																																																																																					   // 44
		std::uint32_t UpdateIndexBufferForInstancing(BSMultiStreamInstanceTriShape* a_instanceShape, std::uint32_t a_indexCount) override;																																																																																				   // 45
		bool FindIntersectionsTriShapeFastPath(const NiPoint3* a_start, const NiPoint3* a_end, NiPick* a_pick, BSTriShape* a_triShape) override;																																																																																		   // 46
		void CreateTangentSpace(std::uint32_t a_numVertices, std::uint16_t* a_indices, std::uint32_t a_indexCount, NiPoint3* a_normals, NiPoint2* a_uvs, NiPoint3* a_tangents, NiPoint3* a_bitangents, NiPoint3* a_positions) override;																																																													   // 47
		REX::Float32 GetShaderFrameCount() override;																																																																																																									   // 48
		REX::Float32 GetShaderTimerDelta() override;																																																																																																									   // 49
		void GetFadeNodeSettings(FadeNodeSettings* a_skinned) override;																																																																																																					   // 50
		void GetCameraVectors(NiPoint3* a_up, NiPoint3* a_right, NiPoint3* a_direction) override;																																																																																														   // 51
	};
}
