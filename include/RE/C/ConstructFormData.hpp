#pragma once

namespace RE
{
	class ConstructFormData
	{
	public:
		// members
		TESForm* pform;		 // 00
		std::uint32_t flags; // 08
	};
	static_assert(sizeof(ConstructFormData) == 0x10);
}