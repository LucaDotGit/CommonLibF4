#include "RE/B/BSScript_StructTypeInfo.hpp"

#include "RE/B/BSScript_LinkValidState.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"

namespace RE::BSScript
{
	BSTSmartPointer<ObjectTypeInfo> StructTypeInfo::GetParentTypeInfo() const noexcept
	{
		return containingObjTypeInfo;
	}

	bool StructTypeInfo::IsLinked() const noexcept
	{
		switch (linkedValid.get()) {
			case LinkValidState::kLinkedValid:
			case LinkValidState::kLinkedInvalid: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool StructTypeInfo::IsLinkedValid() const noexcept
	{
		return linkedValid == LinkValidState::kLinkedValid;
	}

	bool StructTypeInfo::IsLinkedInvalid() const noexcept
	{
		return linkedValid == LinkValidState::kLinkedInvalid;
	}

	auto StructTypeInfo::GetVariableIndex(const BSFixedString& a_name) const
		-> std::optional<std::uint32_t>
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
