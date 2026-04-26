#include "RE/B/BSVisit.hpp"

#include "RE/B/BSGeometry.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiCollisionObject.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointLight.hpp"

namespace RE::BSVisit
{
	BSVisitControl TraverseScenegraphCollision(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiCollisionObject*)>>& a_predicate)
	{
		if (!a_object) {
			return BSVisitControl::kContinue;
		}

		auto* collision = a_object->collisionObject.get();
		if (!collision) {
			return BSVisitControl::kContinue;
		}

		if (std::invoke(*a_predicate, collision) == BSVisitControl::kStop) {
			return BSVisitControl::kStop;
		}

		auto* node = a_object->AsNode();
		if (!node) {
			return BSVisitControl::kContinue;
		}

		for (auto& child : node->children) {
			if (TraverseScenegraphCollision(child.get(), a_predicate) == BSVisitControl::kStop) {
				return BSVisitControl::kStop;
			}
		}

		return BSVisitControl::kContinue;
	}

	BSVisitControl TraverseScenegraphGeometries(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(BSGeometry*)>>& a_predicate)
	{
		if (!a_object) {
			return BSVisitControl::kContinue;
		}

		auto* geom = a_object->AsGeometry();
		if (geom) {
			return std::invoke(*a_predicate, geom);
		}

		auto* node = a_object->AsNode();
		if (!node) {
			return BSVisitControl::kContinue;
		}

		for (auto& child : node->children) {
			if (TraverseScenegraphGeometries(child.get(), *a_predicate) == BSVisitControl::kStop) {
				return BSVisitControl::kStop;
			}
		}

		return BSVisitControl::kContinue;
	}

	BSVisitControl TraverseScenegraphLights(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiPointLight*)>>& a_predicate)
	{
		if (!a_object) {
			return BSVisitControl::kContinue;
		}

		auto* light = NiDynamicCast<NiPointLight*>(a_object);
		if (light) {
			return std::invoke(*a_predicate, light);
		}

		auto* node = a_object->AsNode();
		if (!node) {
			return BSVisitControl::kContinue;
		}

		for (auto& child : node->children) {
			if (TraverseScenegraphLights(child.get(), a_predicate) == BSVisitControl::kStop) {
				return BSVisitControl::kStop;
			}
		}

		return BSVisitControl::kContinue;
	}

	BSVisitControl TraverseScenegraphObjects(NiAVObject* a_object,
		const REX::NotNull<std::function<BSVisitControl(NiAVObject*)>>& a_predicate)
	{
		if (!a_object) {
			return BSVisitControl::kContinue;
		}

		if (std::invoke(*a_predicate, a_object) == BSVisitControl::kStop) {
			return BSVisitControl::kStop;
		}

		auto* node = a_object->AsNode();
		if (!node) {
			return BSVisitControl::kContinue;
		}

		for (auto& child : node->children) {
			if (TraverseScenegraphObjects(child.get(), a_predicate) == BSVisitControl::kStop) {
				return BSVisitControl::kStop;
			}
		}

		return BSVisitControl::kContinue;
	}
}
