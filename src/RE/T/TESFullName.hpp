#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESFullName : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESFullName;
		inline static constexpr const auto& VTABLE = VTABLE::TESFullName;

		~TESFullName() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto GetFullNameLength() const -> std::uint32_t; // 0x07 - { return fullName.size(); }
		virtual auto GetFullName() const -> const char*;		 // 0x08 - { return fullName.data(); }

		[[nodiscard]]
		static auto GetSparseFullNameMap() noexcept -> BSTHashMap<const TESForm*, BGSLocalizedString>&;

		[[nodiscard]]
		static auto GetFormFullName(const TESForm* a_form) -> std::optional<BGSLocalizedString>;
		static auto SetFormFullName(TESForm* a_form, const BGSLocalizedString& a_fullName) -> bool;

		[[nodiscard]]
		static auto GetFormFullOrDisplayName(const TESForm* a_form) -> std::optional<BGSLocalizedString>;
		static auto SetFormFullOrDisplayName(TESForm* a_form, const BGSLocalizedString& a_name) -> bool;

		// members
		BGSLocalizedString fullName; // 0x08
	};

	static_assert(sizeof(TESFullName) == 0x10);
}
