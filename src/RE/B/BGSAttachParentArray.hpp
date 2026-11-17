#pragma once

#include "RE/B/BGSTypedKeywordValue.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSAttachParentArray :
		public BaseFormComponent,								   // 0x00
		public BGSTypedKeywordValueArray<KeywordType::AttachPoint> // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAttachParentArray;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAttachParentArray;

		~BGSAttachParentArray() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		void SetParentGroupNumber(BGSKeyword* a_parent, std::uint32_t a_groupID)
		{
			using FuncType = decltype(&BGSAttachParentArray::SetParentGroupNumber);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSAttachParentArray::SetParentGroupNumber);
			std::invoke(FUNC, this, a_parent, a_groupID);
		}
	};

	static_assert(sizeof(BGSAttachParentArray) == 0x18);
}
