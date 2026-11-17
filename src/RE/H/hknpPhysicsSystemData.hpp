#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkStringPtr.hpp"

namespace RE
{
	class hknpMaterial;
	class hknpMotionProperties;
	class hknpMotionCinfo;
	class hknpBodyCinfo;
	class hknpConstraintCinfo;

	class __declspec(novtable) hknpPhysicsSystemData : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpPhysicsSystemData;
		inline static constexpr const auto& VTABLE = VTABLE::hknpPhysicsSystemData;

		~hknpPhysicsSystemData() override; // 0x00

		// members
		hkArray<hknpMaterial> materials;							   // 0x10
		hkArray<hknpMotionProperties> motionProperties;				   // 0x20
		hkArray<hknpMotionCinfo> motionCinfos;						   // 0x30
		hkArray<hknpBodyCinfo> bodyCinfos;							   // 0x40
		hkArray<hknpConstraintCinfo> constraintCinfos;				   // 0x50
		hkArray<hkRefPtr<const hkReferencedObject>> referencedObjects; // 0x60
		hkStringPtr name;											   // 0x70
	};

	static_assert(sizeof(hknpPhysicsSystemData) == 0x78);
}
