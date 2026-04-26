#include "Scaleform/G/GFx_Resource.hpp"

namespace Scaleform::GFx
{
	void Resource::AddRef() noexcept
	{
		refCount++;
	}

	void Resource::Release() noexcept
	{
		if (--refCount != 0) {
			return;
		}

		try {
			delete lib;
			lib = nullptr;
			delete this;
		}
		catch (...) {
			REX::QuickFail("Failed to release Scaleform resource."sv);
		}
	}
}
