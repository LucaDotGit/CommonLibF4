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

		[[nodiscard]] static RenderTargetManager& GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<RenderTargetManager*>{ ID::BSGraphics::RenderTargetManager::Singleton };
			return *SINGLETON;
		}

		void SetEnableDynamicResolution(bool a_enableDynamicResolution)
		{
			using FuncType = decltype(&RenderTargetManager::SetEnableDynamicResolution);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGraphics::RenderTargetManager::SetEnableDynamicResolution };
			std::invoke(FUNC, this, a_enableDynamicResolution);
		}

		// members
		std::array<RenderTargetProperties, 100> renderTargetDataArray;			   // 000
		std::array<DepthStencilTargetProperties, 12> depthStencilTargetDataArray;  // C80
		std::array<CubeMapRenderTargetProperties, 1> cubeMapRenderTargetDataArray; // DA0
		std::array<std::uint32_t, 100> renderTargetIDs;							   // DC4
		std::array<std::uint32_t, 12> depthStencilTargetIDs;					   // F54
		std::array<std::uint32_t, 1> cubeMapRenderTargetIDs;					   // F84
		REX::Float32 dynamicWidthRatio;											   // F88
		REX::Float32 dynamicHeightRatio;										   // F8C
		REX::Float32 lowestWidthRatio;											   // F90
		REX::Float32 lowestHeightRatio;											   // F94
		REX::Float32 ratioIncreasePerSeconds;									   // F98
		REX::Float32 ratioDecreasePerSeconds;									   // F9C
		REX::Float32 movementDelta;												   // FA0
		bool increaseResolution;												   // FA4
		bool freezeResolution;													   // FA5
		bool updateResolutionOnlyWhenMoving;									   // FA6
		bool useDynamicResolutionViewportAsDefaultViewport;						   // FA7
		bool isDynamicResolutionCurrentlyActivated;								   // FA8
		std::uint32_t nbFramePause;												   // FAC
		std::uint32_t nbFramesSinceLastIncrease;								   // FB0
		BSTAtomicValue<std::uint32_t> dynamicResolutionDisabled;				   // FB4
		CreateType create;														   // FB8
	};
	static_assert(sizeof(RenderTargetManager) == 0xFC0);
}
