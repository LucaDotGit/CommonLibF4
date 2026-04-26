#pragma once

#include "RE/B/BSGraphics_RenderTarget.hpp"
#include "RE/N/NiRect.hpp"

namespace RE::BSGraphics
{
	class RendererWindow
	{
	public:
		template <class T = std::int32_t>
		[[nodiscard]] NiRect<T> GetWindowRect() const
		{
			return {
				static_cast<T>(windowX),
				static_cast<T>(windowX + windowWidth),
				static_cast<T>(windowY),
				static_cast<T>(windowY + windowHeight)
			};
		}

		// members
		REX::W32::HWND hwnd;				 // 00
		std::int32_t windowX;				 // 08
		std::int32_t windowY;				 // 0C
		std::int32_t windowWidth;			 // 10
		std::int32_t windowHeight;			 // 14
		REX::W32::IDXGISwapChain* swapChain; // 18
		RenderTarget swapChainRenderTarget;	 // 20
	};
	static_assert(sizeof(RendererWindow) == 0x50);

	[[nodiscard]] inline RendererWindow* GetCurrentRendererWindow()
	{
		static const auto CURRENT_RENDER_WINDOW = REL::Relocation<RendererWindow**>{ ID::BSGraphics::CurrentRendererWindow };
		return *CURRENT_RENDER_WINDOW;
	}
}
