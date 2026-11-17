#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESRaceForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESRaceForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESRaceForm;

		~TESRaceForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto SwitchRace(TESRace* a_race) -> bool; // 0x07 - { formRace = a_race; return true; }

		[[nodiscard]]
		auto GetFormRace() const noexcept -> TESRace*
		{
			return formRace;
		}

		void SetFormRace(TESRace* a_race) noexcept
		{
			formRace = a_race;
		}

		// members
		TESRace* formRace; // 0x08
	};

	static_assert(sizeof(TESRaceForm) == 0x10);
}
