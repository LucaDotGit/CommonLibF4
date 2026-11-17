#pragma once

#include "RE/H/hkAabb.hpp"
#include "RE/H/hkFreeListArray.hpp"
#include "RE/H/hknpCompositeShape.hpp"
#include "RE/H/hknpShapeInstance.hpp"
#include "RE/H/hknpShapeInstanceId.hpp"

namespace RE
{
	class __declspec(novtable) hknpCompoundShape : public hknpCompositeShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpCompoundShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpCompoundShape;

		~hknpCompoundShape() override; // 0x00

		// add
		virtual auto UpdateAabb() -> bool = 0;												 // 0x1E
		virtual void GetInstanceAabb(hknpShapeInstanceId a_id, hkAabb& a_outAabb) const = 0; // 0x1F

		// members
		hkFreeListArray<hknpShapeInstance, hknpShapeInstanceId, 8, hknpShapeInstance> instances; // 0x60
		hkAabb aabb;																			 // 0x80
		bool isMutable;																			 // 0xA0
		std::array<std::byte, 0x10> mutationSignals; // 0xA1 - To-Do: hknpShapeSignals
	};

	static_assert(sizeof(hknpCompoundShape) == 0xC0);
}
