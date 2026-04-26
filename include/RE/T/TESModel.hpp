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

	class __declspec(novtable) TESModel
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESModel };
		inline static constexpr auto VTABLE{ VTABLE::TESModel };

		~TESModel() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual const char* GetModel() const;					// 07 - { return model.data(); }
		virtual void SetModel(const char* a_model);				// 08 - { model = a_model; }
		virtual BGSModelMaterialSwap* GetAsModelMaterialSwap(); // 09 - { return nullptr; }

		// members
		BSFixedString model;		 // 08
		BSResource::ID* textures;	 // 10
		BSResource::ID* materials;	 // 18
		std::uint32_t* addons;		 // 20
		std::int8_t numTextures;	 // 28
		std::int8_t numTexturesSRGB; // 29
		std::int8_t numAddons;		 // 2A
		std::int8_t numMaterials;	 // 2B
		std::int8_t flags;			 // 2C
	};
	static_assert(sizeof(TESModel) == 0x30);
}
