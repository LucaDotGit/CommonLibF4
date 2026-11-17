#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;
	class NiNode;

	class BSMagicShaderParticles
	{
	public:
		using Filter = bool(NiAVObject*);

		// members
		void* protoSystem;				 // 0x00 - BSModelDB::Handle
		NiPointer<NiNode> particlesRoot; // 0x08
		bool hasData;					 // 0x10
		bool attached;					 // 0x11
		bool stopped;					 // 0x12
		bool useSizeAdjustments;		 // 0x13
		Filter* filterFunction;			 // 0x18
	};

	static_assert(sizeof(BSMagicShaderParticles) == 0x20);
}
