#pragma once

#include "Scaleform/R/Render_Matrix.hpp"

namespace Scaleform::Render
{
	class ScreenToWorld
	{
	public:
		constexpr ScreenToWorld() = default;

		// members
		REX::Float32 sx{ std::numeric_limits<REX::Float32>::max() };	// 00
		REX::Float32 sy{ std::numeric_limits<REX::Float32>::max() };	// 04
		REX::Float32 lastX{ std::numeric_limits<REX::Float32>::max() }; // 08
		REX::Float32 lastY{ std::numeric_limits<REX::Float32>::max() }; // 0C
		Render::Matrix4x4<REX::Float32> matProj;						// 10
		Render::Matrix3x4<REX::Float32> matView;						// 50
		Render::Matrix3x4<REX::Float32> matWorld;						// 80
		Render::Matrix4x4<REX::Float32> matInvProj;						// B0
	};
	static_assert(sizeof(ScreenToWorld) == 0xF0);
}
