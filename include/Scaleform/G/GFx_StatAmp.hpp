#pragma once

#include "Scaleform/G/GFx_StatGroup.hpp"

namespace Scaleform::GFx
{
	enum StatAmp : std::int32_t
	{
		kStatAmp_Default = kStatGroup_GFxAmp,

		kStatAmp_Mem,
		kStatAmp_ProfileFrame,
		kStatAmp_Server,
		kStatAmp_Message,
		kStatAmp_Callstack,
		kStatAmp_InstrBuffer
	};
}
