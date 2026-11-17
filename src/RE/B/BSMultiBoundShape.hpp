#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class BSMultiBound;
	class NiBound;
	class NiFrustumPlanes;
	class NiPoint3;
	class NiTransform;

	class __declspec(novtable) BSMultiBoundShape : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMultiBoundShape;
		inline static constexpr const auto& VTABLE = VTABLE::BSMultiBoundShape;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSMultiBoundShape;

		~BSMultiBoundShape() override; // 0x00

		enum class BSMBCullResult : std::int32_t
		{
			Untested = 0,
			Visible = 1,
			Culled = 2,
			Occluded = 3
		};

		enum class BSMBIntersectResult : std::int32_t
		{
			None = 0,
			Partial = 1,
			ContainsTarget = 2
		};

		enum class BSMBShapeType : std::int32_t
		{
			Invalid = 0,
			AABB = 1,
			OBB = 2,
			Sphere = 3,
			Capsule = 4
		};

		// add
		virtual auto QType() -> BSMBShapeType;											   // 0x28
		virtual auto QMultiBoundRadius() -> REX::Float32;								   // 0x29
		virtual auto CheckBound(const BSMultiBound& a_targetBound) -> BSMBIntersectResult; // 0x2A
		virtual auto CheckBound(const NiBound& a_targetBound) -> BSMBIntersectResult;	   // 0x2B
		virtual auto WithinFrustum(const NiFrustumPlanes& a_planes) -> bool;			   // 0x2C
		virtual auto CompletelyWithinFrustum(const NiFrustumPlanes& a_planes) -> bool;	   // 0x2D
		virtual auto GetNiBound(NiBound& a_bound) -> bool;								   // 0x2E
		virtual auto GetPointWithin(const NiPoint3& a_point) -> bool;					   // 0x2F
		virtual auto SetCenter(const NiPoint3& a_center) -> bool;						   // 0x30
		virtual auto MoveToWorld(const NiTransform& a_world) -> bool;					   // 0x31

		// members
		BSMBCullResult cullResult; // 0x18
	};

	static_assert(sizeof(BSMultiBoundShape) == 0x18);
}
