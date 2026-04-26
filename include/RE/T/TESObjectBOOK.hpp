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
	class __declspec(novtable) TESObjectBOOK
		: public TESBoundObject,			// 000
		  public TESFullName,				// 068
		  public BGSModelMaterialSwap,		// 078
		  public TESIcon,					// 0B8
		  public TESValueForm,				// 0C8
		  public TESWeightForm,				// 0D8
		  public TESDescription,			// 0E8
		  public BGSDestructibleObjectForm, // 100
		  public BGSMessageIcon,			// 110
		  public BGSPickupPutdownSounds,	// 128
		  public BGSKeywordForm,			// 140
		  public BGSFeaturedItemMessage		// 160
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectBOOK };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectBOOK };
		inline static constexpr auto FORM_TYPE{ FormType::kBook };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kTeaches = 1 << 5,
				kRead = 1 << 6
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]] bool GetHasBeenRead() const noexcept;
		void SetHasBeenRead(bool a_value);

		// members
		OBJ_BOOK data;						// 170
		TESObjectSTAT* inventoryModel;		// 188
		TESDescription itemCardDescription; // 190
	};
	static_assert(sizeof(TESObjectBOOK) == 0x1A8);
}
