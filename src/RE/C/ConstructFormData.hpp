#pragma once

namespace RE
{
	class ConstructFormData
	{
	public:
		// members
		TESForm* pform;		 // 0x00
		std::uint32_t flags; // 0x08
	};

	static_assert(sizeof(ConstructFormData) == 0x10);
}
