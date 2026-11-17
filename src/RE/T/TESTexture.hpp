#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESTexture : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESTexture;
		inline static constexpr const auto& VTABLE = VTABLE::TESTexture;

		~TESTexture() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto GetMaxAllowedSize() -> std::uint32_t;							// 0x07 - { return 0; }
		virtual auto GetAsNormalFile(BSString& a_outFilename) const -> const char*; // 0x08
		virtual auto GetDefaultPath() const -> const char*;							// 0x09 - { return "Textures\\"; }

		// members
		BSFixedString textureName; // 0x08
	};

	static_assert(sizeof(TESTexture) == 0x10);
}
