#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESRaceForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESRaceForm };
		inline static constexpr auto VTABLE{ VTABLE::TESRaceForm };

		~TESRaceForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual bool SwitchRace(TESRace* a_race); // 07 { formRace = a_race; return true; }

		[[nodiscard]] TESRace* GetFormRace() const noexcept { return formRace; }
		void SetFormRace(TESRace* a_race) noexcept { formRace = a_race; }

		// members
		TESRace* formRace; // 08
	};
	static_assert(sizeof(TESRaceForm) == 0x10);
}
