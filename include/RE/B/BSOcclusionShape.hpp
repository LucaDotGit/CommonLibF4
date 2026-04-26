#pragma once

#include "RE/B/BSMultiBoundShape.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiObject.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class __declspec(novtable) BSOcclusionShape
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSOcclusionShape };
		inline static constexpr auto VTABLE{ VTABLE::BSOcclusionShape };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSOcclusionShape };

		~BSOcclusionShape() override; // 00

		// add
		virtual bool GetIsPlane() const = 0; // 28
		virtual bool GetIsBox() const = 0;	 // 29

		// members
		NiPoint3A center;							  // 10
		NiMatrix3 rotation;							  // 20
		BSMultiBoundShape::BSMBCullResult cullResult; // 50
		bool dirtyVertices;							  // 54
	};
	static_assert(sizeof(BSOcclusionShape) == 0x60);
}
