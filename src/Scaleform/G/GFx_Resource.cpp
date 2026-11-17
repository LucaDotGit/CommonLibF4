#include "Scaleform/G/GFx_Resource.hpp"

namespace Scaleform::GFx
{
	void Resource::AddRef() const noexcept
	{
		refCount++;
	}

	void Resource::Release() const noexcept
	{
		if (--refCount != 0) {
			return;
		}

		try {
			delete lib;
			const_cast<Resource*>(this)->lib = nullptr;
			delete this;
		}
		catch (...) {
			REX::Fail("Failed to delete ref resource."sv);
		}
	}
}
