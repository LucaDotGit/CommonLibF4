#pragma once

#include "Scaleform/G/GFx_StatGroup.hpp"

namespace Scaleform::GFx
{
	enum StatAmp : std::int32_t
	{
		StatAmp_Default = StatGroup_GFxAmp,

		StatAmp_Mem,
		StatAmp_ProfileFrame,
		StatAmp_Server,
		StatAmp_Message,
		StatAmp_Callstack,
		StatAmp_InstrBuffer
	};
}
