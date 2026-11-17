#pragma once

#include "RE/N/NiPointer.hpp"
#include "RE/S/SkyObject.hpp"

namespace RE
{
	class BSShaderAccumulator;
	class BSTriShape;
	class NiBillboardNode;
	class NiDirectionalLight;

	class __declspec(novtable) Sun : public SkyObject
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Sun;
		inline static constexpr const auto& VTABLE = VTABLE::Sun;

		~Sun() override; // 0x00

		// members
		NiPointer<NiBillboardNode> sunBaseNode;		   // 0x10
		NiPointer<NiBillboardNode> sunGlareNode;	   // 0x18
		NiPointer<BSTriShape> sunBase;				   // 0x20
		NiPointer<BSTriShape> sunQuery;				   // 0x28
		NiPointer<BSTriShape> sunGlare;				   // 0x30
		NiPointer<NiDirectionalLight> light;		   // 0x38
		NiPointer<NiDirectionalLight> cloudLight;	   // 0x40
		REX::Float32 glareScale;					   // 0x48
		bool doOcclusionTests;						   // 0x4C
		NiPointer<BSShaderAccumulator> sunAccumulator; // 0x50
	};

	static_assert(sizeof(Sun) == 0x58);
}
