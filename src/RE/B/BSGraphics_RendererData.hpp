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
		[[nodiscard]]
		static auto GetSingleton() noexcept -> RendererData*
		{
			static const auto SINGLETON = REL::Relocation<RendererData**>(ID::BSGraphics::RenderData::Singleton);
			return *SINGLETON;
		}

		// members
		RendererShadowState* shadowState;						 // 0x0000
		BSD3DResourceCreator* resourceCreator;					 // 0x0008
		std::uint32_t adapter;									 // 0x0010
		REX::W32::DXGI_RATIONAL desiredRefreshRate;				 // 0x0014
		REX::W32::DXGI_RATIONAL actualRefreshRate;				 // 0x001C
		REX::W32::DXGI_MODE_SCALING scaleMode;					 // 0x0024
		REX::W32::DXGI_MODE_SCANLINE_ORDER scanlineMode;		 // 0x0028
		std::int32_t fullScreen;								 // 0x002C
		bool appFullScreen;										 // 0x0030
		bool borderlessWindow;									 // 0x0031
		bool vsync;												 // 0x0032
		bool initialized;										 // 0x0033
		bool requestWindowSizeChange;							 // 0x0034
		std::uint32_t newWidth;									 // 0x0038
		std::uint32_t newHeight;								 // 0x003C
		std::uint32_t presentInterval;							 // 0x0040
		REX::W32::ID3D11Device* device;							 // 0x0048
		REX::W32::ID3D11DeviceContext* context;					 // 0x0050
		std::array<RendererWindow, 32> renderWindow;			 // 0x0058
		std::array<RenderTarget, 101> renderTargets;			 // 0x0A58
		std::array<DepthStencilTarget, 13> depthStencilTargets;	 // 0x1D48
		std::array<CubeMapRenderTarget, 2> cubeMapRenderTargets; // 0x2500
		mutable BSCriticalSection rendererLock;					 // 0x2580
		const char* className;									 // 0x25A8
		void* instance;											 // 0x25B0
		bool nvapiEnabled;										 // 0x25B8
	};

	static_assert(sizeof(RendererData) == 0x25C0);
}
