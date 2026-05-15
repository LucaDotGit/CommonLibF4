#pragma once

#include "RE/H/hknpConvexShape.hpp"

namespace RE
{
	class hkStridedVertices;
	class hkVector4;

	class __declspec(novtable) hknpConvexPolytopeShape
		: public hknpConvexShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpConvexPolytopeShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpConvexPolytopeShape };

		class Face
		{
		public:
			// members
			std::uint16_t firstIndex;  // 00
			std::uint8_t numIndices;   // 02
			std::uint8_t minHalfAngle; // 03
		};

		~hknpConvexPolytopeShape() override; // 00

		[[nodiscard]] static hknpConvexPolytopeShape* CreateFromVerticesInternal(const hkStridedVertices& a_vertices, const REX::Float32 a_radius, const BuildConfig& a_config)
		{
			using FuncType = decltype(&hknpConvexPolytopeShape::CreateFromVerticesInternal);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpConvexPolytopeShape::CreateFromVerticesInternal };
			return std::invoke(FUNC, a_vertices, a_radius, a_config);
		}

		// members
		hkRelArray<hkVector4> planes;	  // 40
		hkRelArray<Face> faces;			  // 44
		hkRelArray<std::uint8_t> indices; // 48
	};
	static_assert(sizeof(hknpConvexPolytopeShape) == 0x50);
}
