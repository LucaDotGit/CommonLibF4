#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESObjectACTI.hpp"
#include "RE/W/WorkbenchData.hpp"

namespace RE
{
	class BSFurnitureMarker;
	class TESContainer;

	class __declspec(novtable) TESFurniture : public TESObjectACTI // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESFurniture;
		inline static constexpr const auto& VTABLE = VTABLE::TESFurniture;
		inline static constexpr auto FORM_TYPE = FormType::Furniture;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				HasContainer = 1 << 2,
				Deleted = 1 << 5,
				IsPerch = 1 << 7,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16,
				IsMarker = 1 << 23,
				IsPowerArmor = 1 << 25,
				MustExitToTalk = 1 << 28,
				ChildCanUse = 1 << 29
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			Sit0 = 1 << 0,
			Sit1 = 1 << 1,
			Sit2 = 1 << 2,
			Sit3 = 1 << 3,
			Sit4 = 1 << 4,
			Sit5 = 1 << 5,
			Sit6 = 1 << 6,
			Sit7 = 1 << 7,
			Sit8 = 1 << 8,
			Sit9 = 1 << 9,
			Sit10 = 1 << 10,
			Sit11 = 1 << 11,
			Sit12 = 1 << 12,
			Sit13 = 1 << 13,
			Sit14 = 1 << 14,
			Sit15 = 1 << 15,
			Sit16 = 1 << 16,
			Sit17 = 1 << 17,
			Sit18 = 1 << 18,
			Sit19 = 1 << 19,
			Sit20 = 1 << 20,
			Sit21 = 1 << 21,
			Sit22 = 1 << 22,
			Sit23 = 1 << 23,
			DisablesActivation = 1 << 25,
			IsPerch = 1 << 26,
			MustExitToTalk = 1 << 27,
			Sit28 = 1 << 28,
			CanLean = 1 << 29,
			CanSit = 1 << 30,
			CanSleep = static_cast<std::uint32_t>(1) << 31
		};

		class EntryPointData
		{
		public:
			// members
			std::uint32_t entryPoint; // 0x00
			std::uint32_t flags;	  // 0x04
		};

		static_assert(sizeof(EntryPointData) == 0x08);

		~TESFurniture() override; // 0x00

		[[nodiscard]]
		auto GetContainer() const -> TESContainer*
		{
			using FuncType = decltype(&TESFurniture::GetContainer);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESFurniture::GetContainer);
			return std::invoke(FUNC, this);
		}

		// members
		BSTArray<EntryPointData> entryPointDataArray;	   // 0x148
		BGSAttachParentArray attachParents;				   // 0x160
		WorkbenchData workbenchData;					   // 0x178
		REX::EnumSet<Flags, std::uint32_t> furnitureFlags; // 0x17C
		TESForm* associatedForm;						   // 0x180
		BSTArray<BSFurnitureMarker> markersArray;		   // 0x188
	};

	static_assert(sizeof(TESFurniture) == 0x1A0);
}
