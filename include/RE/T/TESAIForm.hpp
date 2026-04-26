#pragma once

#include "RE/A/AIDATA_GAME.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/P/PackageList.hpp"

namespace RE
{
	class __declspec(novtable) TESAIForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESAIForm };
		inline static constexpr auto VTABLE{ VTABLE::TESAIForm };

		~TESAIForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		AIDATA_GAME aiData;		// 08
		PackageList aiPackList; // 18
	};
	static_assert(sizeof(TESAIForm) == 0x28);
}
