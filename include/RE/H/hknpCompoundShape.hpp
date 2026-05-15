#pragma once

#include "RE/H/hkAabb.hpp"
#include "RE/H/hkFreeListArray.hpp"
#include "RE/H/hknpCompositeShape.hpp"
#include "RE/H/hknpShapeInstance.hpp"
#include "RE/H/hknpShapeInstanceId.hpp"

namespace RE
{
	class __declspec(novtable) hknpCompoundShape
		: public hknpCompositeShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpCompoundShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpCompoundShape };

		~hknpCompoundShape() override; // 00

		// add
		virtual bool UpdateAabb() = 0;														 // 1E
		virtual void GetInstanceAabb(hknpShapeInstanceId a_id, hkAabb& a_outAabb) const = 0; // 1F

		// members
		hkFreeListArray<hknpShapeInstance, hknpShapeInstanceId, 8, hknpShapeInstance> instances; // 60
		hkAabb aabb;																			 // 80
		bool isMutable;																			 // A0
		std::array<std::byte, 0x10> mutationSignals;											 // A1 - TODO: hknpShapeSignals
	};
	static_assert(sizeof(hknpCompoundShape) == 0xC0);
}
