#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkBlockStream.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkResult.hpp"
#include "RE/H/hkVector4f.hpp"
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
	class hkTransformf;
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

	class __declspec(novtable) alignas(0x10) hknpShape
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpShape };

		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kIsConvexShape = 1 << 0,
			kIsConvexPolytopeShape = 1 << 1,
			kIsCompositeShape = 1 << 2,
			kIsHeightFieldShape = 1 << 3,
			kUseSinglePointManifold = 1 << 4,
			kIsInteriorTriangle = 1 << 5,
			kSupportsCollisionsWithInteriorTriangles = 1 << 6,
			kUseNormalToFindSupportPlane = 1 << 7,
			kUseSmallFaceIndices = 1 << 8,
			kNoGetShapeKeysOnSPU = 1 << 9,
			kShapeNotSupportedOnSPU = 1 << 10,
			kIsTriangleOrQuadShape = 1 << 11,
			kIsQuadShape = 1 << 12
		};

		class BuildSurfaceGeometryConfig; // TODO
		class GetShapeKeysConfig;		  // TODO
		class MassConfig;				  // TODO
		class SdfContactPoint;			  // TODO
		class SdfQuery;					  // TODO

		// add
		virtual hknpShapeType GetType() const;																																																																				  // 04
		virtual std::int32_t CalcSize() const;																																																																				  // 05
		virtual void CalcAabb(const hkTransformf& a_transform, hkAabb& a_aabbOut) const;																																																									  // 06
		virtual hknpShapeSignals* GetMutationSignals();																																																																		  // 07
		virtual std::int32_t GetNumberOfSupportVertices() const;																																																															  // 08
		virtual const hkcdVertex* GetSupportVertices(hkcdVertex* a_vertexBuffer, std::int32_t a_bufferSize) const;																																																			  // 09
		virtual void GetSupportingVertex(const hkVector4f& a_direction, hkcdVertex* a_vertexBufferOut) const;																																																				  // 0A
		virtual void ConvertVertexIdsToVertices(const std::uint8_t* a_ids, std::int32_t a_numIDs, hkcdVertex* a_verticesOut) const;																																															  // 0B
		virtual std::int32_t GetNumberOfFaces() const;																																																																		  // 0C
		virtual void GetFaceInfo(std::int32_t a_faceID, hkVector4f& a_planeOut, std::int32_t& a_minAngleOut) const;																																																			  // 0D
		virtual std::int32_t GetFaceVertices(std::int32_t a_faceID, hkVector4f& a_planeOut, hkcdVertex* a_vertexBufferOut) const;																																															  // 0E
		virtual std::int32_t GetSupportingFace(hkVector4f& a_direction, hkVector4f& a_surfacePoint, const hkcdGsk::Cache* a_gskCache, bool a_useB, std::uint32_t a_prevFaceID, hkVector4f& a_planeOut, std::int32_t& a_minAngleOut) const;																					  // 0F
		virtual REX::Float32 CalcMinAngleBetweenFaces() const;																																																																  // 10
		virtual void GetSignedDistances(const SdfQuery& a_query, SdfContactPoint* a_contactsOut) const;																																																						  // 11
		virtual std::int32_t GetSignedDistanceContacts(const hknpCdBody& a_queryBody, REX::Float32 a_maxDistance, std::int32_t a_vertexIdOffset, hkBlockStream<SdfContactPoint>::Writer& a_contactPointsOut) const;																											  // 12
		virtual hknpShapeKeyMask* CreateShapeKeyMask() const;																																																																  // 13
		virtual std::int32_t GetShapeKeys(std::uint32_t* a_shapeKeysOut, std::int32_t a_capacity, std::uint32_t a_previousKey, const GetShapeKeysConfig& a_config) const;																																					  // 14
		virtual std::int32_t GetLeafShapes(const std::uint32_t* a_keys, std::int32_t a_numKeys, hknpShapeCollector* a_collector) const;																																														  // 15
		virtual void CastRayImpl(hknpCollisionQueryContext* a_queryContext, const hknpRayCastQuery& a_query, const hknpQueryFilterData& a_targetShapeFilterData, const hknpShapeQueryInfo& a_targetShapeInfo, hknpCollisionQueryCollector* a_collector) const;																  // 16
		virtual void QueryPointImpl(hknpCollisionQueryContext* a_queryContext, const hknpPointQuery& a_query, const hknpQueryFilterData& a_targetShapeFilterData, const hknpShapeQueryInfo& a_targetShapeInfo, hknpCollisionQueryCollector* a_collector) const;																  // 17
		virtual void QueryAabbImpl(hknpCollisionQueryContext* a_queryContext, const hknpAabbQuery& a_query, const hknpShapeQueryInfo& a_queryShapeInfo, const hknpQueryFilterData& a_targetShapeFilterData, const hknpShapeQueryInfo& a_targetShapeInfo, hkArray<std::uint32_t>* a_hits, hkAabb* a_nmpInOut) const;			  // 19
		virtual void QueryAabbImpl(hknpCollisionQueryContext* a_queryContext, const hknpAabbQuery& a_query, const hknpShapeQueryInfo& a_queryShapeInfo, const hknpQueryFilterData& a_targetShapeFilterData, const hknpShapeQueryInfo& a_targetShapeInfo, hknpCollisionQueryCollector* a_collector, hkAabb* a_nmpInOut) const; // 18
		virtual std::int32_t SelectLevelOfDetail(const hknpSolverInfo& a_si, const hknpCdBody& a_partner, std::int32_t a_previousLevelOfDetail) const;																																										  // 1A
		virtual void BuildMassProperties(const MassConfig& a_massConfig, hkDiagonalizedMassProperties& a_massPropertiesOut) const;																																															  // 1B
		virtual hkResult BuildSurfaceGeometry(const BuildSurfaceGeometryConfig& a_config, hkGeometry* a_geometryOut) const;																																																	  // 1C
		virtual void CheckConsistency() const;																																																																				  // 1D

		// members
		REX::EnumSet<Flags, std::uint16_t> flags;						// 10
		std::uint8_t numShapeKeyBits;									// 12
		REX::Enum<hknpCollisionDispatchType, std::int8_t> dispatchType; // 13
		REX::Float32 convexRadius;										// 14
		std::uintptr_t userData;										// 18
		hkRefCountedProperties* properties;								// 20
	};
	static_assert(sizeof(hknpShape) == 0x30);
}
