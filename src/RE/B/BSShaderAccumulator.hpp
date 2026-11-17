#pragma once

#include "RE/B/BSBatchRenderer.hpp"
#include "RE/B/BSShaderManager.hpp"
#include "RE/N/NiAlphaAccumulator.hpp"
#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SunOcclusionTest.hpp"

namespace RE
{
	class BSLight;
	class ShadowSceneNode;

	class __declspec(novtable) BSShaderAccumulator : public NiAlphaAccumulator // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSShaderAccumulator;
		inline static constexpr const auto& VTABLE = VTABLE::BSShaderAccumulator;
		inline static constexpr auto Ni_RTTI = Ni_RTTI::BSShaderAccumulator;

		enum class WATER_SIDE : std::uint32_t
		{
			AboveWater = 0,
			BelowWater = 1
		};

		// add
		virtual void FinishAccumulatingPreResolveDepth();  // 0x2E
		virtual void FinishAccumulatingPostResolveDepth(); // 0x2F

		// members
		std::uint32_t sunPixelCount;									 // 0x058
		bool waitingForSunQuery;										 // 0x05C
		REX::Float32 percentSunOccludedStored;							 // 0x060
		std::array<SunOcclusionTest, 3> sunTests;						 // 0x068
		bool firstPerson;												 // 0x0B0
		bool zPrePass;													 // 0x0B1
		NiColorA silhouetteColor;										 // 0x0B4
		bool renderDecals;												 // 0x0C4
		BSBatchRenderer batchRenderer;									 // 0x0C8
		std::uint32_t currentPass;										 // 0x548
		std::uint32_t currentBucket;									 // 0x54C
		bool currentActiveA;											 // 0x550
		ShadowSceneNode* activeShadowSceneNode;							 // 0x558
		REX::Enum<BSShaderManager::RenderMode, std::int32_t> renderMode; // 0x560
		NiPointer<BSLight> shadowLight;									 // 0x568
		NiPoint3A eyePosition;											 // 0x570
		std::uint32_t depthPassIndex;									 // 0x580
	};

	static_assert(sizeof(BSShaderAccumulator) == 0x590);
}
