#pragma once

#include "RE/B/BGSTypedKeywordValue.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSAttachParentArray
		: public BaseFormComponent,									  // 00
		  public BGSTypedKeywordValueArray<KeywordType::kAttachPoint> // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAttachParentArray };
		inline static constexpr auto VTABLE{ VTABLE::BGSAttachParentArray };

		~BGSAttachParentArray() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		void SetParentGroupNumber(BGSKeyword* a_parent, std::uint32_t a_groupID)
		{
			using FuncType = decltype(&BGSAttachParentArray::SetParentGroupNumber);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSAttachParentArray::SetParentGroupNumber };
			FUNC(this, a_parent, a_groupID);
		}
	};
	static_assert(sizeof(BGSAttachParentArray) == 0x18);
}
