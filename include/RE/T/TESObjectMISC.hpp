#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSFeaturedItemMessage.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/S/SimpleArray.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectMISC
		: public TESBoundObject,			// 000
		  public TESFullName,				// 068
		  public BGSModelMaterialSwap,		// 078
		  public TESIcon,					// 0B8
		  public TESValueForm,				// 0C8
		  public TESWeightForm,				// 0D8
		  public BGSDestructibleObjectForm, // 0E8
		  public BGSMessageIcon,			// 0F8
		  public BGSPickupPutdownSounds,	// 110
		  public BGSKeywordForm,			// 128
		  public BGSFeaturedItemMessage		// 148
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectMISC };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectMISC };
		inline static constexpr auto FORM_TYPE{ FormType::kMiscObject };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kCalculateFromComponents = 1 << 11,
				kIgnored = 1 << 12,
				kPackInUseOnly = 1 << 13
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// add
		virtual void SaveImpl();									// 67 - { return; }
		virtual void LoadImpl(TESFile* a_file, CHUNK_ID a_chunkID); // 68 - { return; }

		[[nodiscard]] auto GetComponents() const noexcept -> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>;
		void SetComponents(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_components);

		[[nodiscard]] auto GetDisplayIndices() noexcept -> std::optional<std::span<std::uint8_t>>;
		[[nodiscard]] auto GetDisplayIndices() const noexcept -> std::optional<std::span<const std::uint8_t>>;
		void SetDisplayIndices(std::span<const std::uint8_t> a_indices);

		// members
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* componentData; // 158
		SimpleArray<std::uint8_t> displayIndices;									  // 160
	};
	static_assert(sizeof(TESObjectMISC) == 0x168);
}
