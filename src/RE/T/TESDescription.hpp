#pragma once

#include "RE/B/BGSLocalizedStringDL.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESDescription : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESDescription;
		inline static constexpr const auto& VTABLE = VTABLE::TESDescription;

		~TESDescription() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		void GetDescription(BSString& a_outString, const TESForm* a_parent = nullptr) const
		{
			using FuncType = decltype(&TESDescription::GetDescription);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESDescription::GetDescription);
			std::invoke(FUNC, this, a_outString, a_parent);
		}

		[[nodiscard]]
		static auto GetFormDescription(const TESForm* a_form) -> std::optional<BSFixedStringCS>;

		// members
		std::uint32_t fileOffset;			  // 0x08
		std::uint32_t chunkOffset;			  // 0x0C
		BGSLocalizedStringDL descriptionText; // 0x10
	};

	static_assert(sizeof(TESDescription) == 0x18);
}
