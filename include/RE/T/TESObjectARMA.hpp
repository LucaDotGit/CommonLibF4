#pragma once

#include "RE/B/BGSBipedObjectForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/O/OBJ_ARMA.hpp"
#include "RE/S/SEX.hpp"
#include "RE/T/TESObject.hpp"
#include "RE/T/TESRaceForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectARMA
		: public TESObject,			// 000
		  public TESRaceForm,		// 020
		  public BGSBipedObjectForm // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectARMA };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectARMA };
		inline static constexpr auto FORM_TYPE{ FormType::kArmorAddon };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kNoUnderArmorScaling = 1 << 6,
				kHasSculpData = 1 << 9,
				kIgnored = 1 << 12,
				kHighResFirstPersonOnly = 1 << 30
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		~TESObjectARMA() override; // 00

		// members
		OBJ_ARMA data;																						  // 040
		std::array<BGSModelMaterialSwap, std::to_underlying(SEX::kTotal)> bipedModels;						  // 050
		std::array<BGSModelMaterialSwap, std::to_underlying(SEX::kTotal)> bipedModelFacebones;				  // 0D0
		std::array<BGSModelMaterialSwap, std::to_underlying(SEX::kTotal)> bipedModel1stPerson;				  // 150
		std::array<BGSTextureSet*, std::to_underlying(SEX::kTotal)> skinTextures;							  // 1D0
		std::array<BGSListForm*, std::to_underlying(SEX::kTotal)> skinTextureSwapLists;						  // 1E0
		BSTArray<TESRace*> additionalRaces;																	  // 1F0
		BGSFootstepSet* footstepSet;																		  // 208
		BGSArtObject* artObject;																			  // 210
		std::array<BSTHashMap<BSFixedString, NiPoint3>*, std::to_underlying(SEX::kTotal)> boneScaleModifiers; // 218
	};
	static_assert(sizeof(TESObjectARMA) == 0x228);
}
