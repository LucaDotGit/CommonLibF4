#include "RE/B/BSScript_StructTypeInfo.hpp"

#include "RE/B/BSScript_LinkValidState.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"

namespace RE::BSScript
{
	auto StructTypeInfo::GetParentTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>
	{
		return containingObjTypeInfo;
	}

	auto StructTypeInfo::IsLinked() const noexcept -> bool
	{
		switch (linkedValid.get()) {
			case LinkValidState::LinkedValid:
			case LinkValidState::LinkedInvalid: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto StructTypeInfo::IsLinkedValid() const noexcept -> bool
	{
		return linkedValid == LinkValidState::LinkedValid;
	}

	auto StructTypeInfo::IsLinkedInvalid() const noexcept -> bool
	{
		return linkedValid == LinkValidState::LinkedInvalid;
	}

	auto StructTypeInfo::GetVariableIndexByName(const BSFixedString& a_name) const -> std::optional<std::uint32_t>
	{
		const auto varIt = varNameIndexMap.find(a_name);
		if (varIt == varNameIndexMap.end()) {
			return std::nullopt;
		}

		const auto varIndex = varIt->second;
		if (varIndex >= variables.size()) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		return varIndex;
	}
}
