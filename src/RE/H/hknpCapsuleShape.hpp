#pragma once

#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpConvexPolytopeShape.hpp"

namespace RE
{
	class __declspec(novtable) hknpCapsuleShape : public hknpConvexPolytopeShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpCapsuleShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpCapsuleShape;

		~hknpCapsuleShape() override; // 0x00

		[[nodiscard]]
		static auto CreateCapsuleShape(const hkVector4& a_vertexA, const hkVector4& a_vertexB, REX::Float32 a_radius)
			-> hknpCapsuleShape*
		{
			using FuncType = decltype(&hknpCapsuleShape::CreateCapsuleShape);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpCapsuleShape::CreateCapsuleShape);
			return std::invoke(FUNC, a_vertexA, a_vertexB, a_radius);
		}

		void Init(const hkVector4& a_vertexA, const hkVector4& a_vertexB)
		{
			using FuncType = decltype(&hknpCapsuleShape::Init);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpCapsuleShape::Init);
			std::invoke(FUNC, this, a_vertexA, a_vertexB);
		}

		// members
		hkVector4 vertexA; // 0x50
		hkVector4 vertexB; // 0x60
	};

	static_assert(sizeof(hknpCapsuleShape) == 0x70);
}
