#include "RE/B/bhkUtilFunctions.hpp"

namespace RE::bhkUtilFunctions
{
	bhkNPCollisionObject* FindFirstCollisionObject(NiAVObject* a_object)
	{
		using FuncType = decltype(&bhkUtilFunctions::FindFirstCollisionObject);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkUtilFunctions::FindFirstCollisionObject };
		return std::invoke(FUNC, a_object);
	}
}
