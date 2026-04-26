#include "RE/T/TESObjectBOOK.hpp"

namespace RE
{
	bool TESObjectBOOK::GetHasBeenRead() const noexcept
	{
		return data.flags.any(OBJ_BOOK::Flags::kHasBeenRead);
	}

	void TESObjectBOOK::SetHasBeenRead(bool a_value)
	{
		data.flags.set(a_value, OBJ_BOOK::Flags::kHasBeenRead);
		AddChange(ChangeFlags::kRead);
	}
}
