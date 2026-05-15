#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESFullName
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESFullName };
		inline static constexpr auto VTABLE{ VTABLE::TESFullName };

		~TESFullName() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual std::uint32_t GetFullNameLength() const; // 07 - { return fullName.size(); }
		virtual const char* GetFullName() const;		 // 08 - { return fullName.data(); }

		[[nodiscard]] static auto GetSparseFullNameMap()
			-> BSTHashMap<const TESForm*, BGSLocalizedString>&;

		[[nodiscard]] static auto GetFormFullName(const TESForm* a_form)
			-> std::optional<BGSLocalizedString>;
		static bool SetFormFullName(TESForm* a_form, const BGSLocalizedString& a_fullName, bool a_addChange = true);

		[[nodiscard]] static auto GetFormFullOrDisplayName(const TESForm* a_form)
			-> std::optional<BGSLocalizedString>;
		static bool SetFormFullOrDisplayName(TESForm* a_form, const BGSLocalizedString& a_name, bool a_addChange = true);

		// members
		BGSLocalizedString fullName; // 08
	};
	static_assert(sizeof(TESFullName) == 0x10);
}
