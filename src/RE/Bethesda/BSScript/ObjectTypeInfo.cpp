#include "RE/Bethesda/BSScript/ObjectTypeInfo.hpp"

namespace RE::BSScript
{
	std::uint32_t ObjectTypeInfo::GetTotalNumVariables() const
	{
		auto numVars = GetNumVariables();
		for (auto iter = GetParent(); iter; iter = iter->GetParent()) {
			numVars += iter->GetNumVariables();
		}
		return numVars;
	}

	std::uint32_t ObjectTypeInfo::GetPropertyIndex(const BSFixedString& a_name) const
	{
		const auto props = GetPropertyIter();
		if (props) {
			for (std::uint32_t i = 0; i < GetNumProperties(); ++i) {
				const auto& prop = props[i];
				if (prop.name == a_name) {
					return prop.info.autoVarIndex;
				}
			}
		}
		return static_cast<std::uint32_t>(-1);
	}

	void ObjectTypeInfo::Dtor()
	{
		using func_t = decltype(&ObjectTypeInfo::Dtor);
		static REL::Relocation<func_t> func{ REL::ID(1047917) };
		return func(this);
	}
}
