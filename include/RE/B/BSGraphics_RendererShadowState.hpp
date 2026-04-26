#pragma once

#include "RE/B/BSGraphics_ViewData.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE::BSGraphics
{
	enum class AlphaBlendAlphaToCoverage : std::int32_t;
	enum class AlphaBlendMode : std::int32_t;
	enum class AlphaBlendWriteMode : std::int32_t;
	enum class DepthStencilDepthMode : std::int32_t;
	enum class DepthStencilExtraMode : std::int32_t;
	enum class DepthStencilStencilMode : std::int32_t;
	enum class RasterStateCullMode : std::int32_t;
	enum class RasterStateDepthBiasMode : std::int32_t;
	enum class RasterStateFillMode : std::int32_t;
	enum class RasterStateScissorMode : std::int32_t;
	enum class SetRenderTargetMode : std::int32_t;
	enum class TextureAddressMode : std::int32_t;
	enum class TextureFilterMode : std::int32_t;

	class DomainShader;
	class HullShader;
	class PixelShader;
	class VertexShader;

	class RendererShadowState
	{
	public:
		// members
		std::int32_t dirty;																  // 000
		std::int32_t vsTextureDirty;													  // 004
		std::int32_t vsTextureStateDirty;												  // 008
		std::int32_t dsTextureDirty;													  // 00C
		std::int32_t dsTextureStateDirty;												  // 010
		std::int32_t psTextureDirty;													  // 014
		std::int32_t psTextureStateDirty;												  // 018
		std::int32_t csTextureDirty;													  // 01C
		std::int32_t csTextureStateDirty;												  // 020
		std::int32_t csUAVDirty;														  // 024
		bool readOnlyDepth;																  // 028
		bool readOnlyStencil;															  // 029
		bool usesVertexIndexBuffer;														  // 02A
		std::array<std::int32_t, 8> renderTargets;										  // 02C
		std::int32_t depthStencil;														  // 04C
		std::int32_t depthStencilSlice;													  // 050
		std::int32_t cubeMapRenderTarget;												  // 054
		std::int32_t cubeMapRenderTargetView;											  // 058
		std::array<REX::Enum<SetRenderTargetMode, std::int32_t>, 8> setRenderTargetMode;  // 05C
		REX::Enum<SetRenderTargetMode, std::int32_t> setDepthStencilMode;				  // 07C
		REX::Enum<SetRenderTargetMode, std::int32_t> setCubeMapRenderTargetMode;		  // 080
		std::int32_t currentRenderTargetIndex;											  // 084
		std::int32_t currentDepthStencilTargetIndex;									  // 088
		std::int32_t currentCubeMapRenderTargetIndex;									  // 08C
		REX::W32::D3D11_VIEWPORT viewport;												  // 090
		REX::Enum<DepthStencilDepthMode, std::int32_t> depthStencilDepthMode;			  // 0A8
		REX::Enum<DepthStencilStencilMode, std::int32_t> depthStencilStencilMode;		  // 0AC
		REX::Enum<DepthStencilExtraMode, std::int32_t> depthStencilExMode;				  // 0B0
		std::uint32_t stencilRef;														  // 0B4
		REX::Enum<RasterStateFillMode, std::int32_t> rasterStateFillMode;				  // 0B8
		REX::Enum<RasterStateCullMode, std::int32_t> rasterStateCullMode;				  // 0BC
		REX::Enum<RasterStateDepthBiasMode, std::int32_t> rasterStateDepthBiasMode;		  // 0C0
		REX::Enum<RasterStateScissorMode, std::int32_t> rasterStateScissorMode;			  // 0C4
		REX::Enum<AlphaBlendMode, std::int32_t> alphaBlendMode;							  // 0C8
		REX::Enum<AlphaBlendAlphaToCoverage, std::int32_t> alphaBlendAlphaToCoverage;	  // 0CC
		REX::Enum<AlphaBlendWriteMode, std::int32_t> alphaBlendWriteMode;				  // 0D0
		bool alphaTestEnabled;															  // 0D4
		REX::Float32 alphaTestRef;														  // 0D8
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> vsTextureAddressMode; // 0DC
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> vsTextureFilterMode;	  // 11C
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> vsTexture;					  // 160
		std::array<std::uint32_t, 16> vsTextureMinLodMode;								  // 1E0
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> dsTextureAddressMode; // 220
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> dsTextureFilterMode;	  // 260
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> dsTexture;					  // 2A0
		std::array<std::uint32_t, 16> dsTextureMinLodMode;								  // 320
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> psTextureAddressMode; // 360
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> psTextureFilterMode;	  // 3A0
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> psTexture;					  // 3E0
		std::array<std::uint32_t, 16> psTextureMinLodMode;								  // 460
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> csTextureAddressMode; // 4A0
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> csTextureFilterMode;	  // 4E0
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> csTexture;					  // 520
		std::array<std::uint32_t, 16> csTextureMinLodMode;								  // 5A0
		std::array<REX::W32::ID3D11UnorderedAccessView*, 8> csUav;						  // 5E0
		std::array<REX::W32::ID3D11Buffer*, 3> vertexConstantBuffer;					  // 620
		std::array<REX::W32::ID3D11Buffer*, 3> pixelConstantBuffer;						  // 638
		std::array<REX::W32::ID3D11Buffer*, 3> domainConstantBuffer;					  // 650
		std::array<REX::W32::ID3D11Buffer*, 3> hullConstantBuffer;						  // 668
		std::uint64_t vertexDesc;														  // 680
		VertexShader* currentVertexShader;												  // 688
		DomainShader* currentDomainShader;												  // 690
		HullShader* currentHullShader;													  // 698
		PixelShader* currentPixelShader;												  // 6A0
		REX::Enum<REX::W32::D3D_PRIMITIVE_TOPOLOGY, std::int32_t> topology;				  // 6A8
		NiPoint3A posAdjust;															  // 6B0
		NiPoint3A previousPosAdjust;													  // 6C0
		ViewData cameraData;															  // 6D0
		std::array<REX::Float32, 4> clearColor;											  // 8E0
		std::array<REX::Float32, 4> previousClearColor;									  // 8F0
		std::uint8_t clearStencil;														  // 900
	};
	static_assert(sizeof(RendererShadowState) == 0x910);
}
