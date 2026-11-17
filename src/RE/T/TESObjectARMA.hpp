#pragma once

#include "RE/B/BGSBipedObjectForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/O/OBJ_ARMA.hpp"
#include "RE/S/SEX.hpp"
#include "RE/T/TESObject.hpp"
#include "RE/T/TESRaceForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectARMA :
		public TESObject,		  // 0x000
		public TESRaceForm,		  // 0x020
		public BGSBipedObjectForm // 0x030
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectARMA;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectARMA;
		inline static constexpr auto FORM_TYPE = FormType::ArmorAddon;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				NoUnderArmorScaling = 1 << 6,
				HasSculpData = 1 << 9,
				Ignored = 1 << 12,
				HighResFirstPersonOnly = 1 << 30
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESObjectARMA() override; // 0x00

		// members
		OBJ_ARMA data;																						  // 0x040
		std::array<BGSModelMaterialSwap, std::to_underlying(SEX::_Count)> bipedModels;						  // 0x050
		std::array<BGSModelMaterialSwap, std::to_underlying(SEX::_Count)> bipedModelFacebones;				  // 0x0D0
		std::array<BGSModelMaterialSwap, std::to_underlying(SEX::_Count)> bipedModel1stPerson;				  // 0x150
		std::array<BGSTextureSet*, std::to_underlying(SEX::_Count)> skinTextures;							  // 0x1D0
		std::array<BGSListForm*, std::to_underlying(SEX::_Count)> skinTextureSwapLists;						  // 0x1E0
		BSTArray<TESRace*> additionalRaces;																	  // 0x1F0
		BGSFootstepSet* footstepSet;																		  // 0x208
		BGSArtObject* artObject;																			  // 0x210
		std::array<BSTHashMap<BSFixedString, NiPoint3>*, std::to_underlying(SEX::_Count)> boneScaleModifiers; // 0x218
	};

	static_assert(sizeof(TESObjectARMA) == 0x228);
}
