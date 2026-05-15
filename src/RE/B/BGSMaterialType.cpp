#include "RE/B/BGSMaterialType.hpp"

namespace RE
{
	auto BGSMaterialType::GetMaterialIDMap()
		-> BSTHashMap<std::uint32_t, BGSMaterialType*>&
	{
		static const auto MATERIAL_ID_MAP = REL::Relocation<BSTHashMap<std::uint32_t, BGSMaterialType*>*>{ ID::BGSMaterialType::MaterialIDMap, Offset::BGSMaterialType::MaterialIDMap };
		return *MATERIAL_ID_MAP;
	}

	BGSMaterialType* BGSMaterialType::GetMaterialTypeByID(std::uint32_t a_materialID)
	{
		const auto& materialMap = GetMaterialIDMap();

		const auto materialIt = materialMap.find(a_materialID);
		if (materialIt == materialMap.end()) {
			return nullptr;
		}

		return materialIt->second;
	}
}
