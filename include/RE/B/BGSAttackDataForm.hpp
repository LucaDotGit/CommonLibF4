#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSAttackDataMap;

	class __declspec(novtable) BGSAttackDataForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAttackDataForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSAttackDataForm };

		~BGSAttackDataForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		NiPointer<BGSAttackDataMap> attackDataMap; // 08
	};
	static_assert(sizeof(BGSAttackDataForm) == 0x10);
}
