#pragma once

#include "RE/B/BSGraphics_ViewData.hpp"
#include "RE/N/NiPoint3.hpp"

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
		std::int32_t dirty;																  // 0x000
		std::int32_t vsTextureDirty;													  // 0x004
		std::int32_t vsTextureStateDirty;												  // 0x008
		std::int32_t dsTextureDirty;													  // 0x00C
		std::int32_t dsTextureStateDirty;												  // 0x010
		std::int32_t psTextureDirty;													  // 0x014
		std::int32_t psTextureStateDirty;												  // 0x018
		std::int32_t csTextureDirty;													  // 0x01C
		std::int32_t csTextureStateDirty;												  // 0x020
		std::int32_t csUAVDirty;														  // 0x024
		bool readOnlyDepth;																  // 0x028
		bool readOnlyStencil;															  // 0x029
		bool usesVertexIndexBuffer;														  // 0x02A
		std::array<std::int32_t, 8> renderTargets;										  // 0x02C
		std::int32_t depthStencil;														  // 0x04C
		std::int32_t depthStencilSlice;													  // 0x050
		std::int32_t cubeMapRenderTarget;												  // 0x054
		std::int32_t cubeMapRenderTargetView;											  // 0x058
		std::array<REX::Enum<SetRenderTargetMode, std::int32_t>, 8> setRenderTargetMode;  // 0x05C
		REX::Enum<SetRenderTargetMode, std::int32_t> setDepthStencilMode;				  // 0x07C
		REX::Enum<SetRenderTargetMode, std::int32_t> setCubeMapRenderTargetMode;		  // 0x080
		std::int32_t currentRenderTargetIndex;											  // 0x084
		std::int32_t currentDepthStencilTargetIndex;									  // 0x088
		std::int32_t currentCubeMapRenderTargetIndex;									  // 0x08C
		REX::W32::D3D11_VIEWPORT viewport;												  // 0x090
		REX::Enum<DepthStencilDepthMode, std::int32_t> depthStencilDepthMode;			  // 0x0A8
		REX::Enum<DepthStencilStencilMode, std::int32_t> depthStencilStencilMode;		  // 0x0AC
		REX::Enum<DepthStencilExtraMode, std::int32_t> depthStencilExMode;				  // 0x0B0
		std::uint32_t stencilRef;														  // 0x0B4
		REX::Enum<RasterStateFillMode, std::int32_t> rasterStateFillMode;				  // 0x0B8
		REX::Enum<RasterStateCullMode, std::int32_t> rasterStateCullMode;				  // 0x0BC
		REX::Enum<RasterStateDepthBiasMode, std::int32_t> rasterStateDepthBiasMode;		  // 0x0C0
		REX::Enum<RasterStateScissorMode, std::int32_t> rasterStateScissorMode;			  // 0x0C4
		REX::Enum<AlphaBlendMode, std::int32_t> alphaBlendMode;							  // 0x0C8
		REX::Enum<AlphaBlendAlphaToCoverage, std::int32_t> alphaBlendAlphaToCoverage;	  // 0x0CC
		REX::Enum<AlphaBlendWriteMode, std::int32_t> alphaBlendWriteMode;				  // 0x0D0
		bool alphaTestEnabled;															  // 0x0D4
		REX::Float32 alphaTestRef;														  // 0x0D8
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> vsTextureAddressMode; // 0x0DC
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> vsTextureFilterMode;	  // 0x11C
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> vsTexture;					  // 0x160
		std::array<std::uint32_t, 16> vsTextureMinLodMode;								  // 0x1E0
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> dsTextureAddressMode; // 0x220
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> dsTextureFilterMode;	  // 0x260
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> dsTexture;					  // 0x2A0
		std::array<std::uint32_t, 16> dsTextureMinLodMode;								  // 0x320
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> psTextureAddressMode; // 0x360
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> psTextureFilterMode;	  // 0x3A0
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> psTexture;					  // 0x3E0
		std::array<std::uint32_t, 16> psTextureMinLodMode;								  // 0x460
		std::array<REX::Enum<TextureAddressMode, std::int32_t>, 16> csTextureAddressMode; // 0x4A0
		std::array<REX::Enum<TextureFilterMode, std::int32_t>, 16> csTextureFilterMode;	  // 0x4E0
		std::array<REX::W32::ID3D11ShaderResourceView*, 16> csTexture;					  // 0x520
		std::array<std::uint32_t, 16> csTextureMinLodMode;								  // 0x5A0
		std::array<REX::W32::ID3D11UnorderedAccessView*, 8> csUav;						  // 0x5E0
		std::array<REX::W32::ID3D11Buffer*, 3> vertexConstantBuffer;					  // 0x620
		std::array<REX::W32::ID3D11Buffer*, 3> pixelConstantBuffer;						  // 0x638
		std::array<REX::W32::ID3D11Buffer*, 3> domainConstantBuffer;					  // 0x650
		std::array<REX::W32::ID3D11Buffer*, 3> hullConstantBuffer;						  // 0x668
		std::uint64_t vertexDesc;														  // 0x680
		VertexShader* currentVertexShader;												  // 0x688
		DomainShader* currentDomainShader;												  // 0x690
		HullShader* currentHullShader;													  // 0x698
		PixelShader* currentPixelShader;												  // 0x6A0
		REX::Enum<REX::W32::D3D_PRIMITIVE_TOPOLOGY, std::int32_t> topology;				  // 0x6A8
		NiPoint3A posAdjust;															  // 0x6B0
		NiPoint3A previousPosAdjust;													  // 0x6C0
		ViewData cameraData;															  // 0x6D0
		std::array<REX::Float32, 4> clearColor;											  // 0x8E0
		std::array<REX::Float32, 4> previousClearColor;									  // 0x8F0
		std::uint8_t clearStencil;														  // 0x900
	};

	static_assert(sizeof(RendererShadowState) == 0x910);
}
