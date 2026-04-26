#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hknpBodyId.hpp"

namespace RE
{
	class hknpPhysicsSystemData;
	class hknpWorld;

	class __declspec(novtable) hknpPhysicsSystem
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpPhysicsSystem };
		inline static constexpr auto VTABLE{ VTABLE::hknpPhysicsSystem };

		~hknpPhysicsSystem() override; // 00

		// members
		hkRefPtr<const hknpPhysicsSystemData> data; // 10
		hkRefPtr<hknpWorld> world;					// 18
		hkArray<hknpBodyId> bodyIds;				// 20
		hkArray<hknpBodyId> constraintIds;			// 30
	};
	static_assert(sizeof(hknpPhysicsSystem) == 0x40);
}
