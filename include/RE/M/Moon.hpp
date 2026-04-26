#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/N/NiBillboardNode.hpp"
#include "RE/S/SkyObject.hpp"

namespace RE
{
	class __declspec(novtable) Moon
		: public SkyObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Moon };
		inline static constexpr auto VTABLE{ VTABLE::Moon };

		virtual ~Moon(); // 00

		enum class Phase : std::int32_t
		{
			kFull = 0,
			k3QWan = 1,
			kHalfWan = 2,
			k1QWan = 3,
			kNew = 4,
			k1QWax = 5,
			kHalfWax = 6,
			k3QWax = 7
		};

		enum class UpdateStatus : std::int32_t
		{
			kNotRequired = 0,
			kWhenCulled = 1,
			kInitialize = 2
		};

		// members
		NiPointer<NiBillboardNode> moonBaseNode; // 10
		NiPointer<NiNode> moonNode;				 // 18
		NiPointer<NiNode> shadowNode;			 // 20
		NiPointer<BSTriShape> moonMesh;			 // 28
		NiPointer<BSTriShape> shadowMesh;		 // 30
		std::array<BSString, 8> textures;		 // 38
		REX::Float32 angleFadeStart;			 // B8
		REX::Float32 angleFadeEnd;				 // BC
		REX::Float32 angleShadowEarlyFade;		 // C0
		REX::Float32 speed;						 // C4
		REX::Float32 zOffset;					 // C8
		std::uint32_t size;						 // CC
		UpdateStatus updateMoonTexture;			 // D0
	};
	static_assert(sizeof(Moon) == 0xD8);
}
