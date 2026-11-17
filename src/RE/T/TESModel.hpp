#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE::BSResource
{
	class ID;
}

namespace RE
{
	class BGSModelMaterialSwap;

	class __declspec(novtable) TESModel : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESModel;
		inline static constexpr const auto& VTABLE = VTABLE::TESModel;

		enum class ModelFlags : std::uint8_t; // To-Do

		~TESModel() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto GetModel() const -> const char*;					// 0x07 - { return model.data(); }
		virtual void SetModel(const char* a_model);						// 0x08 - { model = a_model; }
		virtual auto GetAsModelMaterialSwap() -> BGSModelMaterialSwap*; // 0x09 - { return nullptr; }

		// members
		BSFixedString model;							   // 0x08
		BSResource::ID* textures;						   // 0x10
		BSResource::ID* materials;						   // 0x18
		std::uint32_t* addons;							   // 0x20
		std::int8_t numTextures;						   // 0x28
		std::int8_t numTexturesSRGB;					   // 0x29
		std::int8_t numAddons;							   // 0x2A
		std::int8_t numMaterials;						   // 0x2B
		REX::EnumSet<ModelFlags, std::uint8_t> modelFlags; // 0x2C
	};

	static_assert(sizeof(TESModel) == 0x30);
}
