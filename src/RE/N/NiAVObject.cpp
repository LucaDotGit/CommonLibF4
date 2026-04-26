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
		BSVisit::TraverseScenegraphGeometries(this, [a_cull](BSGeometry* a_geo) -> BSVisit::BSVisitControl {
			a_geo->SetAppCulled(a_cull);
			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::CullNode(bool a_cull)
	{
		BSVisit::TraverseScenegraphObjects(this, [a_cull](NiAVObject* a_object) -> BSVisit::BSVisitControl {
			a_object->SetAppCulled(a_cull);
			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::Update(NiUpdateData& a_data)
	{
		UpdateDownwardPass(a_data, 0);
		if (parent && ((a_data.flags & 0x200) == 0)) {
			parent->UpdateUpwardPass(a_data);
		}
	}
}
