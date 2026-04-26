#pragma once

#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSNote
		: public TESBoundObject,		// 000
		  public TESWeightForm,			// 068
		  public TESValueForm,			// 078
		  public TESModel,				// 088
		  public TESFullName,			// 0B8
		  public TESIcon,				// 0C8
		  public BGSPickupPutdownSounds // 0D8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSNote };
		inline static constexpr auto VTABLE{ VTABLE::BGSNote };
		inline static constexpr auto FORM_TYPE{ FormType::kNote };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kRead = 1ui32 << 31
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

		enum class NOTE_TYPE : std::int8_t
		{
			kVoice = 0,
			kScene = 1,
			kProgram = 2,
			kTerminal = 3
		};

		[[nodiscard]] bool GetHasNoteBeenRead() const noexcept;
		void SetHasNoteBeenRead(bool a_value) noexcept;

		[[nodiscard]] BGSSoundDescriptorForm* GetNoteVoice() const;
		void SetNoteVoice(BGSSoundDescriptorForm* a_voice);

		[[nodiscard]] BGSScene* GetNoteScene() const;
		void SetNoteScene(BGSScene* a_scene);

		[[nodiscard]] BSFixedString GetNoteProgram() const;
		void SetNoteProgram(const BSFixedString& a_program);

		[[nodiscard]] BGSTerminal* GetNoteTerminal() const;
		void SetNoteTerminal(BGSTerminal* a_terminal);

		void ClearNote();

		// members
		BSFixedString programFile; // 0F0
		union
		{
			BGSSoundDescriptorForm* noteSound;
			TESFormID noteFormID;
		}; // 0F8
		REX::Enum<NOTE_TYPE, std::int8_t> type; // 100
		bool hasBeenRead;						// 101
	};
	static_assert(sizeof(BGSNote) == 0x108);
}
