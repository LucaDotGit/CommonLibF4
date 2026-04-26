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

	class __declspec(novtable) hknpPhysicsSystemData
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpPhysicsSystemData };
		inline static constexpr auto VTABLE{ VTABLE::hknpPhysicsSystemData };

		~hknpPhysicsSystemData() override; // 00

		// members
		hkArray<hknpMaterial> materials;							   // 10
		hkArray<hknpMotionProperties> motionProperties;				   // 20
		hkArray<hknpMotionCinfo> motionCinfos;						   // 30
		hkArray<hknpBodyCinfo> bodyCinfos;							   // 40
		hkArray<hknpConstraintCinfo> constraintCinfos;				   // 50
		hkArray<hkRefPtr<const hkReferencedObject>> referencedObjects; // 60
		hkStringPtr name;											   // 70
	};
	static_assert(sizeof(hknpPhysicsSystemData) == 0x78);
}
