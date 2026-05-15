#include "RE/T/TESNPC.hpp"

#include "RE/A/ACTOR_BASE_DATA.hpp"
#include "RE/F/FACTION_RANK.hpp"
#include "RE/P/PlayerCharacter.hpp"
#include "RE/T/TESRace.hpp"

namespace RE
{
	auto TESNPC::GetAlternateHeadPartListMap()
		-> BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>&
	{
		static const auto ALTERNATIVE_HEAD_PART_LIST_MAP = REL::Relocation<BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>*>{ ID::TESNPC::AlternateHeadPartListMap, Offset::TESNPC::AlternateHeadPartListMap };
		return *ALTERNATIVE_HEAD_PART_LIST_MAP;
	}

	bool TESNPC::HasApplicableKeywordString(std::string_view a_editorID) const
	{
		if (ContainsExactKeywordString(a_editorID)) {
			return true;
		}

		if (formRace && formRace->ContainsExactKeywordString(a_editorID)) {
			return true;
		}

		return false;
	}

	BGSColorForm* TESNPC::GetFacialHairColor() const noexcept
	{
		return headRelatedData ? headRelatedData->facialHairColor : nullptr;
	}

	REX::Float32 TESNPC::GetFacialBoneMorphIntensity() const
	{
		using FuncType = decltype(&TESNPC::GetFacialBoneMorphIntensity);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESNPC::GetFacialBoneMorphIntensity };
		return std::invoke(FUNC, this);
	}

	BGSTextureSet* TESNPC::GetFaceDetails() const noexcept
	{
		return headRelatedData ? headRelatedData->faceDetails : nullptr;
	}

	BGSColorForm* TESNPC::GetHairColor() const noexcept
	{
		return headRelatedData ? headRelatedData->hairColor : nullptr;
	}

	std::span<BGSHeadPart*> TESNPC::GetHeadParts(bool a_alternate)
	{
		if (!a_alternate || !UsesAlternateHeadPartList()) {
			return { headParts.data(), numHeadParts };
		}

		const auto& headPartMap = GetAlternateHeadPartListMap();
		const auto headPartIt = headPartMap.find(this);

		if (headPartIt == headPartMap.end()) {
			return {};
		}

		return { headPartIt->second.data(), headPartIt->second.size() };
	}

	std::span<BGSHeadPart* const> TESNPC::GetHeadParts(bool a_alternate) const
	{
		if (!a_alternate || !UsesAlternateHeadPartList()) {
			return { headParts.data(), numHeadParts };
		}

		const auto& headPartMap = GetAlternateHeadPartListMap();
		const auto headPartIt = headPartMap.find(this);

		if (headPartIt == headPartMap.end()) {
			return {};
		}

		return { headPartIt->second.data(), headPartIt->second.size() };
	}

	TESNPC* TESNPC::GetRootFaceNPC() noexcept
	{
		auto* root = this;
		while (root->faceNPC) {
			root = root->faceNPC;
		}

		return root;
	}

	const TESNPC* TESNPC::GetRootFaceNPC() const noexcept
	{
		const auto* root = this;
		while (root->faceNPC) {
			root = root->faceNPC;
		}

		return root;
	}

	SEX TESNPC::GetSex() const noexcept
	{
		return actorData.actorBaseFlags.any(ACTOR_BASE_DATA::Flags::kFemale) ? SEX::kFemale : SEX::kMale;
	}

	const char* TESNPC::GetShortName() const
	{
		using FuncType = decltype(&TESNPC::GetShortName);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESNPC::GetShortName };
		return std::invoke(FUNC, this);
	}

	bool TESNPC::IsInFaction(const TESFaction* a_faction) const
	{
		return std::ranges::any_of(factions, [a_faction](const FACTION_RANK& a_factionRank) -> bool {
			return a_factionRank.faction == a_faction && a_factionRank.rank > -1;
		});
	}

	void TESNPC::SetFaceDetails(BGSTextureSet* a_faceDetails)
	{
		if (!headRelatedData) {
			headRelatedData = new HeadRelatedData();
		}

		if (!headRelatedData) {
			return;
		}

		headRelatedData->faceDetails = a_faceDetails;
	}

	void TESNPC::SetFacialHairColor(BGSColorForm* a_facialHairColor)
	{
		if (!headRelatedData) {
			headRelatedData = new HeadRelatedData();
		}

		if (!headRelatedData) {
			return;
		}

		headRelatedData->facialHairColor = a_facialHairColor;
	}

	void TESNPC::SetHairColor(BGSColorForm* a_hairColor)
	{
		if (!headRelatedData) {
			headRelatedData = new HeadRelatedData();
		}

		if (!headRelatedData) {
			return;
		}

		headRelatedData->hairColor = a_hairColor;
	}

	void TESNPC::SetHeadParts(std::span<BGSHeadPart*> a_headParts, bool a_alternate)
	{
		if (!a_alternate || !UsesAlternateHeadPartList()) {
			headParts.allocate_bytes(static_cast<std::uint32_t>(a_headParts.size()));

			std::ranges::copy(a_headParts, headParts.data());
			numHeadParts = static_cast<std::uint8_t>(a_headParts.size());
			return;
		}

		auto& headPartMap = GetAlternateHeadPartListMap();
		headPartMap.insert_or_assign(this, BSTArray<BGSHeadPart*>{ a_headParts.begin(), a_headParts.end() });
	}

	void TESNPC::SetTintingData(std::uint16_t a_uniqueID, REX::Float32 a_value, std::uint32_t a_color)
	{
		using FuncType = decltype(&TESNPC::SetTintingData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESNPC::SetTintingData };
		std::invoke(FUNC, this, a_uniqueID, a_value, a_color);
	}

	bool TESNPC::UsesAlternateHeadPartList() const
	{
		const auto* player = PlayerCharacter::GetSingleton();

		if (player && IsPlayer() && player->charGenRace && player->charGenRace != formRace) {
			const auto& headPartMap = GetAlternateHeadPartListMap();
			return headPartMap.contains(player->GetActorBase());
		}

		return originalRace && originalRace != formRace;
	}
}
