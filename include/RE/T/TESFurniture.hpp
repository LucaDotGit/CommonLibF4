#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESObjectACTI.hpp"
#include "RE/W/WorkbenchData.hpp"

namespace RE
{
	class BSFurnitureMarker;
	class TESContainer;

	class __declspec(novtable) TESFurniture
		: public TESObjectACTI // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESFurniture };
		inline static constexpr auto VTABLE{ VTABLE::TESFurniture };
		inline static constexpr auto FORM_TYPE{ FormType::kFurniture };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kHasContainer = 1 << 2,
				kDeleted = 1 << 5,
				kIsPerch = 1 << 7,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16,
				kIsMarker = 1 << 23,
				kIsPowerArmor = 1 << 25,
				kMustExitToTalk = 1 << 28,
				kChildCanUse = 1 << 29
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kSit0 = 1 << 0,
			kSit1 = 1 << 1,
			kSit2 = 1 << 2,
			kSit3 = 1 << 3,
			kSit4 = 1 << 4,
			kSit5 = 1 << 5,
			kSit6 = 1 << 6,
			kSit7 = 1 << 7,
			kSit8 = 1 << 8,
			kSit9 = 1 << 9,
			kSit10 = 1 << 10,
			kSit11 = 1 << 11,
			kSit12 = 1 << 12,
			kSit13 = 1 << 13,
			kSit14 = 1 << 14,
			kSit15 = 1 << 15,
			kSit16 = 1 << 16,
			kSit17 = 1 << 17,
			kSit18 = 1 << 18,
			kSit19 = 1 << 19,
			kSit20 = 1 << 20,
			kSit21 = 1 << 21,
			kSit22 = 1 << 22,
			kSit23 = 1 << 23,
			kDisablesActivation = 1 << 25,
			kIsPerch = 1 << 26,
			kMustExitToTalk = 1 << 27,
			kSit28 = 1 << 28,
			kCanLean = 1 << 29,
			kCanSit = 1 << 30,
			kCanSleep = 1ui32 << 31
		};

		class EntryPointData
		{
		public:
			// members
			std::uint32_t entryPoint; // 00
			std::uint32_t flags;	  // 04
		};
		static_assert(sizeof(EntryPointData) == 0x08);

		[[nodiscard]] TESContainer* GetContainer()
		{
			using FuncType = decltype(&TESFurniture::GetContainer);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFurniture::GetContainer };
			return std::invoke(FUNC, this);
		}

		// members
		BSTArray<EntryPointData> entryPointDataArray;	   // 148
		BGSAttachParentArray attachParents;				   // 160
		WorkbenchData workbenchData;					   // 178
		REX::EnumSet<Flags, std::uint32_t> furnitureFlags; // 17C
		TESForm* associatedForm;						   // 180
		BSTArray<BSFurnitureMarker> markersArray;		   // 188
	};
	static_assert(sizeof(TESFurniture) == 0x1A0);
}
