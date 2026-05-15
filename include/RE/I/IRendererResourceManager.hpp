#pragma once

namespace RE::BSGraphics
{
	class Texture;
}

namespace RE
{
	class BSDynamicLines;
	class BSDynamicTriShape;
	class BSLines;
	class BSMeshLODTriShape;
	class BSMultiStreamInstanceTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class FadeNodeSettings;
	class NiAVObject;
	class NiColorA;
	class NiDefaultAVObjectPalette;
	class NiNode;
	class NiPick;
	class NiPoint2;
	class NiPoint3;
	class NiShadeProperty;
	class NiStream;
	class NiTexture;

	class __declspec(novtable) IRendererResourceManager
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IRendererResourceManager };
		inline static constexpr auto VTABLE{ VTABLE::IRendererResourceManager };

		virtual ~IRendererResourceManager(); // 00

		virtual BSTriShape* CreateTriShape(std::uint32_t a_numTriangles, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords0, NiColorA* a_texCoords1, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_colors, NiColorA* a_skinBoneWeights, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData1, NiColorA* a_landscapeData2, REX::Float32* a_eyeData, bool a_generatePositionData) = 0;				  // 01
		virtual BSTriShape* CreateTriShape(std::uint32_t a_numTriangles, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, std::uint16_t* a_indices) = 0;																																																																						  // 02
		virtual void* CreateTriShape(NiStream* a_stream, std::uint64_t a_vertexDesc, std::uint32_t a_vertexCount, std::uint32_t a_indexCount, char** a_dynamicData) = 0;																																																																													  // 03
		virtual void* CreateTriShapeRendererData(void* a_vertexBuffer, std::uint64_t a_vertexDesc, std::uint16_t* a_indices, std::uint32_t a_indexCount) = 0;																																																																																  // 04
		virtual BSSubIndexTriShape* CreateSubIndexTriShape(std::uint32_t a_numTriangles, std::uint32_t a_numSegments, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords0, NiColorA* a_texCoords1, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_colors, NiColorA* a_skinBoneWeights, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData1, NiColorA* a_landscapeData2, REX::Float32* a_eyeData) = 0; // 05
		virtual void IncRefTriShape(void* a_rendererData) = 0;																																																																																																								  // 06
		virtual void DecRefTriShape(void* a_rendererData) = 0;																																																																																																								  // 07
		virtual BSDynamicTriShape* CreateDynamicTriShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numTriangles, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords0, NiColorA* a_texCoords1, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_colors, NiColorA* a_skinBoneWeights, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData1, NiColorA* a_landscapeData2, REX::Float32* a_eyeData) = 0;  // 08
		virtual BSDynamicTriShape* CreateDynamicTriShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numTriangles, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, std::uint16_t* a_indices) = 0;																																																											  // 09
		virtual void IncRefDynamicTriShape(void* a_rendererData) = 0;																																																																																																						  // 10
		virtual void DecRefDynamicTriShape(void* a_rendererData) = 0;																																																																																																						  // 11
		virtual void ConvertBSTriShapeToBSDynamicTriShape(NiNode* a_root, NiDefaultAVObjectPalette* a_objectPalette) = 0;																																																																																									  // 12
		virtual void ApplyMaterials(NiAVObject* a_root) = 0;																																																																																																								  // 13
		virtual void SetTriShapeStreamDynamicFlags(std::uint32_t a_flags) = 0;																																																																																																				  // 14
		virtual void* CreateParticleShape() = 0;																																																																																																											  // 15
		virtual void IncRefParticleShape(void* a_rendererData) = 0;																																																																																																							  // 16
		virtual void DecRefParticleShape(void* a_rendererData) = 0;																																																																																																							  // 17
		virtual BSLines* CreateLineShape(std::uint32_t a_numLines, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_texCoords1, NiColorA* a_landscapeData1, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData2, NiColorA* a_skinBoneWeights, REX::Float32* a_eyeData) = 0;													  // 18
		virtual BSDynamicLines* CreateDynamicLineShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numLines, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, std::uint16_t* a_indices) = 0;																																																												  // 19
		virtual void* CreateDynamicLineShape(NiStream* a_stream, std::uint64_t a_vertexDesc, std::uint32_t a_vertexCount, std::uint32_t a_indexCount) = 0;																																																																																	  // 20
		virtual BSDynamicLines* CreateDynamicLineShape(std::uint32_t a_dynamicFlags, std::uint32_t a_numLines, std::uint16_t* a_indices, std::uint32_t a_numVertices, NiPoint3* a_positions, NiPoint2* a_texCoords, NiColorA* a_colors, NiPoint3* a_normals, NiPoint3* a_binormals, NiPoint3* a_tangents, NiColorA* a_texCoords1, NiColorA* a_landscapeData1, std::uint8_t* a_skinBoneIndices, NiColorA* a_landscapeData2, NiColorA* a_skinBoneWeights, REX::Float32* a_eyeData) = 0;		  // 21
		virtual void IncRefLines(void* a_rendererData) = 0;																																																																																																									  // 22
		virtual void DecRefLines(void* a_rendererData) = 0;																																																																																																									  // 23
		virtual void IncRefDynamicLines(void* a_rendererData) = 0;																																																																																																							  // 24
		virtual void DecRefDynamicLines(void* a_rendererData) = 0;																																																																																																							  // 25
		virtual void LoadTexture(NiTexture* apTexture) = 0;																																																																																																									  // 26
		virtual void CreateStreamingTexture(NiTexture* a_texture, const void* a_userDataIn, void* a_userDataOut) = 0;																																																																																										  // 27
		virtual bool ReadStreamingTextureData(NiTexture* a_texture, void* a_userDataIn) = 0;																																																																																																  // 28
		virtual bool CreateStreamingTextureArraySlice(NiTexture* a_texture, const void* a_userDataIn, void* a_userDataOut, std::uint32_t a_slice) = 0;																																																																																		  // 29
		virtual bool ReadStreamingTextureDataToArraySlice(NiTexture* a_texture, void* a_userDataIn, std::uint32_t a_slice) = 0;																																																																																								  // 30
		virtual void FinishStreamingTexture(NiTexture* a_texture) = 0;																																																																																																						  // 31
		virtual void IncRefTexture(BSGraphics::Texture* a_texture) = 0;																																																																																																						  // 32
		virtual void DecRefTexture(BSGraphics::Texture* a_texture) = 0;																																																																																																						  // 33
		virtual void GetTextureWidthHeight(NiTexture* a_texture, std::uint32_t* a_width, std::uint32_t* a_height) = 0;																																																																																										  // 34
		virtual std::uint32_t GetTextureFormat(NiTexture* a_texture) = 0;																																																																																																					  // 35
		virtual bool UpdateTextureToDesiredMipLevel(NiTexture* a_texture, std::uint32_t* a_mipLevel) = 0;																																																																																													  // 36
		virtual void LoadUpgradeTextureData(NiTexture* a_texture) = 0;																																																																																																						  // 37
		virtual bool UpdateStreamingTextureToDesiredMipLevel(NiTexture* a_texture, std::uint32_t* a_mipLevel, void* a_userDataIn, void* a_userDataOut) = 0;																																																																																	  // 38
		virtual void FinishStreamingTextureUpgrade(NiTexture* a_texture) = 0;																																																																																																				  // 39
		virtual void* CreateVertexBuffer(std::uint32_t* a_dataSize, void* a_data, std::uint32_t a_stride, std::uint64_t a_unk01) = 0;																																																																																						  // 40
		virtual void DecRefVertexBuffer(void* a_rendererData) = 0;																																																																																																							  // 41
		virtual NiShadeProperty* CreateDefaultEffectShaderProperty(bool a_vertexColors, bool a_skinned) = 0;																																																																																												  // 42
		virtual BSMeshLODTriShape* CreateMeshLODTriShape(std::uint32_t* a_levels, std::uint32_t a_numLevels, std::uint64_t a_vertexDesc, std::uint32_t a_vertexCount, std::uint32_t a_triangleCount, void* a_rendererData) = 0;																																																																  // 43
		virtual BSMeshLODTriShape* CreateMeshLODTriShape(BSTriShape* a_triShape, std::uint32_t* a_levels, std::uint32_t a_numLevels) = 0;																																																																																					  // 44
		virtual std::uint32_t UpdateIndexBufferForInstancing(BSMultiStreamInstanceTriShape* a_instanceShape, std::uint32_t a_indexCount) = 0;																																																																																				  // 45
		virtual bool FindIntersectionsTriShapeFastPath(const NiPoint3* a_start, const NiPoint3* a_end, NiPick* a_pick, BSTriShape* a_triShape) = 0;																																																																																			  // 46
		virtual void CreateTangentSpace(std::uint32_t a_numVertices, std::uint16_t* a_indices, std::uint32_t a_indexCount, NiPoint3* a_normals, NiPoint2* a_uvs, NiPoint3* a_tangents, NiPoint3* a_bitangents, NiPoint3* a_positions) = 0;																																																													  // 47
		virtual REX::Float32 GetShaderFrameCount() = 0;																																																																																																										  // 48
		virtual REX::Float32 GetShaderTimerDelta() = 0;																																																																																																										  // 49
		virtual void GetFadeNodeSettings(FadeNodeSettings* a_skinned) = 0;																																																																																																					  // 50
		virtual void GetCameraVectors(NiPoint3* a_up, NiPoint3* a_right, NiPoint3* a_direction) = 0;																																																																																														  // 51

		[[nodiscard]] static IRendererResourceManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<IRendererResourceManager**>{ ID::IRendererResourceManager::Singleton };
			return *SINGLETON;
		}
	};
}
