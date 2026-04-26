#pragma once

namespace RE
{
	class NiCollisionObject;
	class BSGeometry;
	class NiPointLight;
	class NiAVObject;
}

namespace RE::BSVisit
{
	enum class BSVisitControl : std::int32_t
	{
		kContinue = 0,
		kStop = 1
	};

	BSVisitControl TraverseScenegraphCollision(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiCollisionObject*)>>& a_predicate);
	BSVisitControl TraverseScenegraphGeometries(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(BSGeometry*)>>& a_predicate);
	BSVisitControl TraverseScenegraphLights(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiPointLight*)>>& a_predicate);
	BSVisitControl TraverseScenegraphObjects(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiAVObject*)>>& a_predicate);
}
