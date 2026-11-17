#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hknpBodyId.hpp"

namespace RE
{
	class hknpPhysicsSystemData;
	class hknpWorld;

	class __declspec(novtable) hknpPhysicsSystem : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpPhysicsSystem;
		inline static constexpr const auto& VTABLE = VTABLE::hknpPhysicsSystem;

		~hknpPhysicsSystem() override; // 0x00

		// members
		hkRefPtr<const hknpPhysicsSystemData> data; // 0x10
		hkRefPtr<hknpWorld> world;					// 0x18
		hkArray<hknpBodyId> bodyIds;				// 0x20
		hkArray<hknpBodyId> constraintIds;			// 0x30
	};

	static_assert(sizeof(hknpPhysicsSystem) == 0x40);
}
