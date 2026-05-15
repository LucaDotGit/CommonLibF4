#pragma once

#include "RE/B/BGSLocalizedStringDL.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESDescription
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESDescription };
		inline static constexpr auto VTABLE{ VTABLE::TESDescription };

		~TESDescription() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		void GetDescription(BSString& a_outString, const TESForm* a_parent = nullptr) const
		{
			using FuncType = decltype(&TESDescription::GetDescription);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDescription::GetDescription };
			std::invoke(FUNC, this, a_outString, a_parent);
		}

		[[nodiscard]] static auto GetFormDescription(const TESForm* a_form)
			-> std::optional<BSFixedStringCS>;

		// members
		std::uint32_t fileOffset;			  // 08
		std::uint32_t chunkOffset;			  // 0C
		BGSLocalizedStringDL descriptionText; // 10
	};
	static_assert(sizeof(TESDescription) == 0x18);
}
