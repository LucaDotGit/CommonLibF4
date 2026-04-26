#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESTexture
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESTexture };
		inline static constexpr auto VTABLE{ VTABLE::TESTexture };

		~TESTexture() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual std::uint32_t GetMaxAllowedSize();							// 07 - { return 0; }
		virtual const char* GetAsNormalFile(BSString& a_outFilename) const; // 08
		virtual const char* GetDefaultPath() const;							// 09 - { return "Textures\\"; }

		// members
		BSFixedString textureName; // 08
	};
	static_assert(sizeof(TESTexture) == 0x10);
}
