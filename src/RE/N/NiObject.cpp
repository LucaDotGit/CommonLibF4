#include "RE/N/NiObject.hpp"

namespace RE
{
	NiObject::NiObject()
	{
		REL::EmplaceVtable(this);
	}
}
