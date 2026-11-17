#include "RE/T/TESQuest.hpp"

#include "RE/B/BGSBaseAlias.hpp"
#include "RE/B/BSReadWriteLock.hpp"

namespace RE
{
	auto TESQuest::GetAliasByID(std::uint32_t a_id) const -> BGSBaseAlias*
	{
		const auto aliasLock = BSAutoReadLock(aliasAccessLock);

		for (auto* alias : aliases) {
			if (alias && alias->aliasID == a_id) {
				return alias;
			}
		}

		return nullptr;
	}

	auto TESQuest::GetAliasByName(const BSFixedString& a_name) const -> BGSBaseAlias*
	{
		const auto aliasLock = BSAutoReadLock(aliasAccessLock);

		for (auto* alias : aliases) {
			if (alias && alias->aliasName == a_name) {
				return alias;
			}
		}

		return nullptr;
	}

	auto TESQuest::GetAliasedRef(ObjectRefHandle* a_result, std::uint32_t a_aiAliasID) -> ObjectRefHandle
	{
		using FuncType = decltype(&TESQuest::GetAliasedRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESQuest::GetAliasedRef);
		return std::invoke(FUNC, this, a_result, a_aiAliasID);
	}

	auto TESQuest::SetStage(std::uint16_t a_stage) -> bool
	{
		using FuncType = decltype(&TESQuest::SetStage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESQuest::SetStage);
		return std::invoke(FUNC, this, a_stage);
	}
}
