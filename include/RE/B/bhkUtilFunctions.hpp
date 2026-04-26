#pragma once

namespace RE
{
	class bhkNPCollisionObject;
	class NiAVObject;
}

namespace RE::bhkUtilFunctions
{
	[[nodiscard]] bhkNPCollisionObject* FindFirstCollisionObject(NiAVObject* a_object);
}
