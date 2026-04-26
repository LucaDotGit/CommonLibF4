#pragma once

#include "RE/B/BSBatchRenderer.hpp"
#include "RE/B/BSShaderManager.hpp"
#include "RE/N/NiAlphaAccumulator.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SunOcclusionTest.hpp"

namespace RE
{
	class BSLight;
	class ShadowSceneNode;

	class __declspec(novtable) BSShaderAccumulator
		: public NiAlphaAccumulator // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShaderAccumulator };
		inline static constexpr auto VTABLE{ VTABLE::BSShaderAccumulator };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::BSShaderAccumulator };

		enum class WATER_SIDE : std::uint32_t
		{
			kAboveWater = 0,
			kBelowWater = 1
		};

		// add
		virtual void FinishAccumulatingPreResolveDepth();  // 2E
		virtual void FinishAccumulatingPostResolveDepth(); // 2F

		// members
		std::uint32_t sunPixelCount;									 // 058
		bool waitingForSunQuery;										 // 05C
		REX::Float32 percentSunOccludedStored;							 // 060
		std::array<SunOcclusionTest, 3> sunTests;						 // 068
		bool firstPerson;												 // 0B0
		bool zPrePass;													 // 0B1
		NiColorA silhouetteColor;										 // 0B4
		bool renderDecals;												 // 0C4
		BSBatchRenderer batchRenderer;									 // 0C8
		std::uint32_t currentPass;										 // 548
		std::uint32_t currentBucket;									 // 54C
		bool currentActiveA;											 // 550
		ShadowSceneNode* activeShadowSceneNode;							 // 558
		REX::Enum<BSShaderManager::RenderMode, std::int32_t> renderMode; // 560
		NiPointer<BSLight> shadowLight;									 // 568
		NiPoint3A eyePosition;											 // 570
		std::uint32_t depthPassIndex;									 // 580
	};
	static_assert(sizeof(BSShaderAccumulator) == 0x590);
}
