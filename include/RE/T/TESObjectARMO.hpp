#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BGSBipedObjectForm.hpp"
#include "RE/B/BGSBlockBashData.hpp"
#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSInstanceNamingRulesForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/T/TESBipedModelForm.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESEnchantableForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESRaceForm.hpp"

namespace RE
{
	enum class STAGGER_MAGNITUDE : std::int32_t;

	class __declspec(novtable) TESObjectARMO
		: public TESBoundObject,			// 000
		  public TESFullName,				// 068
		  public TESRaceForm,				// 078
		  public TESEnchantableForm,		// 088
		  public BGSDestructibleObjectForm, // 0A0
		  public BGSPickupPutdownSounds,	// 0B0
		  public TESBipedModelForm,			// 0C8
		  public BGSEquipType,				// 1D0
		  public BGSBipedObjectForm,		// 1E0
		  public BGSBlockBashData,			// 1F0
		  public BGSKeywordForm,			// 208
		  public TESDescription,			// 228
		  public BGSInstanceNamingRulesForm // 240
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectARMO };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectARMO };
		inline static constexpr auto FORM_TYPE{ FormType::kArmor };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kShield = 1 << 6,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class __declspec(novtable) InstanceData
			: public TBO_InstanceData // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::TESObjectARMO__InstanceData };
			inline static constexpr auto VTABLE{ VTABLE::TESObjectARMO__InstanceData };

			~InstanceData() override; // 00

			// members
			BSTArray<EnchantmentItem*>* enchantments;									// 10
			BSTArray<BGSMaterialSwap*>* materialSwaps;									// 18
			BGSBlockBashData* blockBashData;											// 20
			BGSKeywordForm* keywords;													// 28
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 30
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues; // 38
			REX::Float32 weight;														// 40
			REX::Float32 colorRemappingIndex;											// 44
			std::uint32_t value;														// 48
			std::uint32_t health;														// 4C
			REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerRating;					// 50
			std::uint16_t rating;														// 54
			std::uint16_t index;														// 56
		};
		static_assert(sizeof(InstanceData) == 0x58);

		class ArmorAddon
		{
		public:
			// members
			std::uint16_t index;	   // 00
			TESObjectARMA* armorAddon; // 08
		};
		static_assert(sizeof(ArmorAddon) == 0x10);

		bool Protects(const ActorValueInfo* a_condition, bool a_only)
		{
			using FuncType = decltype(&TESObjectARMO::Protects);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectARMO::Protects };
			return std::invoke(FUNC, this, a_condition, a_only);
		}

		// members
		InstanceData armorData;				// 250
		BSTArray<ArmorAddon> models;		// 2A8
		TESObjectARMO* armorTemplate;		// 2C0
		BGSAttachParentArray attachParents; // 2C8
	};
	static_assert(sizeof(TESObjectARMO) == 0x2E0);
}
