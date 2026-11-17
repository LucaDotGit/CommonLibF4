#pragma once

#include "RE/B/BSMultiBoundShape.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiObject.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class __declspec(novtable) BSOcclusionShape : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSOcclusionShape;
		inline static constexpr const auto& VTABLE = VTABLE::BSOcclusionShape;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSOcclusionShape;

		~BSOcclusionShape() override; // 0x00

		// add
		virtual auto GetIsPlane() const -> bool = 0; // 0x28
		virtual auto GetIsBox() const -> bool = 0;	 // 0x29

		// members
		NiPoint3A center;							  // 0x10
		NiMatrix3 rotation;							  // 0x20
		BSMultiBoundShape::BSMBCullResult cullResult; // 0x50
		bool dirtyVertices;							  // 0x54
	};

	static_assert(sizeof(BSOcclusionShape) == 0x60);
}
