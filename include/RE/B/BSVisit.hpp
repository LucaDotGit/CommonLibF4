#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	class NiCollisionObject;
	class BSGeometry;
	class NiPointLight;
	class NiAVObject;
}

namespace RE::BSVisit
{
	using BSVisitControl = BSContainer::ForEachResult;

	BSVisitControl TraverseScenegraphCollision(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiCollisionObject*)>>& a_predicate);
	BSVisitControl TraverseScenegraphGeometries(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(BSGeometry*)>>& a_predicate);
	BSVisitControl TraverseScenegraphLights(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiPointLight*)>>& a_predicate);
	BSVisitControl TraverseScenegraphObjects(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiAVObject*)>>& a_predicate);
}
