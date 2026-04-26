#pragma once

#include "RE/B/BGSBipedObjectForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/O/OBJ_ARMA.hpp"
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
		OBJ_ARMA data; // 040
		union
		{
			std::array<BGSModelMaterialSwap, 2> bipedModels;
			struct
			{
				BGSModelMaterialSwap maleBipedModel;
				BGSModelMaterialSwap femaleBipedModel;
			};
		}; // 050
		union
		{
			std::array<BGSModelMaterialSwap, 2> bipedModelFacebones;
			struct
			{
				BGSModelMaterialSwap maleModelFacebones;
				BGSModelMaterialSwap femaleModelFacebones;
			};
		}; // 0D0
		union
		{
			std::array<BGSModelMaterialSwap, 2> bipedModel1stPerson;
			struct
			{
				BGSModelMaterialSwap maleBipedModel1stPerson;
				BGSModelMaterialSwap femaleBipedModel1stPerson;
			};
		}; // 150
		union
		{
			std::array<BGSTextureSet*, 2> skinTextures;
			struct
			{
				BGSTextureSet* maleSkinTexture;
				BGSTextureSet* femaleSkinTexture;
			};
		}; // 1D0
		union
		{
			std::array<BGSListForm*, 2> skinTextureSwapLists;
			struct
			{
				BGSListForm* maleSkinTextureSwapList;
				BGSListForm* femaleSkinTextureSwapList;
			};
		}; // 1E0
		BSTArray<TESRace*> additionalRaces; // 1F0
		BGSFootstepSet* footstepSet;		// 208
		BGSArtObject* artObject;			// 210
		union
		{
			std::array<BSTHashMap<BSFixedString, NiPoint3>*, 2> boneScaleModifiers;
			struct
			{
				BSTHashMap<BSFixedString, NiPoint3>* maleBoneScaleModifiers;
				BSTHashMap<BSFixedString, NiPoint3>* femaleBoneScaleModifiers;
			};
		}; // 218
	};
	static_assert(sizeof(TESObjectARMA) == 0x228);
}
