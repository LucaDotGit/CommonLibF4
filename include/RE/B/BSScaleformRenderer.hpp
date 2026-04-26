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

	class BSScaleformRenderer
		: public BSTEventSource<SFRendererInitializedEvent> // 00
	{
	public:
		void Initialize()
		{
			using FuncType = decltype(&BSScaleformRenderer::Initialize);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScaleformRenderer::Initialize };
			FUNC(this);
		}

		// members
		::Scaleform::Ptr<::Scaleform::Render::Renderer2D> renderer;			  // 058
		::Scaleform::Ptr<::Scaleform::Render::HAL> renderConfig;			  // 060
		::Scaleform::Ptr<::Scaleform::Render::TextureManager> textureManager; // 068
		std::array<::Scaleform::Render::RenderTarget*, 100> renderTargets;	  // 070
		bool initialized;													  // 390
	};
	static_assert(sizeof(BSScaleformRenderer) == 0x398);
}
