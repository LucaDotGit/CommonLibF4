#pragma once

#include "RE/B/BSTEvent.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::Render
{
	class HAL;
	class Renderer2D;
	class RenderTarget;
	class TextureManager;
}

namespace RE
{
	class SFRendererInitializedEvent;

	class BSScaleformRenderer : public BSTEventSource<SFRendererInitializedEvent> // 0x00
	{
	public:
		void Initialize()
		{
			using FuncType = decltype(&BSScaleformRenderer::Initialize);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSScaleformRenderer::Initialize);
			std::invoke(FUNC, this);
		}

		// members
		Scaleform::Ptr<Scaleform::Render::Renderer2D> renderer;			  // 0x058
		Scaleform::Ptr<Scaleform::Render::HAL> renderConfig;			  // 0x060
		Scaleform::Ptr<Scaleform::Render::TextureManager> textureManager; // 0x068
		std::array<Scaleform::Render::RenderTarget*, 100> renderTargets;  // 0x070
		bool initialized;												  // 0x390
	};

	static_assert(sizeof(BSScaleformRenderer) == 0x398);
}
