#include "RE/N/NiAVObject.hpp"

#include "RE/B/BSGeometry.hpp"
#include "RE/B/BSVisit.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiUpdateData.hpp"

namespace RE
{
	NiAVObject::NiAVObject()
	{
		REL::EmplaceVtable(this);
	}

	NiAVObject::~NiAVObject()
	{
		if (parent) {
			parent->DetachChild(this);
		}
	}

	void NiAVObject::CullGeometry(bool a_cull)
	{
		BSVisit::ForEachScenegraphGeometries(
			NiPointer(this),
			[a_cull](const NiPointer<BSGeometry>& a_geometry) -> BSVisit::BSVisitControl {
				if (!a_geometry) {
					return BSVisit::BSVisitControl::Continue;
				}

				a_geometry->SetAppCulled(a_cull);
				return BSVisit::BSVisitControl::Continue;
			});
	}

	void NiAVObject::CullNode(bool a_cull)
	{
		BSVisit::ForEachScenegraphObjects(
			NiPointer(this),
			[a_cull](const NiPointer<NiAVObject>& a_object) -> BSVisit::BSVisitControl {
				if (!a_object) {
					return BSVisit::BSVisitControl::Continue;
				}

				a_object->SetAppCulled(a_cull);
				return BSVisit::BSVisitControl::Continue;
			});
	}

	void NiAVObject::Update(NiUpdateData& a_data)
	{
		UpdateDownwardPass(a_data, 0);

		if (parent && a_data.flags.none(0x200)) {
			parent->UpdateUpwardPass(a_data);
		}
	}
}
