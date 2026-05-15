#pragma once

#include "RE/H/hkRelArray.hpp"
#include "RE/H/hknpShape.hpp"

namespace RE
{
	class hkAabb;
	class hkStridedVertices;
	class hkTransform;
	class hkVector4;
	class hkcdVertex;

	class __declspec(novtable) hknpConvexShape
		: public hknpShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpConvexShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpConvexShape };

		class MassConfig
		{
		public:
			// members
			REX::Enum<hknpShape::MassConfig::Quality, std::int32_t> quality; // 00
			REX::Float32 inertiaFactor;										 // 04
			REX::Float32 massOrNegativeDensity;								 // 08
		};
		static_assert(sizeof(MassConfig) == 0x0C);

		class BuildConfig
		{
		public:
			// members
			REX::Float32 simplificationTolerance{ 0.0099999998f }; // 00
			bool shrinkByRadius{ true };						   // 04
			REX::Float32 featurePreservationFactor{ 0.0f };		   // 08
			bool buildFaces{ true };							   // 0C
			bool buildMassProperties{ false };					   // 0D
			MassConfig massConfig;								   // 10
			hkTransform* extraTransform{ nullptr };				   // 20
			std::uint32_t sizeOfBaseClass{ 80 };				   // 28
			std::uint32_t maxNumVertices{ 252 };				   // 2C
			bool checkForDegenerateFaces{ false };				   // 30
			bool verbose{ false };								   // 31
		};
		static_assert(sizeof(BuildConfig) == 0x38);

		~hknpConvexShape() override; // 00

		[[nodiscard]] static hknpConvexShape* CreateFromAabb(const hkAabb& a_aabb, const REX::Float32 a_radius, const BuildConfig& a_config)
		{
			using FuncType = decltype(&hknpConvexShape::CreateFromAabb);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpConvexShape::CreateFromAabb };
			return std::invoke(FUNC, a_aabb, a_radius, a_config);
		}

		[[nodiscard]] static hknpConvexShape* CreateFromCylinder(const hkVector4& a_halfExtent, std::int32_t a_numVertices, const REX::Float32 a_radius, const BuildConfig& a_config)
		{
			using FuncType = decltype(&hknpConvexShape::CreateFromCylinder);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpConvexShape::CreateFromCylinder };
			return std::invoke(FUNC, a_halfExtent, a_numVertices, a_radius, a_config);
		}

		[[nodiscard]] static hknpConvexShape* CreateFromHalfExtents(const hkVector4& a_halfExtent, const REX::Float32 a_radius, const BuildConfig& a_config)
		{
			using FuncType = decltype(&hknpConvexShape::CreateFromHalfExtents);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpConvexShape::CreateFromHalfExtents };
			return std::invoke(FUNC, a_halfExtent, a_radius, a_config);
		}

		[[nodiscard]] static hknpConvexShape* CreateFromIndexedVertices(const hkVector4* a_vertexBuffer, const std::uint16_t* a_indexBuffer, std::int32_t a_numVertices, const REX::Float32 a_radius, const BuildConfig& a_config)
		{
			using FuncType = decltype(&hknpConvexShape::CreateFromIndexedVertices);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpConvexShape::CreateFromIndexedVertices };
			return std::invoke(FUNC, a_vertexBuffer, a_indexBuffer, a_numVertices, a_radius, a_config);
		}

		[[nodiscard]] static hknpConvexShape* CreateFromVertices(const hkStridedVertices& a_vertices, const REX::Float32 a_radius, const BuildConfig& a_config)
		{
			using FuncType = decltype(&hknpConvexShape::CreateFromVertices);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpConvexShape::CreateFromVertices };
			return std::invoke(FUNC, a_vertices, a_radius, a_config);
		}

		// members
		hkRelArray<hkcdVertex> vertices;   // 30
		std::array<std::byte, 0x14> pad34; // 34
	};
	static_assert(sizeof(hknpConvexShape) == 0x40);
}
