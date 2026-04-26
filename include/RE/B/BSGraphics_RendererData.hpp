#pragma once

#include "RE/B/BSCriticalSection.hpp"
#include "RE/B/BSGraphics_CubeMapRenderTarget.hpp"
#include "RE/B/BSGraphics_DepthStencilTarget.hpp"
#include "RE/B/BSGraphics_RendererWindow.hpp"

namespace RE::BSGraphics
{
	class RendererShadowState;
	class BSD3DResourceCreator;

	class RendererData
	{
	public:
		[[nodiscard]] static RendererData* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<RendererData**>{ ID::BSGraphics::RenderData::Singleton };
			return *SINGLETON;
		}

		// members
		RendererShadowState* shadowState;						 // 0000
		BSD3DResourceCreator* resourceCreator;					 // 0008
		std::uint32_t adapter;									 // 0010
		REX::W32::DXGI_RATIONAL desiredRefreshRate;				 // 0014
		REX::W32::DXGI_RATIONAL actualRefreshRate;				 // 001C
		REX::W32::DXGI_MODE_SCALING scaleMode;					 // 0024
		REX::W32::DXGI_MODE_SCANLINE_ORDER scanlineMode;		 // 0028
		std::int32_t fullScreen;								 // 002C
		bool appFullScreen;										 // 0030
		bool borderlessWindow;									 // 0031
		bool vsync;												 // 0032
		bool initialized;										 // 0033
		bool requestWindowSizeChange;							 // 0034
		std::uint32_t newWidth;									 // 0038
		std::uint32_t newHeight;								 // 003C
		std::uint32_t presentInterval;							 // 0040
		REX::W32::ID3D11Device* device;							 // 0048
		REX::W32::ID3D11DeviceContext* context;					 // 0050
		std::array<RendererWindow, 32> renderWindow;			 // 0058
		std::array<RenderTarget, 101> renderTargets;			 // 0A58
		std::array<DepthStencilTarget, 13> depthStencilTargets;	 // 1D48
		std::array<CubeMapRenderTarget, 2> cubeMapRenderTargets; // 2500
		mutable BSCriticalSection rendererLock;					 // 2580
		const char* className;									 // 25A8
		void* instance;											 // 25B0
		bool nvapiEnabled;										 // 25B8
	};
	static_assert(sizeof(RendererData) == 0x25C0);
}
