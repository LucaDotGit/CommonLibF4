#pragma once

namespace RE
{
	class NiAVObject;
}

namespace RE::BSPreCulledObjects
{
	class ObjectRecord
	{
	public:
		// members
		NiAVObject* object;	 // 0x00
		std::uint32_t flags; // 0x08 - To-Do
	};

	static_assert(sizeof(ObjectRecord) == 0x10);
}
