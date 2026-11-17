#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/N/NiPointer.hpp"

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

	auto ForEachScenegraphCollision(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<NiCollisionObject>&) const>>&
			a_predicate) -> BSVisitControl;

	auto ForEachScenegraphGeometries(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<BSGeometry>&) const>>& a_predicate)
		-> BSVisitControl;

	auto ForEachScenegraphLights(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<NiPointLight>&) const>>& a_predicate)
		-> BSVisitControl;

	auto ForEachScenegraphObjects(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<NiAVObject>&) const>>& a_predicate)
		-> BSVisitControl;
}
