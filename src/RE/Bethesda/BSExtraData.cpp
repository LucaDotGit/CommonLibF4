#include "RE/Bethesda/BSExtraData.hpp"

#include "RE/Bethesda/BGSMod.hpp"
#include "RE/Bethesda/FormComponents.hpp"
#include "RE/Bethesda/TESBoundObjects.hpp"

namespace RE
{
	ExtraInstanceData::ExtraInstanceData() :
		ExtraInstanceData(nullptr, nullptr)
	{
	}

	ExtraInstanceData::ExtraInstanceData(const TESBoundObject* a_base, BSTSmartPointer<TBO_InstanceData> a_data) :
		BSExtraData(TYPE),
		base(a_base),
		data(std::move(a_data))
	{
		stl::emplace_vtable(this);
	}

	void BGSObjectInstanceExtra::CreateBaseInstanceData(const TESBoundObject& a_object, BSTSmartPointer<TBO_InstanceData>& a_instanceData) const
	{
		if (values && itemIndex != static_cast<std::uint16_t>(-1)) {
			a_object.ApplyMods(a_instanceData, this);
		}
	}

	std::span<BGSMod::ObjectIndexData> BGSObjectInstanceExtra::GetIndexData() const noexcept
	{
		return values->GetBuffer<BGSMod::ObjectIndexData>(0);
	}

	ExtraLightDataStruct::ExtraLightDataStruct() :
		fov(0.0),
		fade(0.0),
		endDistanceCap(0.0),
		shadowDepthBias(0.0),
		spotNear(0.0),
		volumetricIntensity(0.0)
	{
	}
}
