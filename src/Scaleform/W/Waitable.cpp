#include "Scaleform/W/Waitable.hpp"

namespace Scaleform
{
	void Waitable::HandlerArray::AddRef() const noexcept
	{
		refCount++;
	}

	void Waitable::HandlerArray::Release() const noexcept
	{
		if (--refCount != 0) {
			return;
		}

		try {
			delete this;
		}
		catch (...) {
			REX::Fail("Failed to delete ref waitable handler array."sv);
		}
	}
}
