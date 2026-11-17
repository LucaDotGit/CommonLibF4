#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class Resource;

	class __declspec(novtable) ResourceLibBase : public RefCountBase<ResourceLibBase, 2> // 0x00
	{
	public:
		// add
		virtual void RemoveResourceOnRelease(Resource* a_res) = 0; // 0x01
		virtual void PinResource(Resource* a_res) = 0;			   // 0x02
		virtual void UnpinResource(Resource* a_res) = 0;		   // 0x03
	};

	static_assert(sizeof(ResourceLibBase) == 0x10);
}
