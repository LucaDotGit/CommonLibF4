#pragma once

#include "Scaleform/R/Render_Matrix3x4.hpp"
#include "Scaleform/R/Render_Matrix4x4.hpp"

namespace Scaleform::Render
{
	class ScreenToWorld
	{
	public:
		// members
		REX::Float32 sx{std::numeric_limits<REX::Float32>::max()};	  // 0x00
		REX::Float32 sy{std::numeric_limits<REX::Float32>::max()};	  // 0x04
		REX::Float32 lastX{std::numeric_limits<REX::Float32>::max()}; // 0x08
		REX::Float32 lastY{std::numeric_limits<REX::Float32>::max()}; // 0x0C
		Render::Matrix4x4F matProj;									  // 0x10
		Render::Matrix3x4<REX::Float32> matView;					  // 0x50
		Render::Matrix3x4<REX::Float32> matWorld;					  // 0x80
		Render::Matrix4x4F matInvProj;								  // 0xB0
	};

	static_assert(sizeof(ScreenToWorld) == 0xF0);
}
