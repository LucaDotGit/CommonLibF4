#pragma once

#include "RE/B/BSGraphics_RendererData.hpp"

namespace RE::BSGraphics
{
	class Buffer;

	class Renderer
	{
	public:
		using ResetRenderTargetsType = void (*)();

		void IncRef(Buffer* a_vertexBuffer)
		{
			using FuncType = decltype(&BSGraphics::Renderer::IncRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Renderer::IncRef };
			FUNC(this, a_vertexBuffer);
		}

		void DecRef(Buffer* a_vertexBuffer)
		{
			using FuncType = decltype(&BSGraphics::Renderer::DecRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Renderer::DecRef };
			FUNC(this, a_vertexBuffer);
		}

		void Begin(std::uint32_t a_windowID)
		{
			using FuncType = decltype(&BSGraphics::Renderer::Begin);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Renderer::Begin };
			FUNC(this, a_windowID);
		}

		void End()
		{
			using FuncType = decltype(&BSGraphics::Renderer::End);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::Renderer::End };
			FUNC(this);
		}

		// members
		bool skipNextPresent;						// 00
		ResetRenderTargetsType* resetRenderTargets; // 08
		RendererData data;							// 10
	};
	static_assert(sizeof(Renderer) == 0x25D0);
}
