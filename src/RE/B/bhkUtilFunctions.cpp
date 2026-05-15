#include "RE/B/bhkUtilFunctions.hpp"

#include "RE/H/hknpBodyId.hpp"

namespace RE::bhkUtilFunctions
{
	bhkNPCollisionObject* FindFirstCollisionObject(NiAVObject* a_object)
	{
		using FuncType = decltype(&bhkUtilFunctions::FindFirstCollisionObject);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkUtilFunctions::FindFirstCollisionObject };
		return std::invoke(FUNC, a_object);
	}

	NiAVObject* GetAVObjectFromBodyID(const hknpBSWorld* a_world, hknpBodyId a_bodyID)
	{
		using FuncType = decltype(&bhkUtilFunctions::GetAVObjectFromBodyID);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkUtilFunctions::GetAVObjectFromBodyID };
		return std::invoke(FUNC, a_world, a_bodyID);
	}
}
