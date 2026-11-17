#pragma once

#include "RE/B/BSShaderPropertyLightData.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSGeometry;
	class FlattenedGeometryData;

	class __declspec(novtable) BSFadeNode : public NiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSFadeNode;
		inline static constexpr const auto& VTABLE = VTABLE::BSFadeNode;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSFadeNode;

		class FlattenedGeometryData
		{
		public:
			// members
			NiBound bound;					// 0x00
			NiPointer<BSGeometry> geometry; // 0x10
			std::uint32_t flags;			// 0x18
		};

		static_assert(sizeof(FlattenedGeometryData) == 0x20);

		// members
		BSShaderPropertyLightData lightData;			 // 0x140
		BSTArray<FlattenedGeometryData> geomArray;		 // 0x168
		BSTAlignedArray<NiBound, 0x10> mergedGeomBounds; // 0x180
		REX::Float32 nearDistSqr;						 // 0x198
		REX::Float32 farDistSqr;						 // 0x19C
		REX::Float32 currentFade;						 // 0x1A0
		REX::Float32 currentDecalFade;					 // 0x1A4
		REX::Float32 boundRadius;						 // 0x1A8
		REX::Float32 timeSinceUpdate;					 // 0x1AC
		std::int32_t frameCounter;						 // 0x1B0
		REX::Float32 previousMaxA;						 // 0x1B4
		REX::Float32 currentShaderLODLevel;				 // 0x1B8
		REX::Float32 previousShaderLODLevel;			 // 0x1BC
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSFadeNode) == 0x1C0);
#else
	static_assert(sizeof(BSFadeNode) == 0x1A0);
#endif
}
