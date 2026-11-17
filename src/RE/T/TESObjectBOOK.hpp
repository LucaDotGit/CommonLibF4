#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSFeaturedItemMessage.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/O/OBJ_BOOK.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectBOOK :
		public TESBoundObject,			  // 0x000
		public TESFullName,				  // 0x068
		public BGSModelMaterialSwap,	  // 0x078
		public TESIcon,					  // 0x0B8
		public TESValueForm,			  // 0x0C8
		public TESWeightForm,			  // 0x0D8
		public TESDescription,			  // 0x0E8
		public BGSDestructibleObjectForm, // 0x100
		public BGSMessageIcon,			  // 0x110
		public BGSPickupPutdownSounds,	  // 0x128
		public BGSKeywordForm,			  // 0x140
		public BGSFeaturedItemMessage	  // 0x160
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectBOOK;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectBOOK;
		inline static constexpr auto FORM_TYPE = FormType::Book;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Teaches = 1 << 5,
				Read = 1 << 6
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESObjectBOOK() override; // 0x00

		[[nodiscard]]
		auto GetHasBeenRead() const noexcept -> bool;
		void SetHasBeenRead(bool a_value);

		// members
		OBJ_BOOK data;						// 0x170
		TESObjectSTAT* inventoryModel;		// 0x188
		TESDescription itemCardDescription; // 0x190
	};

	static_assert(sizeof(TESObjectBOOK) == 0x1A8);
}
