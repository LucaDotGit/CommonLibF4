#include "RE/B/bhkUtilFunctions.hpp"

#include "RE/H/hknpBodyId.hpp"

namespace RE::bhkUtilFunctions
{
	auto FindFirstCollisionObject(NiAVObject* a_object) -> bhkNPCollisionObject*
	{
		using FuncType = decltype(&bhkUtilFunctions::FindFirstCollisionObject);
		static const auto FUNC = REL::Relocation<FuncType>(ID::bhkUtilFunctions::FindFirstCollisionObject);
		return std::invoke(FUNC, a_object);
	}

	auto GetAVObjectFromBodyID(const hknpBSWorld* a_world, hknpBodyId a_bodyID) -> NiAVObject*
	{
		using FuncType = decltype(&bhkUtilFunctions::GetAVObjectFromBodyID);
		static const auto FUNC = REL::Relocation<FuncType>(ID::bhkUtilFunctions::GetAVObjectFromBodyID);
		return std::invoke(FUNC, a_world, a_bodyID);
	}
}
