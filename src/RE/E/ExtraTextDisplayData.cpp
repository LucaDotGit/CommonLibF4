#include "RE/E/ExtraTextDisplayData.hpp"

namespace RE
{
	auto ExtraTextDisplayData::GetDisplayName(TESBoundObject* a_baseObject) const -> BSFixedStringCS
	{
		using FuncType = decltype(&ExtraTextDisplayData::GetDisplayName);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ExtraTextDisplayData::GetDisplayName);
		return std::invoke(FUNC, this, a_baseObject);
	}

	auto ExtraTextDisplayData::GetCustomName() const -> std::optional<BSFixedStringCS>
	{
		if (ownerInstance != DisplayDataType::CustomName) {
			return std::nullopt;
		}

		return displayName;
	}

	void ExtraTextDisplayData::SetCustomName(const BSFixedStringCS& a_name)
	{
		ownerInstance = DisplayDataType::CustomName;
		customNameLength = static_cast<std::uint16_t>(a_name.size());
		displayName = a_name;
	}
}
