#pragma once

#include "RE/I/IRendererResourceManager.hpp"

namespace RE
{
	class __declspec(novtable) BSShaderResourceManager : public IRendererResourceManager // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSShaderResourceManager;
		inline static constexpr const auto& VTABLE = VTABLE::BSShaderResourceManager;

		~BSShaderResourceManager() override; // 0x00

		auto CreateTriShape(
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
			bool a_generatePositionData) -> BSTriShape* override; // 0x01
		auto CreateTriShape(
			std::uint32_t a_numTriangles,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			std::uint16_t* a_indices) -> BSTriShape* override; // 0x02
		auto CreateTriShape(
			NiStream* a_stream,
			std::uint64_t a_vertexDesc,
			std::uint32_t a_vertexCount,
			std::uint32_t a_indexCount,
			char** a_dynamicData) -> void* override; // 0x03
		auto CreateTriShapeRendererData(
			void* a_vertexBuffer,
			std::uint64_t a_vertexDesc,
			std::uint16_t* a_indices,
			std::uint32_t a_indexCount) -> void* override; // 0x04
		auto CreateSubIndexTriShape(
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
			REX::Float32* a_eyeData) -> BSSubIndexTriShape* override; // 0x05
		void IncRefTriShape(void* a_rendererData) override;			  // 0x06
		void DecRefTriShape(void* a_rendererData) override;			  // 0x07
		auto CreateDynamicTriShape(
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
			REX::Float32* a_eyeData) -> BSDynamicTriShape* override; // 0x08
		auto CreateDynamicTriShape(
			std::uint32_t a_dynamicFlags,
			std::uint32_t a_numTriangles,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			std::uint16_t* a_indices) -> BSDynamicTriShape* override; // 0x09
		void IncRefDynamicTriShape(void* a_rendererData) override;	  // 0x10
		void DecRefDynamicTriShape(void* a_rendererData) override;	  // 0x11
		void ConvertBSTriShapeToBSDynamicTriShape(NiNode* a_root, NiDefaultAVObjectPalette* a_objectPalette)
			override;														// 0x12
		void ApplyMaterials(NiAVObject* a_root) override;					// 0x13
		void SetTriShapeStreamDynamicFlags(std::uint32_t a_flags) override; // 0x14
		auto CreateParticleShape() -> void* override;						// 0x15
		void IncRefParticleShape(void* a_rendererData) override;			// 0x16
		void DecRefParticleShape(void* a_rendererData) override;			// 0x17
		auto CreateLineShape(
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
			REX::Float32* a_eyeData) -> BSLines* override; // 0x18
		auto CreateDynamicLineShape(
			std::uint32_t a_dynamicFlags,
			std::uint32_t a_numLines,
			std::uint32_t a_numVertices,
			NiPoint3* a_positions,
			NiPoint2* a_texCoords,
			NiColorA* a_colors,
			std::uint16_t* a_indices) -> BSDynamicLines* override; // 0x19
		auto CreateDynamicLineShape(
			NiStream* a_stream,
			std::uint64_t a_vertexDesc,
			std::uint32_t a_vertexCount,
			std::uint32_t a_indexCount) -> void* override; // 0x20
		auto CreateDynamicLineShape(
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
			REX::Float32* a_eyeData) -> BSDynamicLines* override; // 0x21
		void IncRefLines(void* a_rendererData) override;		  // 0x22
		void DecRefLines(void* a_rendererData) override;		  // 0x23
		void IncRefDynamicLines(void* a_rendererData) override;	  // 0x24
		void DecRefDynamicLines(void* a_rendererData) override;	  // 0x25
		void LoadTexture(NiTexture* apTexture) override;		  // 0x26
		void CreateStreamingTexture(NiTexture* a_texture, const void* a_userDataIn, void* a_userDataOut)
			override;																			  // 0x27
		auto ReadStreamingTextureData(NiTexture* a_texture, void* a_userDataIn) -> bool override; // 0x28
		auto CreateStreamingTextureArraySlice(
			NiTexture* a_texture,
			const void* a_userDataIn,
			void* a_userDataOut,
			std::uint32_t a_slice) -> bool override; // 0x29
		auto ReadStreamingTextureDataToArraySlice(NiTexture* a_texture, void* a_userDataIn, std::uint32_t a_slice)
			-> bool override;										 // 0x30
		void FinishStreamingTexture(NiTexture* a_texture) override;	 // 0x31
		void IncRefTexture(BSGraphics::Texture* a_texture) override; // 0x32
		void DecRefTexture(BSGraphics::Texture* a_texture) override; // 0x33
		void GetTextureWidthHeight(NiTexture* a_texture, std::uint32_t* a_width, std::uint32_t* a_height)
			override;																						   // 0x34
		auto GetTextureFormat(NiTexture* a_texture) -> std::uint32_t override;								   // 0x35
		auto UpdateTextureToDesiredMipLevel(NiTexture* a_texture, std::uint32_t* a_mipLevel) -> bool override; // 0x36
		void LoadUpgradeTextureData(NiTexture* a_texture) override;											   // 0x37
		auto UpdateStreamingTextureToDesiredMipLevel(
			NiTexture* a_texture,
			std::uint32_t* a_mipLevel,
			void* a_userDataIn,
			void* a_userDataOut) -> bool override;						   // 0x38
		void FinishStreamingTextureUpgrade(NiTexture* a_texture) override; // 0x39
		auto CreateVertexBuffer(std::uint32_t* a_dataSize, void* a_data, std::uint32_t a_stride, std::uint64_t a_unk01)
			-> void* override;									// 0x40
		void DecRefVertexBuffer(void* a_rendererData) override; // 0x41
		auto CreateDefaultEffectShaderProperty(bool a_vertexColors, bool a_skinned)
			-> NiShadeProperty* override; // 0x42
		auto CreateMeshLODTriShape(
			std::uint32_t* a_levels,
			std::uint32_t a_numLevels,
			std::uint64_t a_vertexDesc,
			std::uint32_t a_vertexCount,
			std::uint32_t a_triangleCount,
			void* a_rendererData) -> BSMeshLODTriShape* override; // 0x43
		auto CreateMeshLODTriShape(
			BSTriShape* a_triShape,
			std::uint32_t* a_levels,
			std::uint32_t a_numLevels) -> BSMeshLODTriShape* override; // 0x44
		auto UpdateIndexBufferForInstancing(
			BSMultiStreamInstanceTriShape* a_instanceShape,
			std::uint32_t a_indexCount) -> std::uint32_t override; // 0x45
		auto FindIntersectionsTriShapeFastPath(
			const NiPoint3* a_start,
			const NiPoint3* a_end,
			NiPick* a_pick,
			BSTriShape* a_triShape) -> bool override; // 0x46
		void CreateTangentSpace(
			std::uint32_t a_numVertices,
			std::uint16_t* a_indices,
			std::uint32_t a_indexCount,
			NiPoint3* a_normals,
			NiPoint2* a_uvs,
			NiPoint3* a_tangents,
			NiPoint3* a_bitangents,
			NiPoint3* a_positions) override;													  // 0x47
		auto GetShaderFrameCount() -> REX::Float32 override;									  // 0x48
		auto GetShaderTimerDelta() -> REX::Float32 override;									  // 0x49
		void GetFadeNodeSettings(FadeNodeSettings* a_skinned) override;							  // 0x50
		void GetCameraVectors(NiPoint3* a_up, NiPoint3* a_right, NiPoint3* a_direction) override; // 0x51
	};
}
