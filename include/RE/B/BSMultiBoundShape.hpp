#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class BSMultiBound;
	class NiBound;
	class NiFrustumPlanes;
	class NiPoint3;
	class NiTransform;

	class __declspec(novtable) BSMultiBoundShape
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSMultiBoundShape };
		inline static constexpr auto VTABLE{ VTABLE::BSMultiBoundShape };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSMultiBoundShape };

		~BSMultiBoundShape() override; // 00

		enum class BSMBCullResult : std::int32_t
		{
			kUntested = 0,
			kVisible = 1,
			kCulled = 2,
			kOccluded = 3
		};

		enum class BSMBIntersectResult : std::int32_t
		{
			kNone = 0,
			kPartial = 1,
			kContainsTarget = 2
		};

		enum class BSMBShapeType : std::int32_t
		{
			kInvalid = 0,
			kAABB = 1,
			kOBB = 2,
			kSphere = 3,
			kCapsule = 4
		};

		// add
		virtual BSMBShapeType QType();											   // 28
		virtual REX::Float32 QMultiBoundRadius();								   // 29
		virtual BSMBIntersectResult CheckBound(const BSMultiBound& a_targetBound); // 2A
		virtual BSMBIntersectResult CheckBound(const NiBound& a_targetBound);	   // 2B
		virtual bool WithinFrustum(const NiFrustumPlanes& a_planes);			   // 2C
		virtual bool CompletelyWithinFrustum(const NiFrustumPlanes& a_planes);	   // 2D
		virtual bool GetNiBound(NiBound& a_bound);								   // 2E
		virtual bool GetPointWithin(const NiPoint3& a_point);					   // 2F
		virtual bool SetCenter(const NiPoint3& a_center);						   // 30
		virtual bool MoveToWorld(const NiTransform& a_world);					   // 31

		// members
		BSMBCullResult cullResult; // 18
	};
	static_assert(sizeof(BSMultiBoundShape) == 0x18);
}
