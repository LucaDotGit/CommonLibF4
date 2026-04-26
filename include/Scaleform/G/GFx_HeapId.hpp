#pragma once

#include "Scaleform/S/StatBasicValues.hpp"

namespace Scaleform::GFx
{
	enum HeapId : std::int32_t
	{
		kHeapId_Global = kHeapId_Default,
		kHeapId_MovieDef,
		kHeapId_MovieView,
		kHeapId_MovieData,
		kHeapId_Images,
		kHeapId_OtherHeaps,
		kHeapId_HUDHeaps,
		kHeapId_Video
	};
}
