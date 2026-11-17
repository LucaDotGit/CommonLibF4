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

	class __declspec(novtable) TESWaterObject : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWaterObject;
		inline static constexpr const auto& VTABLE = VTABLE::TESWaterObject;

		enum class Flags : std::uint8_t
		{
			None = 0,
			Visible = 1 << 0,
			LOD = 1 << 1,
			NoDisplacements = 1 << 2,
			ProceduralWater = 1 << 3
		};

		// members
		NiPlane waterPlane;									   // 0x10
		NiPointer<NiAVObject> waterObject;					   // 0x20
		NiPointer<NiAVObject> waterRipplesObject;			   // 0x28
		TESWaterForm* waterType;							   // 0x30
		NiPointer<TESWaterReflections> waterReflections;	   // 0x38
		NiPointer<TESWaterNormals> waterNormals;			   // 0x40
		NiPointer<TESWaterDisplacement> waterDisplacement;	   // 0x48
		BSTArray<NiPointer<BSMultiBoundAABB>> multiBoundShape; // 0x50
		REX::EnumSet<Flags, std::uint8_t> flags;			   // 0x68
	};

	static_assert(sizeof(TESWaterObject) == 0x70);
}
