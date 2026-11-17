#include "RE/B/BSVisit.hpp"

#include "RE/B/BSGeometry.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiCollisionObject.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointLight.hpp"

namespace RE::BSVisit
{
	auto ForEachScenegraphCollision(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<NiCollisionObject>&) const>>&
			a_predicate) -> BSVisitControl
	{
		if (!a_object) {
			return BSVisitControl::Continue;
		}

		auto collision = a_object->collisionObject;
		if (!collision) {
			return BSVisitControl::Continue;
		}

		if (std::invoke(a_predicate.get(), collision) == BSVisitControl::Stop) {
			return BSVisitControl::Stop;
		}

		const auto node = dynamic_ni_pointer_cast<NiNode>(a_object);
		if (!node) {
			return BSVisitControl::Continue;
		}

		for (const auto& child : node->GetRuntimeData().children) {
			if (ForEachScenegraphCollision(child, a_predicate) == BSVisitControl::Stop) {
				return BSVisitControl::Stop;
			}
		}

		return BSVisitControl::Continue;
	}

	auto ForEachScenegraphGeometries(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<BSGeometry>&) const>>& a_predicate)
		-> BSVisitControl
	{
		if (!a_object) {
			return BSVisitControl::Continue;
		}

		auto geometry = dynamic_ni_pointer_cast<BSGeometry>(a_object);
		if (geometry) {
			return std::invoke(a_predicate.get(), geometry);
		}

		const auto node = dynamic_ni_pointer_cast<NiNode>(a_object);
		if (!node) {
			return BSVisitControl::Continue;
		}

		for (const auto& child : node->GetRuntimeData().children) {
			if (ForEachScenegraphGeometries(child, a_predicate) == BSVisitControl::Stop) {
				return BSVisitControl::Stop;
			}
		}

		return BSVisitControl::Continue;
	}

	auto ForEachScenegraphLights(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<NiPointLight>&) const>>& a_predicate)
		-> BSVisitControl
	{
		if (!a_object) {
			return BSVisitControl::Continue;
		}

		auto light = dynamic_ni_pointer_cast<NiPointLight>(a_object);
		if (light) {
			return std::invoke(a_predicate.get(), light);
		}

		const auto node = dynamic_ni_pointer_cast<NiNode>(a_object);
		if (!node) {
			return BSVisitControl::Continue;
		}

		for (const auto& child : node->GetRuntimeData().children) {
			if (ForEachScenegraphLights(child, a_predicate) == BSVisitControl::Stop) {
				return BSVisitControl::Stop;
			}
		}

		return BSVisitControl::Continue;
	}

	auto ForEachScenegraphObjects(
		const NiPointer<NiAVObject>& a_object,
		const REX::NotNull<std::move_only_function<BSVisitControl(const NiPointer<NiAVObject>&) const>>& a_predicate)
		-> BSVisitControl
	{
		if (!a_object) {
			return BSVisitControl::Continue;
		}

		if (std::invoke(a_predicate.get(), a_object) == BSVisitControl::Stop) {
			return BSVisitControl::Stop;
		}

		const auto node = dynamic_ni_pointer_cast<NiNode>(a_object);
		if (!node) {
			return BSVisitControl::Continue;
		}

		for (const auto& child : node->GetRuntimeData().children) {
			if (ForEachScenegraphObjects(child, a_predicate) == BSVisitControl::Stop) {
				return BSVisitControl::Stop;
			}
		}

		return BSVisitControl::Continue;
	}
}
