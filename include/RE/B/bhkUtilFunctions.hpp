#pragma once

namespace RE
{
	class bhkNPCollisionObject;
	class hknpBodyId;
	class hknpBSWorld;
	class NiAVObject;
}

namespace RE::bhkUtilFunctions
{
	[[nodiscard]] bhkNPCollisionObject* FindFirstCollisionObject(NiAVObject* a_object);
	[[nodiscard]] NiAVObject* GetAVObjectFromBodyID(const hknpBSWorld* a_world, hknpBodyId a_bodyID);
}
