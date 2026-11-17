#include "RE/P/PlayerCharacter.hpp"

#include "RE/B/BGSEntryPoint.hpp"
#include "RE/C/Calendar.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	auto PlayerCharacter::GetSingleton() noexcept -> PlayerCharacter*
	{
		static const auto SINGLETON = REL::Relocation<NiPointer<PlayerCharacter>*>(ID::PlayerCharacter::Singleton);
		return (*SINGLETON).get();
	}

	auto PlayerCharacter::GetPlayerHandle() -> ActorHandle
	{
		static const auto SINGLETON = REL::Relocation<ActorHandle*>(ID::PlayerCharacter::GetPlayerHandle);
		return *SINGLETON;
	}

	void PlayerCharacter::ClearPrison()
	{
		using FuncType = decltype(&PlayerCharacter::ClearPrison);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::ClearPrison);
		std::invoke(FUNC, this);
	}

	void PlayerCharacter::EnableRadio(bool a_enable)
	{
		using FuncType = decltype(&PlayerCharacter::EnableRadio);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::EnableRadio);
		std::invoke(FUNC, this, a_enable);
	}

	auto PlayerCharacter::GetDifficultyLevel() const -> DifficultyLevel
	{
		using FuncType = decltype(&PlayerCharacter::GetDifficultyLevel);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::GetDifficultyLevel);
		return std::invoke(FUNC, this);
	}

	auto PlayerCharacter::HandlePositionPlayerRequest() -> bool
	{
		using FuncType = decltype(&PlayerCharacter::HandlePositionPlayerRequest);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::HandlePositionPlayerRequest);
		return std::invoke(FUNC, this);
	}

	auto PlayerCharacter::HasLOSToTarget(Actor* a_targetRef, bool& a_pickPerformed) -> bool
	{
		using FuncType = decltype(&PlayerCharacter::HasLOSToTarget);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::HasLOSToTarget);
		return std::invoke(FUNC, this, a_targetRef, a_pickPerformed);
	}

	auto PlayerCharacter::IsGodMode() const -> bool
	{
		using FuncType = decltype(&PlayerCharacter::IsGodMode);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::IsGodMode);
		return std::invoke(FUNC, this);
	}

	auto PlayerCharacter::IsHolotapePlaying(BGSNote* a_holotape) const -> bool
	{
		using FuncType = decltype(&PlayerCharacter::IsHolotapePlaying);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::IsHolotapePlaying);
		return std::invoke(FUNC, this, a_holotape);
	}

	auto PlayerCharacter::IsImmortal() const -> bool
	{
		using FuncType = decltype(&PlayerCharacter::IsImmortal);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::IsImmortal);
		return std::invoke(FUNC, this);
	}

	auto PlayerCharacter::IsLockedOutOfTerminal(ObjectRefHandle a_refHandle) -> bool
	{
		if (!a_refHandle) {
			return false;
		}

		const auto* calendar = Calendar::GetSingleton();
		if (!calendar) {
			return false;
		}

		{
			const auto elapsedHours = calendar->GetElapsedHours();

			// NOLINTNEXTLINE(modernize-use-ranges)
			const auto* eraseIt = std::remove_if(
				lockedTerminals.begin(),
				lockedTerminals.end(),
				[elapsedHours](const BSTPair<const ObjectRefHandle, REX::Float32>& a_pair) noexcept -> bool {
					return a_pair.second > elapsedHours.count();
				});

			lockedTerminals.erase(eraseIt, lockedTerminals.end());
		}

		return std::ranges::any_of(
			lockedTerminals,
			[a_refHandle](const BSTPair<const ObjectRefHandle, REX::Float32>& a_pair) noexcept -> bool {
				return a_pair.first == a_refHandle;
			});
	}

	auto PlayerCharacter::IsPipboyLightOn() const noexcept -> bool
	{
		return pipboyLight != nullptr;
	}

	void PlayerCharacter::LockOutOfTerminal(ObjectRefHandle a_refHandle)
	{
		if (!a_refHandle) {
			return;
		}

		const auto* calendar = Calendar::GetSingleton();
		if (!calendar) {
			return;
		}

		static const auto TerminalLockoutTimeSetting = REX::NotNull(GetINISetting("iTerminalLockoutTime:GamePlay"sv));
		if (!TerminalLockoutTimeSetting->IsInt()) {
			return;
		}

		auto terminalLockoutTime = static_cast<Calendar::Hours>(TerminalLockoutTimeSetting->GetInt());
		BGSEntryPoint::HandleEntryPoint(
			BGSEntryPoint::ENTRY_POINT::ModTerminalLockoutTime,
			this,
			terminalLockoutTime.count());

		const auto timeScale = calendar->GetTimeScale();
		terminalLockoutTime *= timeScale / static_cast<Calendar::Hours>(1);
		terminalLockoutTime += calendar->GetElapsedHours();

		lockedTerminals.emplace_back(a_refHandle, terminalLockoutTime.count());
	}

	void PlayerCharacter::PauseHolotape(BGSNote* a_holotape)
	{
		using FuncType = decltype(&PlayerCharacter::PauseHolotape);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::PauseHolotape);
		std::invoke(FUNC, this, a_holotape);
	}

	void PlayerCharacter::PlayHolotape(BGSNote* a_holotape)
	{
		using FuncType = decltype(&PlayerCharacter::PlayHolotape);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::PlayHolotape);
		std::invoke(FUNC, this, a_holotape);
	}

	void PlayerCharacter::QueueFastTravel(ObjectRefHandle a_marker, bool a_allowAutoSave)
	{
		using FuncType = decltype(&PlayerCharacter::QueueFastTravel);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::QueueFastTravel);
		std::invoke(FUNC, this, a_marker, a_allowAutoSave);
	}

	void PlayerCharacter::RemoveLastUsedPowerArmor()
	{
		using FuncType = decltype(&PlayerCharacter::RemoveLastUsedPowerArmor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::RemoveLastUsedPowerArmor);
		std::invoke(FUNC, this);
	}

	void PlayerCharacter::SelectPerk(TESFormID a_formID, std::int8_t a_rank)
	{
		using FuncType = decltype(&PlayerCharacter::SelectPerk);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SelectPerk);
		std::invoke(FUNC, this, a_formID, a_rank);
	}

	void PlayerCharacter::SetAIControlledPackage(bool a_enable)
	{
		using FuncType = decltype(&PlayerCharacter::SetAIControlledPackage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SetAIControlledPackage);
		std::invoke(FUNC, this, a_enable);
	}

	void PlayerCharacter::SetEscaping(bool a_set, bool a_escaped)
	{
		using FuncType = decltype(&PlayerCharacter::SetEscaping);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SetEscaping);
		std::invoke(FUNC, this, a_set, a_escaped);
	}

	void PlayerCharacter::SetLastDialogueInput(std::uint32_t a_dialogueOption)
	{
		using FuncType = decltype(&PlayerCharacter::SetLastDialogueInput);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SetLastDialogueInput);
		std::invoke(FUNC, this, a_dialogueOption);
	}

	void PlayerCharacter::SetPerkCount(std::uint8_t a_count)
	{
		using FuncType = decltype(&PlayerCharacter::SetPerkCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SetPerkCount);
		std::invoke(FUNC, this, a_count);
	}

	void PlayerCharacter::SetTintingData(std::uint16_t a_uniqueID, REX::Float32 a_value, std::uint32_t a_color)
	{
		using FuncType = decltype(&PlayerCharacter::SetTintingData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SetTintingData);
		std::invoke(FUNC, this, a_uniqueID, a_value, a_color);
	}

	void PlayerCharacter::SetVATSCriticalCount(std::uint32_t a_critCount)
	{
		using FuncType = decltype(&PlayerCharacter::SetVATSCriticalCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::SetVATSCriticalCount);
		std::invoke(FUNC, this, a_critCount);
	}

	void PlayerCharacter::ShowPipboyLight(bool a_show, bool a_skipEffects)
	{
		using FuncType = decltype(&PlayerCharacter::ShowPipboyLight);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::ShowPipboyLight);
		std::invoke(FUNC, this, a_show, a_skipEffects);
	}

	void PlayerCharacter::StopHolotape(BGSNote* a_holotape)
	{
		using FuncType = decltype(&PlayerCharacter::PauseHolotape);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::StopHolotape);
		std::invoke(FUNC, this, a_holotape);
	}
}

namespace RE
{
	auto IsPlayerInDialogue() -> bool
	{
		using FuncType = decltype(&IsPlayerInDialogue);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacter::IsPlayerInDialogue);
		return std::invoke(FUNC);
	}
}
