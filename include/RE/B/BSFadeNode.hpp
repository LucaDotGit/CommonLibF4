#pragma once

#include "RE/B/BSShaderPropertyLightData.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSGeometry;
	class FlattenedGeometryData;

	class __declspec(novtable) BSFadeNode
		: public NiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSFadeNode };
		inline static constexpr auto VTABLE{ VTABLE::BSFadeNode };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSFadeNode };

		class FlattenedGeometryData
		{
		public:
			// members
			NiBound bound;					// 00
			NiPointer<BSGeometry> geometry; // 10
			std::uint32_t flags;			// 18
		};
		static_assert(sizeof(FlattenedGeometryData) == 0x20);

		// members
		BSShaderPropertyLightData lightData;			 // 140
		BSTArray<FlattenedGeometryData> geomArray;		 // 168
		BSTAlignedArray<NiBound, 0x10> mergedGeomBounds; // 180
		REX::Float32 nearDistSqr;						 // 198
		REX::Float32 farDistSqr;						 // 19C
		REX::Float32 currentFade;						 // 1A0
		REX::Float32 currentDecalFade;					 // 1A4
		REX::Float32 boundRadius;						 // 1A8
		REX::Float32 timeSinceUpdate;					 // 1AC
		std::int32_t frameCounter;						 // 1B0
		REX::Float32 previousMaxA;						 // 1B4
		REX::Float32 currentShaderLODLevel;				 // 1B8
		REX::Float32 previousShaderLODLevel;			 // 1BC
	};
	static_assert(sizeof(BSFadeNode) == 0x1C0);
}
