#pragma once

#include "RE/A/AIDATA_GAME.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/P/PackageList.hpp"

namespace RE
{
	class __declspec(novtable) TESAIForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESAIForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESAIForm;

		~TESAIForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// members
		AIDATA_GAME aiData;		// 0x08
		PackageList aiPackList; // 0x18
	};

	static_assert(sizeof(TESAIForm) == 0x28);
}
