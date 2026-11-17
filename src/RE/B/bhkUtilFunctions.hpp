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
	[[nodiscard]]
	auto FindFirstCollisionObject(NiAVObject* a_object) -> bhkNPCollisionObject*;
	[[nodiscard]]
	auto GetAVObjectFromBodyID(const hknpBSWorld* a_world, hknpBodyId a_bodyID) -> NiAVObject*;
}
