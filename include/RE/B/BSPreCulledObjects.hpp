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
		NiAVObject* object;	 // 00
		std::uint32_t flags; // 08 - TODO
	};
	static_assert(sizeof(ObjectRecord) == 0x10);
}
