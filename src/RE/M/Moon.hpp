#pragma once

#include "RE/B/BSString.hpp"
#include "RE/N/NiBillboardNode.hpp"
#include "RE/S/SkyObject.hpp"

namespace RE
{
	class __declspec(novtable) Moon : public SkyObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Moon;
		inline static constexpr const auto& VTABLE = VTABLE::Moon;

		~Moon() override; // 0x00

		enum class Phase : std::int32_t
		{
			Full = 0,
			k3QWan = 1,
			HalfWan = 2,
			k1QWan = 3,
			New = 4,
			k1QWax = 5,
			HalfWax = 6,
			k3QWax = 7
		};

		enum class UpdateStatus : std::int32_t
		{
			NotRequired = 0,
			WhenCulled = 1,
			Initialize = 2
		};

		// members
		NiPointer<NiBillboardNode> moonBaseNode; // 0x10
		NiPointer<NiNode> moonNode;				 // 0x18
		NiPointer<NiNode> shadowNode;			 // 0x20
		NiPointer<BSTriShape> moonMesh;			 // 0x28
		NiPointer<BSTriShape> shadowMesh;		 // 0x30
		std::array<BSString, 8> textures;		 // 0x38
		REX::Float32 angleFadeStart;			 // 0xB8
		REX::Float32 angleFadeEnd;				 // 0xBC
		REX::Float32 angleShadowEarlyFade;		 // 0xC0
		REX::Float32 speed;						 // 0xC4
		REX::Float32 zOffset;					 // 0xC8
		std::uint32_t size;						 // 0xCC
		UpdateStatus updateMoonTexture;			 // 0xD0
	};

	static_assert(sizeof(Moon) == 0xD8);
}
