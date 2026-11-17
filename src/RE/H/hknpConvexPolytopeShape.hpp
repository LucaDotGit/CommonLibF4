#pragma once

#include "RE/H/hknpConvexShape.hpp"

namespace RE
{
	class hkStridedVertices;
	class hkVector4;

	class __declspec(novtable) hknpConvexPolytopeShape : public hknpConvexShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpConvexPolytopeShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpConvexPolytopeShape;

		class Face
		{
		public:
			// members
			std::uint16_t firstIndex;  // 0x00
			std::uint8_t numIndices;   // 0x02
			std::uint8_t minHalfAngle; // 0x03
		};

		~hknpConvexPolytopeShape() override; // 0x00

		[[nodiscard]]
		static auto CreateFromVerticesInternal(
			const hkStridedVertices& a_vertices,
			const REX::Float32 a_radius,
			const BuildConfig& a_config) -> hknpConvexPolytopeShape*
		{
			using FuncType = decltype(&hknpConvexPolytopeShape::CreateFromVerticesInternal);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpConvexPolytopeShape::CreateFromVerticesInternal);
			return std::invoke(FUNC, a_vertices, a_radius, a_config);
		}

		// members
		hkRelArray<hkVector4> planes;	  // 0x40
		hkRelArray<Face> faces;			  // 0x44
		hkRelArray<std::uint8_t> indices; // 0x48
	};

	static_assert(sizeof(hknpConvexPolytopeShape) == 0x50);
}
