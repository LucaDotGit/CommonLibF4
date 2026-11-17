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
		inline static constexpr const auto& RTTI = RTTI::IRendererResourceManager;
		inline static constexpr const auto& VTABLE = VTABLE::IRendererResourceManager;

		virtual ~IRendererResourceManager(); // 0x00

		virtual auto CreateTriShape(
			std::uint32_t a_numTriangles,
			std::uint16_t* a_indices,
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
			bool a_generatePositionData) -> BSTriShape* = 0; // 0x01
		virtual auto CreateTriShape(
			std::uint32_t a_numTriangles,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			std::uint16_t* a_indices) -> BSTriShape* = 0; // 0x02
		virtual auto CreateTriShape(
			NiStream* a_stream,
			std::uint64_t a_vertexDesc,
			std::uint32_t a_vertexCount,
			std::uint32_t a_indexCount,
			char** a_dynamicData) -> void* = 0; // 0x03
		virtual auto CreateTriShapeRendererData(
			void* a_vertexBuffer,
			std::uint64_t a_vertexDesc,
			std::uint16_t* a_indices,
			std::uint32_t a_indexCount) -> void* = 0; // 0x04
		virtual auto CreateSubIndexTriShape(
			std::uint32_t a_numTriangles,
			std::uint32_t a_numSegments,
			std::uint16_t* a_indices,
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
			REX::Float32* a_eyeData) -> BSSubIndexTriShape* = 0; // 0x05
		virtual void IncRefTriShape(void* a_rendererData) = 0;	 // 0x06
		virtual void DecRefTriShape(void* a_rendererData) = 0;	 // 0x07
		virtual auto CreateDynamicTriShape(
			std::uint32_t a_dynamicFlags,
			std::uint32_t a_numTriangles,
			std::uint16_t* a_indices,
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
			REX::Float32* a_eyeData) -> BSDynamicTriShape* = 0; // 0x08
		virtual auto CreateDynamicTriShape(
			std::uint32_t a_dynamicFlags,
			std::uint32_t a_numTriangles,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			std::uint16_t* a_indices) -> BSDynamicTriShape* = 0;	  // 0x09
		virtual void IncRefDynamicTriShape(void* a_rendererData) = 0; // 0x10
		virtual void DecRefDynamicTriShape(void* a_rendererData) = 0; // 0x11
		virtual void ConvertBSTriShapeToBSDynamicTriShape(
			NiNode* a_root,
			NiDefaultAVObjectPalette* a_objectPalette) = 0;					   // 0x12
		virtual void ApplyMaterials(NiAVObject* a_root) = 0;				   // 0x13
		virtual void SetTriShapeStreamDynamicFlags(std::uint32_t a_flags) = 0; // 0x14
		virtual auto CreateParticleShape() -> void* = 0;					   // 0x15
		virtual void IncRefParticleShape(void* a_rendererData) = 0;			   // 0x16
		virtual void DecRefParticleShape(void* a_rendererData) = 0;			   // 0x17
		virtual auto CreateLineShape(
			std::uint32_t a_numLines,
			std::uint16_t* a_indices,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			NiPoint3* a_normals,
			NiPoint3* a_binormals,
			NiPoint3* a_tangents,
			NiColorA* a_texCoords1,
			NiColorA* a_landscapeData1,
			std::uint8_t* a_skinBoneIndices,
			NiColorA* a_landscapeData2,
			NiColorA* a_skinBoneWeights,
			REX::Float32* a_eyeData) -> BSLines* = 0; // 0x18
		virtual auto CreateDynamicLineShape(
			std::uint32_t a_dynamicFlags,
			std::uint32_t a_numLines,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			std::uint16_t* a_indices) -> BSDynamicLines* = 0; // 0x19
		virtual auto CreateDynamicLineShape(
			NiStream* a_stream,
			std::uint64_t a_vertexDesc,
			std::uint32_t a_vertexCount,
			std::uint32_t a_indexCount) -> void* = 0; // 0x20
		virtual auto CreateDynamicLineShape(
			std::uint32_t a_dynamicFlags,
			std::uint32_t a_numLines,
			std::uint16_t* a_indices,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			NiPoint3* a_normals,
			NiPoint3* a_binormals,
			NiPoint3* a_tangents,
			NiColorA* a_texCoords1,
			NiColorA* a_landscapeData1,
			std::uint8_t* a_skinBoneIndices,
			NiColorA* a_landscapeData2,
			NiColorA* a_skinBoneWeights,
			REX::Float32* a_eyeData) -> BSDynamicLines* = 0;	   // 0x21
		virtual void IncRefLines(void* a_rendererData) = 0;		   // 0x22
		virtual void DecRefLines(void* a_rendererData) = 0;		   // 0x23
		virtual void IncRefDynamicLines(void* a_rendererData) = 0; // 0x24
		virtual void DecRefDynamicLines(void* a_rendererData) = 0; // 0x25
		virtual void LoadTexture(NiTexture* apTexture) = 0;		   // 0x26
		virtual void CreateStreamingTexture(
			NiTexture* a_texture,
			const void* a_userDataIn,
			void* a_userDataOut) = 0;																 // 0x27
		virtual auto ReadStreamingTextureData(NiTexture* a_texture, void* a_userDataIn) -> bool = 0; // 0x28
		virtual auto CreateStreamingTextureArraySlice(
			NiTexture* a_texture,
			const void* a_userDataIn,
			void* a_userDataOut,
			std::uint32_t a_slice) -> bool = 0; // 0x29
		virtual auto ReadStreamingTextureDataToArraySlice(
			NiTexture* a_texture,
			void* a_userDataIn,
			std::uint32_t a_slice) -> bool = 0;							// 0x30
		virtual void FinishStreamingTexture(NiTexture* a_texture) = 0;	// 0x31
		virtual void IncRefTexture(BSGraphics::Texture* a_texture) = 0; // 0x32
		virtual void DecRefTexture(BSGraphics::Texture* a_texture) = 0; // 0x33
		virtual void GetTextureWidthHeight(
			NiTexture* a_texture,
			std::uint32_t* a_width,
			std::uint32_t* a_height) = 0;										  // 0x34
		virtual auto GetTextureFormat(NiTexture* a_texture) -> std::uint32_t = 0; // 0x35
		virtual auto UpdateTextureToDesiredMipLevel(NiTexture* a_texture, std::uint32_t* a_mipLevel)
			-> bool = 0;											   // 0x36
		virtual void LoadUpgradeTextureData(NiTexture* a_texture) = 0; // 0x37
		virtual auto UpdateStreamingTextureToDesiredMipLevel(
			NiTexture* a_texture,
			std::uint32_t* a_mipLevel,
			void* a_userDataIn,
			void* a_userDataOut) -> bool = 0;								  // 0x38
		virtual void FinishStreamingTextureUpgrade(NiTexture* a_texture) = 0; // 0x39
		virtual auto CreateVertexBuffer(
			std::uint32_t* a_dataSize,
			void* a_data,
			std::uint32_t a_stride,
			std::uint64_t a_unk01) -> void* = 0;				   // 0x40
		virtual void DecRefVertexBuffer(void* a_rendererData) = 0; // 0x41
		virtual auto CreateDefaultEffectShaderProperty(bool a_vertexColors, bool a_skinned)
			-> NiShadeProperty* = 0; // 0x42
		virtual auto CreateMeshLODTriShape(
			std::uint32_t* a_levels,
			std::uint32_t a_numLevels,
			std::uint64_t a_vertexDesc,
			std::uint32_t a_vertexCount,
			std::uint32_t a_triangleCount,
			void* a_rendererData) -> BSMeshLODTriShape* = 0; // 0x43
		virtual auto CreateMeshLODTriShape(
			BSTriShape* a_triShape,
			std::uint32_t* a_levels,
			std::uint32_t a_numLevels) -> BSMeshLODTriShape* = 0; // 0x44
		virtual auto UpdateIndexBufferForInstancing(
			BSMultiStreamInstanceTriShape* a_instanceShape,
			std::uint32_t a_indexCount) -> std::uint32_t = 0; // 0x45
		virtual auto FindIntersectionsTriShapeFastPath(
			const NiPoint3* a_start,
			const NiPoint3* a_end,
			NiPick* a_pick,
			BSTriShape* a_triShape) -> bool = 0; // 0x46
		virtual void CreateTangentSpace(
			std::uint32_t a_numVertices,
			std::uint16_t* a_indices,
			std::uint32_t a_indexCount,
			NiPoint3* a_normals,
			NiPoint2* a_uvs,
			NiPoint3* a_tangents,
			NiPoint3* a_bitangents,
			NiPoint3* a_positions) = 0;																 // 0x47
		virtual auto GetShaderFrameCount() -> REX::Float32 = 0;										 // 0x48
		virtual auto GetShaderTimerDelta() -> REX::Float32 = 0;										 // 0x49
		virtual void GetFadeNodeSettings(FadeNodeSettings* a_skinned) = 0;							 // 0x50
		virtual void GetCameraVectors(NiPoint3* a_up, NiPoint3* a_right, NiPoint3* a_direction) = 0; // 0x51

		[[nodiscard]]
		static auto GetSingleton() noexcept -> IRendererResourceManager*
		{
			static const auto SINGLETON =
				REL::Relocation<IRendererResourceManager**>{ID::IRendererResourceManager::Singleton};
			return *SINGLETON;
		}
	};
}
