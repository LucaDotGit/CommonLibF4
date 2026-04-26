#include "RE/T/TESQuest.hpp"

#include "RE/B/BGSBaseAlias.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	BGSBaseAlias* TESQuest::GetAliasByID(std::uint32_t a_id) const
	{
		const auto aliasLock = BSAutoReadLock(aliasAccessLock);

		for (auto* alias : aliases) {
			if (alias && alias->aliasID == a_id) {
				return alias;
			}
		}

		return nullptr;
	}

	BGSBaseAlias* TESQuest::GetAliasByName(const BSFixedString& a_name) const
	{
		const auto aliasLock = BSAutoReadLock(aliasAccessLock);

		for (auto* alias : aliases) {
			if (alias && alias->aliasName == a_name) {
				return alias;
			}
		}

		return nullptr;
	}

	ObjectRefHandle TESQuest::GetAliasedRef(ObjectRefHandle* a_result, std::uint32_t a_aiAliasID)
	{
		using FuncType = decltype(&TESQuest::GetAliasedRef);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESQuest::GetAliasedRef };
		return std::invoke(FUNC, this, a_result, a_aiAliasID);
	}

	bool TESQuest::SetStage(std::uint16_t a_stage)
	{
		using FuncType = decltype(&TESQuest::SetStage);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESQuest::SetStage };
		return std::invoke(FUNC, this, a_stage);
	}
}
