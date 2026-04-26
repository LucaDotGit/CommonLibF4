#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/T/TESIcon.hpp"

namespace RE
{
	class __declspec(novtable) BGSMessageIcon
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMessageIcon };
		inline static constexpr auto VTABLE{ VTABLE::BGSMessageIcon };

		~BGSMessageIcon() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] const BSFixedString& GetMessageIconTextureName() const noexcept { return icon.textureName; }
		void SetMessageIconTextureName(BSFixedString a_texture) { icon.textureName = std::move(a_texture); }

		// members
		TESIcon icon; // 08
	};
	static_assert(sizeof(BGSMessageIcon) == 0x18);
}
