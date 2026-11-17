#pragma once

#include "RE/B/BSGraphics_RenderTarget.hpp"
#include "RE/N/NiRect.hpp"

namespace RE::BSGraphics
{
	class RendererWindow
	{
	public:
		template <class T = std::int32_t>
		[[nodiscard]]
		auto GetWindowRect() const -> NiRect<T>
		{
			return {
				static_cast<T>(windowX),
				static_cast<T>(windowX + windowWidth),
				static_cast<T>(windowY),
				static_cast<T>(windowY + windowHeight)
			};
		}

		// members
		REX::W32::HWND hwnd;				 // 0x00
		std::int32_t windowX;				 // 0x08
		std::int32_t windowY;				 // 0x0C
		std::int32_t windowWidth;			 // 0x10
		std::int32_t windowHeight;			 // 0x14
		REX::W32::IDXGISwapChain* swapChain; // 0x18
		RenderTarget swapChainRenderTarget;	 // 0x20
	};

	static_assert(sizeof(RendererWindow) == 0x50);

	[[nodiscard]]
	inline auto GetCurrentRendererWindow() noexcept -> RendererWindow*
	{
		static const auto CURRENT_RENDER_WINDOW =
			REL::Relocation<RendererWindow**>{ID::BSGraphics::CurrentRendererWindow};
		return *CURRENT_RENDER_WINDOW;
	}
}
