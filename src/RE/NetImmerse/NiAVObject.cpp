#include "RE/NetImmerse/NiAVObject.hpp"

#include "RE/Bethesda/BSGeometry.hpp"
#include "RE/Bethesda/BSVisit.hpp"
#include "RE/NetImmerse/NiCollisionObject.hpp"
#include "RE/NetImmerse/NiNode.hpp"
#include "RE/NetImmerse/NiUpdateData.hpp"

namespace RE
{
	NiAVObject::NiAVObject()
	{
		stl::emplace_vtable(this);
		local.MakeIdentity();
		world.MakeIdentity();
		previousWorld.MakeIdentity();
		flags.flags = 0xE;
	}

	NiAVObject::~NiAVObject() {} // NOLINT(modernize-use-equals-default)

	void NiAVObject::CullGeometry(bool a_cull)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geo) -> BSVisit::BSVisitControl {
			a_geo->SetAppCulled(a_cull);
			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::CullNode(bool a_cull)
	{
		BSVisit::TraverseScenegraphObjects(this, [&](NiAVObject* a_object) -> BSVisit::BSVisitControl {
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
