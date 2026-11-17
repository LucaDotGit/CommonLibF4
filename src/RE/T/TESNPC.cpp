#include "RE/T/TESNPC.hpp"

#include "RE/A/ACTOR_BASE_DATA.hpp"
#include "RE/F/FACTION_RANK.hpp"
#include "RE/P/PlayerCharacter.hpp"
#include "RE/T/TESRace.hpp"

namespace RE
{
	auto TESNPC::GetAlternateHeadPartListMap() noexcept -> BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>&
	{
		static const auto ALTERNATIVE_HEAD_PART_LIST_MAP =
			REL::Relocation<BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>*>{
				ID::TESNPC::AlternateHeadPartListMap,
				Offset::TESNPC::AlternateHeadPartListMap
		};
		return *ALTERNATIVE_HEAD_PART_LIST_MAP;
	}

	auto TESNPC::HasApplicableKeywordString(std::string_view a_editorID) const -> bool
	{
		if (ContainsExactKeywordString(a_editorID)) {
			return true;
		}

		if (formRace && formRace->ContainsExactKeywordString(a_editorID)) {
			return true;
		}

		return false;
	}

	auto TESNPC::GetFacialHairColor() const noexcept -> BGSColorForm*
	{
		return headRelatedData ? headRelatedData->facialHairColor : nullptr;
	}

	auto TESNPC::GetFacialBoneMorphIntensity() const -> REX::Float32
	{
		using FuncType = decltype(&TESNPC::GetFacialBoneMorphIntensity);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESNPC::GetFacialBoneMorphIntensity);
		return std::invoke(FUNC, this);
	}

	auto TESNPC::GetFaceDetails() const noexcept -> BGSTextureSet*
	{
		return headRelatedData ? headRelatedData->faceDetails : nullptr;
	}

	auto TESNPC::GetHairColor() const noexcept -> BGSColorForm*
	{
		return headRelatedData ? headRelatedData->hairColor : nullptr;
	}

	auto TESNPC::GetHeadParts(bool a_alternate) -> std::span<BGSHeadPart*>
	{
		if (!a_alternate || !UsesAlternateHeadPartList()) {
			return {headParts.data(), numHeadParts};
		}

		const auto& headPartMap = GetAlternateHeadPartListMap();
		const auto headPartIt = headPartMap.find(this);

		if (headPartIt == headPartMap.end()) {
			return {};
		}

		return {headPartIt->second.data(), headPartIt->second.size()};
	}

	auto TESNPC::GetHeadParts(bool a_alternate) const -> std::span<BGSHeadPart* const>
	{
		if (!a_alternate || !UsesAlternateHeadPartList()) {
			return {headParts.data(), numHeadParts};
		}

		const auto& headPartMap = GetAlternateHeadPartListMap();
		const auto headPartIt = headPartMap.find(this);

		if (headPartIt == headPartMap.end()) {
			return {};
		}

		return {headPartIt->second.data(), headPartIt->second.size()};
	}

	auto TESNPC::GetRootFaceNPC() noexcept -> TESNPC*
	{
		auto* root = this;
		while (root->faceNPC) {
			root = root->faceNPC;
		}

		return root;
	}

	auto TESNPC::GetRootFaceNPC() const noexcept -> const TESNPC*
	{
		const auto* root = this;
		while (root->faceNPC) {
			root = root->faceNPC;
		}

		return root;
	}

	auto TESNPC::GetSex() const noexcept -> SEX
	{
		return actorData.actorBaseFlags.any(ACTOR_BASE_DATA::Flags::Female) ? SEX::Female : SEX::Male;
	}

	auto TESNPC::GetShortName() const -> const char*
	{
		using FuncType = decltype(&TESNPC::GetShortName);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESNPC::GetShortName);
		return std::invoke(FUNC, this);
	}

	auto TESNPC::IsInFaction(const TESFaction* a_faction) const -> bool
	{
		return std::ranges::any_of(factions, [a_faction](const FACTION_RANK& a_factionRank) noexcept -> bool {
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
		headPartMap.insert_or_assign(this, BSTArray<BGSHeadPart*>{a_headParts.begin(), a_headParts.end()});
	}

	void TESNPC::SetTintingData(std::uint16_t a_uniqueID, REX::Float32 a_value, std::uint32_t a_color)
	{
		using FuncType = decltype(&TESNPC::SetTintingData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESNPC::SetTintingData);
		std::invoke(FUNC, this, a_uniqueID, a_value, a_color);
	}

	auto TESNPC::UsesAlternateHeadPartList() const -> bool
	{
		const auto* player = PlayerCharacter::GetSingleton();

		if (player && IsPlayer() && player->charGenRace && player->charGenRace != formRace) {
			const auto& headPartMap = GetAlternateHeadPartListMap();
			return headPartMap.contains(player->GetActorBase());
		}

		return originalRace && originalRace != formRace;
	}
}
