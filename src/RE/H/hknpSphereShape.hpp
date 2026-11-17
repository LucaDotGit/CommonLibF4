#pragma once

#include "RE/H/hknpConvexShape.hpp"

namespace RE
{
	class __declspec(novtable) hknpSphereShape : public hknpConvexShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpSphereShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpSphereShape;

		[[nodiscard]]
		static auto CreateSphereShape(const hkVector4& a_center, REX::Float32 a_radius) -> hknpSphereShape*
		{
			using FuncType = decltype(&hknpSphereShape::CreateSphereShape);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpSphereShape::CreateSphereShape);
			return std::invoke(FUNC, a_center, a_radius);
		}
	};

	static_assert(sizeof(hknpSphereShape) == 0x40);
}
