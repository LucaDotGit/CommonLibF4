#pragma once

#include "RE/N/NiPointer.hpp"
#include "RE/S/SkyObject.hpp"

namespace RE
{
	class BSShaderAccumulator;
	class BSTriShape;
	class NiBillboardNode;
	class NiDirectionalLight;

	class __declspec(novtable) Sun
		: public SkyObject
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Sun };
		inline static constexpr auto VTABLE{ VTABLE::Sun };

		~Sun() override; // 00

		// members
		NiPointer<NiBillboardNode> sunBaseNode;		   // 10
		NiPointer<NiBillboardNode> sunGlareNode;	   // 18
		NiPointer<BSTriShape> sunBase;				   // 20
		NiPointer<BSTriShape> sunQuery;				   // 28
		NiPointer<BSTriShape> sunGlare;				   // 30
		NiPointer<NiDirectionalLight> light;		   // 38
		NiPointer<NiDirectionalLight> cloudLight;	   // 40
		REX::Float32 glareScale;					   // 48
		bool doOcclusionTests;						   // 4C
		NiPointer<BSShaderAccumulator> sunAccumulator; // 50
	};
	static_assert(sizeof(Sun) == 0x58);
}
