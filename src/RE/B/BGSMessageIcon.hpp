#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/T/TESIcon.hpp"

namespace RE
{
	class __declspec(novtable) BGSMessageIcon : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMessageIcon;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMessageIcon;

		~BGSMessageIcon() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		auto GetMessageIconTextureName() const noexcept -> BSFixedString
		{
			return icon.textureName;
		}

		void SetMessageIconTextureName(BSFixedString a_texture)
		{
			icon.textureName = std::move(a_texture);
		}

		// members
		TESIcon icon; // 0x08
	};

	static_assert(sizeof(BGSMessageIcon) == 0x18);
}
