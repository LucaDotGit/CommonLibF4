#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkBlockStream.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkResult.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpShapeType.hpp"

namespace RE::hkcdGsk
{
	class Cache;
}

namespace RE
{
	enum class hknpCollisionDispatchType : std::int32_t;

	class hkAabb;
	class hkDiagonalizedMassProperties;
	class hkGeometry;
	class hkRefCountedProperties;
	class hkTransform;
	class hkcdVertex;
	class hknpAabbQuery;
	class hknpCdBody;
	class hknpCollisionQueryCollector;
	class hknpCollisionQueryContext;
	class hknpPointQuery;
	class hknpQueryFilterData;
	class hknpRayCastQuery;
	class hknpShapeCollector;
	class hknpShapeKeyMask;
	class hknpShapeQueryInfo;
	class hknpShapeSignals;
	class hknpSolverInfo;

	class __declspec(novtable) alignas(0x10) hknpShape : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpShape;

		enum class Flags : std::uint16_t
		{
			None = 0,
			IsConvexShape = 1 << 0,
			IsConvexPolytopeShape = 1 << 1,
			IsCompositeShape = 1 << 2,
			IsHeightFieldShape = 1 << 3,
			UseSinglePointManifold = 1 << 4,
			IsInteriorTriangle = 1 << 5,
			SupportsCollisionsWithInteriorTriangles = 1 << 6,
			UseNormalToFindSupportPlane = 1 << 7,
			UseSmallFaceIndices = 1 << 8,
			NoGetShapeKeysOnSPU = 1 << 9,
			ShapeNotSupportedOnSPU = 1 << 10,
			IsTriangleOrQuadShape = 1 << 11,
			IsQuadShape = 1 << 12
		};

		class MassConfig
		{
		public:
			enum class Quality : std::int32_t
			{
				Low = 0,
				Medium = 1,
				High = 2
			};
		};

		static_assert(std::is_empty_v<MassConfig>);

		class BuildSurfaceGeometryConfig; // To-Do
		class GetShapeKeysConfig;		  // To-Do
		class SdfContactPoint;			  // To-Do
		class SdfQuery;					  // To-Do

		~hknpShape() override; // 0x00

		// add
		virtual auto GetType() const -> hknpShapeType;									// 0x04
		virtual auto CalcSize() const -> std::int32_t;									// 0x05
		virtual void CalcAabb(const hkTransform& a_transform, hkAabb& a_aabbOut) const; // 0x06
		virtual auto GetMutationSignals() -> hknpShapeSignals*;							// 0x07
		virtual auto GetNumberOfSupportVertices() const -> std::int32_t;				// 0x08
		virtual auto GetSupportVertices(hkcdVertex* a_vertexBuffer, std::int32_t a_bufferSize) const
			-> const hkcdVertex*;																			 // 0x09
		virtual void GetSupportingVertex(const hkVector4& a_direction, hkcdVertex* a_vertexBufferOut) const; // 0x0A
		virtual void ConvertVertexIdsToVertices(
			const std::uint8_t* a_ids,
			std::int32_t a_numIDs,
			hkcdVertex* a_verticesOut) const;				   // 0x0B
		virtual auto GetNumberOfFaces() const -> std::int32_t; // 0x0C
		virtual void GetFaceInfo(std::int32_t a_faceID, hkVector4& a_planeOut, std::int32_t& a_minAngleOut)
			const; // 0x0D
		virtual auto GetFaceVertices(
			std::int32_t a_faceID,
			hkVector4& a_planeOut,
			hkcdVertex* a_vertexBufferOut) const -> std::int32_t; // 0x0E
		virtual auto GetSupportingFace(
			hkVector4& a_direction,
			hkVector4& a_surfacePoint,
			const hkcdGsk::Cache* a_gskCache,
			bool a_useB,
			std::uint32_t a_prevFaceID,
			hkVector4& a_planeOut,
			std::int32_t& a_minAngleOut) const -> std::int32_t;											// 0x0F
		virtual auto CalcMinAngleBetweenFaces() const -> REX::Float32;									// 0x10
		virtual void GetSignedDistances(const SdfQuery& a_query, SdfContactPoint* a_contactsOut) const; // 0x11
		virtual auto GetSignedDistanceContacts(
			const hknpCdBody& a_queryBody,
			REX::Float32 a_maxDistance,
			std::int32_t a_vertexIdOffset,
			hkBlockStream<SdfContactPoint>::Writer& a_contactPointsOut) const -> std::int32_t; // 0x12
		virtual auto CreateShapeKeyMask() const -> hknpShapeKeyMask*;						   // 0x13
		virtual auto GetShapeKeys(
			std::uint32_t* a_shapeKeysOut,
			std::int32_t a_capacity,
			std::uint32_t a_previousKey,
			const GetShapeKeysConfig& a_config) const -> std::int32_t; // 0x14
		virtual auto GetLeafShapes(
			const std::uint32_t* a_keys,
			std::int32_t a_numKeys,
			hknpShapeCollector* a_collector) const -> std::int32_t; // 0x15
		virtual void CastRayImpl(
			hknpCollisionQueryContext* a_queryContext,
			const hknpRayCastQuery& a_query,
			const hknpQueryFilterData& a_targetShapeFilterData,
			const hknpShapeQueryInfo& a_targetShapeInfo,
			hknpCollisionQueryCollector* a_collector) const; // 0x16
		virtual void QueryPointImpl(
			hknpCollisionQueryContext* a_queryContext,
			const hknpPointQuery& a_query,
			const hknpQueryFilterData& a_targetShapeFilterData,
			const hknpShapeQueryInfo& a_targetShapeInfo,
			hknpCollisionQueryCollector* a_collector) const; // 0x17
		virtual void QueryAabbImpl(
			hknpCollisionQueryContext* a_queryContext,
			const hknpAabbQuery& a_query,
			const hknpShapeQueryInfo& a_queryShapeInfo,
			const hknpQueryFilterData& a_targetShapeFilterData,
			const hknpShapeQueryInfo& a_targetShapeInfo,
			hkArray<std::uint32_t>* a_hits,
			hkAabb* a_nmpInOut) const; // 0x19
		virtual void QueryAabbImpl(
			hknpCollisionQueryContext* a_queryContext,
			const hknpAabbQuery& a_query,
			const hknpShapeQueryInfo& a_queryShapeInfo,
			const hknpQueryFilterData& a_targetShapeFilterData,
			const hknpShapeQueryInfo& a_targetShapeInfo,
			hknpCollisionQueryCollector* a_collector,
			hkAabb* a_nmpInOut) const; // 0x18
		virtual auto SelectLevelOfDetail(
			const hknpSolverInfo& a_si,
			const hknpCdBody& a_partner,
			std::int32_t a_previousLevelOfDetail) const -> std::int32_t; // 0x1A
		virtual void BuildMassProperties(
			const MassConfig& a_massConfig,
			hkDiagonalizedMassProperties& a_massPropertiesOut) const; // 0x1B
		virtual auto BuildSurfaceGeometry(const BuildSurfaceGeometryConfig& a_config, hkGeometry* a_geometryOut) const
			-> hkResult;					   // 0x1C
		virtual void CheckConsistency() const; // 0x1D

		// members
		REX::EnumSet<Flags, std::uint16_t> flags;						// 0x10
		std::uint8_t numShapeKeyBits;									// 0x12
		REX::Enum<hknpCollisionDispatchType, std::int8_t> dispatchType; // 0x13
		REX::Float32 convexRadius;										// 0x14
		std::uintptr_t userData;										// 0x18
		hkRefCountedProperties* properties;								// 0x20
	};

	static_assert(sizeof(hknpShape) == 0x30);
}
