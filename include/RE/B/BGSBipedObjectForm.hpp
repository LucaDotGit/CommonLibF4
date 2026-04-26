#pragma once

#include "RE/B/BIPED_MODEL.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSBipedObjectForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSBipedObjectForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSBipedObjectForm };

		~BGSBipedObjectForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual bool FillsBipedSlot(std::int32_t a_bipedSlot) const; // 06

		// members
		BIPED_MODEL bipedModelData; // 08
	};
	static_assert(sizeof(BGSBipedObjectForm) == 0x10);
}
