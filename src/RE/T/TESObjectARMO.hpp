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

	class __declspec(novtable) TESObjectARMO :
		public TESBoundObject,			  // 0x000
		public TESFullName,				  // 0x068
		public TESRaceForm,				  // 0x078
		public TESEnchantableForm,		  // 0x088
		public BGSDestructibleObjectForm, // 0x0A0
		public BGSPickupPutdownSounds,	  // 0x0B0
		public TESBipedModelForm,		  // 0x0C8
		public BGSEquipType,			  // 0x1D0
		public BGSBipedObjectForm,		  // 0x1E0
		public BGSBlockBashData,		  // 0x1F0
		public BGSKeywordForm,			  // 0x208
		public TESDescription,			  // 0x228
		public BGSInstanceNamingRulesForm // 0x240
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectARMO;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectARMO;
		inline static constexpr auto FORM_TYPE = FormType::Armor;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NonPlayable = 1 << 2,
				Deleted = 1 << 5,
				Shield = 1 << 6,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class __declspec(novtable) InstanceData : public TBO_InstanceData // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::TESObjectARMO__InstanceData;
			inline static constexpr const auto& VTABLE = VTABLE::TESObjectARMO__InstanceData;

			~InstanceData() override; // 0x00

			// members
			BSTArray<EnchantmentItem*>* enchantments;									// 0x10
			BSTArray<BGSMaterialSwap*>* materialSwaps;									// 0x18
			BGSBlockBashData* blockBashData;											// 0x20
			BGSKeywordForm* keywords;													// 0x28
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 0x30
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues; // 0x38
			REX::Float32 weight;														// 0x40
			REX::Float32 colorRemappingIndex;											// 0x44
			std::uint32_t value;														// 0x48
			std::uint32_t health;														// 0x4C
			REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerRating;					// 0x50
			std::uint16_t rating;														// 0x54
			std::uint16_t index;														// 0x56
		};

		static_assert(sizeof(InstanceData) == 0x58);

		class ArmorAddon
		{
		public:
			// members
			std::uint16_t index;	   // 0x00
			TESObjectARMA* armorAddon; // 0x08
		};

		static_assert(sizeof(ArmorAddon) == 0x10);

		~TESObjectARMO() override; // 0x00

		[[nodiscard]]
		auto Protects(const ActorValueInfo* a_condition, bool a_only) const -> bool
		{
			using FuncType = decltype(&TESObjectARMO::Protects);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectARMO::Protects);
			return std::invoke(FUNC, this, a_condition, a_only);
		}

		// members
		InstanceData armorData;				// 0x250
		BSTArray<ArmorAddon> models;		// 0x2A8
		TESObjectARMO* armorTemplate;		// 0x2C0
		BGSAttachParentArray attachParents; // 0x2C8
	};

	static_assert(sizeof(TESObjectARMO) == 0x2E0);
}
