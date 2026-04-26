#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPlane.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSMultiBoundAABB;
	class NiAVObject;
	class TESWaterDisplacement;
	class TESWaterNormals;
	class TESWaterReflections;

	class __declspec(novtable) TESWaterObject
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWaterObject };
		inline static constexpr auto VTABLE{ VTABLE::TESWaterObject };

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kVisible = 1 << 0,
			kLOD = 1 << 1,
			kNoDisplacements = 1 << 2,
			kProceduralWater = 1 << 3
		};

		// members
		NiPlane waterPlane;									   // 10
		NiPointer<NiAVObject> waterObject;					   // 20
		NiPointer<NiAVObject> waterRipplesObject;			   // 28
		TESWaterForm* waterType;							   // 30
		NiPointer<TESWaterReflections> waterReflections;	   // 38
		NiPointer<TESWaterNormals> waterNormals;			   // 40
		NiPointer<TESWaterDisplacement> waterDisplacement;	   // 48
		BSTArray<NiPointer<BSMultiBoundAABB>> multiBoundShape; // 50
		REX::EnumSet<Flags, std::uint8_t> flags;			   // 68
	};
	static_assert(sizeof(TESWaterObject) == 0x70);
}
