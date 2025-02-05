#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/TESCondition.hpp"
#include "RE/Bethesda/TESForms.hpp"

namespace RE
{
	class TESFile;
	class TESForm;

	namespace BGSCharacterTint
	{
		enum BlendOp : std::uint32_t
		{
			kDefault = 0,
			kMultiply = 1,
			kOverlay = 2,
			kSoftLight = 3,
			kHardLight = 4,
			kTotal = 5
		};

		enum EntryType : std::uint32_t
		{
			kMask = 0x0,
			kPalette = 0x1,
			kTexture = 0x2,
			kUnknown = 0x3
		};

		enum class EntrySlot
		{
			kForeheadMask,
			kEyesMask,
			kNoseMask,
			kEarsMask,
			kCheeksMask,
			kMouthMask,
			kNeckMask,
			kLipColor,
			kCheekColor,
			kEyeliner,
			kEyeSocketUpper,
			kEyeSocketLower,
			kSkinTone,
			kPaint,
			kLaughLines,
			kCheekColorLower,
			kNose,
			kChin,
			kNeck,
			kForehead,
			kDirt,
			kScars,
			kFaceDetail,
			kBrow,
			kWrinkles,
			kBeard
		};

		namespace Template
		{
			class __declspec(novtable) Entry
			{
			public:
				inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__Template__Entry };
				inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Template__Entry };

				enum class Flags : std::uint32_t
				{
					kNone = 0x0,
					kOnOffOnly = 0x1,
					kIsChargenDetaul = 0x2,
					kTakesSkinTone = 0x4
				};

				virtual ~Entry(); // 00

				// add
				virtual float GetDefaultValue() { return 0.0F; }				  // 01
				virtual void InitItem(TESForm* a_owner);						  // 02
				virtual void CopyData(BGSCharacterTint::Template::Entry* a_copy); // 03
				virtual void LoadImpl(TESFile* a_file) = 0;						  // 04

				// members
				BGSLocalizedString name;									// 08
				TESCondition chargenConditions;								// 10
				REX::Enum<BGSCharacterTint::EntrySlot, std::uint32_t> slot; // 18
				const std::uint16_t uniqueID{ 0 };							// 1C
				REX::EnumSet<Flags, std::uint8_t> flags;					// 1E
			};
			static_assert(sizeof(Entry) == 0x20);

			class __declspec(novtable) Palette
				: public BGSCharacterTint::Template::Entry
			{
			public:
				inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__Template__Palette };
				inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Template__Palette };

				struct ColorValue
				{
					BGSColorForm* color;			   // 00
					float value;					   // 08
					BGSCharacterTint::BlendOp blendOp; // 0C
					std::uint16_t swatchID;			   // 01
				};
				static_assert(sizeof(ColorValue) == 0x18);

				// Members
				BSFixedString maskTextureName;
				std::uint32_t defaultIndex;
				BSTArray<BGSCharacterTint::Template::Palette::ColorValue> colorValues;
			};
			static_assert(sizeof(Palette) == 0x48);

			class Group
			{
			public:
				// members
				BGSLocalizedString name;							  // 00
				std::uint32_t id;									  // 08
				std::uint32_t chargenIndex;							  // 0C
				BSTArray<BGSCharacterTint::Template::Entry*> entries; // 10
			};
			static_assert(sizeof(Group) == 0x28);

			class Groups
			{
			public:
				// members
				BSTArray<Group*> groups; // 00
			};
			static_assert(sizeof(Groups) == 0x18);
		}

		class __declspec(novtable) Entry
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__Entry };
			inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Entry };

			virtual ~Entry(); // 00

			virtual bool GetIsIdentical(const Entry* entry);										// 08
			virtual bool CopyData(const Entry entry);												// 10
			virtual bool SetFromTemplateDefault(const BGSCharacterTint::Template::Entry* entry);	// 18
			virtual bool GetMatchesTemplateDefault(const BGSCharacterTint::Template::Entry* entry); // 20
			virtual BGSCharacterTint::EntryType GetType();											// 28

			// Members
			BGSCharacterTint::Template::Entry* templateEntry; // 08
			const std::uint16_t idLink;						  // 10
			std::uint8_t tingingValue;						  // 12
		};
		static_assert(sizeof(Entry) == 0x18);

		class __declspec(novtable) MaskEntry
			: public BGSCharacterTint::Entry
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__MaskEntry };
			inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__MaskEntry };
		};
		static_assert(sizeof(MaskEntry) == 0x18);

		class __declspec(novtable) PaletteEntry
			: public BGSCharacterTint::MaskEntry
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__PaletteEntry };
			inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__PaletteEntry };

			// members
			std::uint32_t tintingColor; // 18
			std::uint16_t swatchID;		// 1C
		};
		static_assert(sizeof(PaletteEntry) == 0x20);

		class __declspec(novtable) TextureSetEntry
			: public BGSCharacterTint::Entry
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__TextureSetEntry };
			inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__TextureSetEntry };
		};
		static_assert(sizeof(TextureSetEntry) == 0x18);

		class Entries
		{
		public:
			BSTArray<BGSCharacterTint::Entry*> entriesA;
		};
		static_assert(sizeof(Entries) == 0x18);
	}
}
