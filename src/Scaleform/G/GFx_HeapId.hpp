#pragma once

#include "Scaleform/S/StatBasicValues.hpp"

namespace Scaleform::GFx
{
	enum HeapId : std::int32_t
	{
		HeapId_Global = HeapId_Default,
		HeapId_MovieDef,
		HeapId_MovieView,
		HeapId_MovieData,
		HeapId_Images,
		HeapId_OtherHeaps,
		HeapId_HUDHeaps,
		HeapId_Video
	};
}
