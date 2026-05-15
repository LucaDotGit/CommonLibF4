#pragma once

#include "RE/H/hknpConvexPolytopeShape.hpp"

namespace RE
{
	class __declspec(novtable) hknpTriangleShape
		: public hknpConvexPolytopeShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpTriangleShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpTriangleShape };

		~hknpTriangleShape() override; // 00

		[[nodiscard]] static hknpTriangleShape* CreateEmptyTriangleShape(const REX::Float32 a_radius)
		{
			using FuncType = decltype(&hknpTriangleShape::CreateEmptyTriangleShape);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpTriangleShape::CreateEmptyTriangleShape };
			return std::invoke(FUNC, a_radius);
		}

		[[nodiscard]] static hknpTriangleShape* CreateTriangleShape(const hkVector4& a_vertexA, const hkVector4& a_vertexB, const hkVector4& a_vertexC, REX::Float32 a_radius)
		{
			auto* shape = CreateEmptyTriangleShape(a_radius);
			shape->SetVertices(a_vertexA, a_vertexB, a_vertexC);
			return shape;
		}

		void SetVertices(const hkVector4& a_vertexA, const hkVector4& a_vertexB, const hkVector4& a_vertexC)
		{
			using FuncType = decltype(&hknpTriangleShape::SetVertices);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpTriangleShape::SetVertices };
			std::invoke(FUNC, this, a_vertexA, a_vertexB, a_vertexC);
		}
	};
	static_assert(sizeof(hknpTriangleShape) == 0x50);
}
