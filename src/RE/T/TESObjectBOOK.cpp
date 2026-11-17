#include "RE/T/TESObjectBOOK.hpp"

namespace RE
{
	auto TESObjectBOOK::GetHasBeenRead() const noexcept -> bool
	{
		return data.flags.any(OBJ_BOOK::Flags::HasBeenRead);
	}

	void TESObjectBOOK::SetHasBeenRead(bool a_value)
	{
		data.flags.set(a_value, OBJ_BOOK::Flags::HasBeenRead);
		AddChange(ChangeFlags::Read);
	}
}
