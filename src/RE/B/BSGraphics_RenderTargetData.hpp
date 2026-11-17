#pragma once

#include "RE/B/BSGraphics_CubeMapRenderTargetProperties.hpp"
#include "RE/B/BSGraphics_DepthStencilTargetProperties.hpp"
#include "RE/B/BSGraphics_RenderTargetProperties.hpp"
#include "RE/B/BSTAtomicValue.hpp"

namespace RE::BSGraphics
{
	class RenderTargetManager
	{
	public:
		using CreateType = void (*)();

		[[nodiscard]]
		static auto GetSingleton() noexcept -> RenderTargetManager*
		{
			static const auto SINGLETON =
				REL::Relocation<RenderTargetManager*>{ID::BSGraphics::RenderTargetManager::Singleton};
			return SINGLETON.get();
		}

		void SetEnableDynamicResolution(bool a_enableDynamicResolution)
		{
			using FuncType = decltype(&RenderTargetManager::SetEnableDynamicResolution);
			static const auto FUNC =
				REL::Relocation<FuncType>{ID::BSGraphics::RenderTargetManager::SetEnableDynamicResolution};
			std::invoke(FUNC, this, a_enableDynamicResolution);
		}

		// members
		std::array<RenderTargetProperties, 100> renderTargetDataArray;			   // 0x000
		std::array<DepthStencilTargetProperties, 12> depthStencilTargetDataArray;  // 0xC80
		std::array<CubeMapRenderTargetProperties, 1> cubeMapRenderTargetDataArray; // 0xDA0
		std::array<std::uint32_t, 100> renderTargetIDs;							   // 0xDC4
		std::array<std::uint32_t, 12> depthStencilTargetIDs;					   // 0xF54
		std::array<std::uint32_t, 1> cubeMapRenderTargetIDs;					   // 0xF84
		REX::Float32 dynamicWidthRatio;											   // 0xF88
		REX::Float32 dynamicHeightRatio;										   // 0xF8C
		REX::Float32 lowestWidthRatio;											   // 0xF90
		REX::Float32 lowestHeightRatio;											   // 0xF94
		REX::Float32 ratioIncreasePerSeconds;									   // 0xF98
		REX::Float32 ratioDecreasePerSeconds;									   // 0xF9C
		REX::Float32 movementDelta;												   // 0xFA0
		bool increaseResolution;												   // 0xFA4
		bool freezeResolution;													   // 0xFA5
		bool updateResolutionOnlyWhenMoving;									   // 0xFA6
		bool useDynamicResolutionViewportAsDefaultViewport;						   // 0xFA7
		bool isDynamicResolutionCurrentlyActivated;								   // 0xFA8
		std::uint32_t nbFramePause;												   // 0xFAC
		std::uint32_t nbFramesSinceLastIncrease;								   // 0xFB0
		BSTAtomicValue<std::uint32_t> dynamicResolutionDisabled;				   // 0xFB4
		CreateType create;														   // 0xFB8
	};

	static_assert(sizeof(RenderTargetManager) == 0xFC0);
}
