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
	class __declspec(novtable) BGSNote :
		public TESBoundObject,		  // 0x000
		public TESWeightForm,		  // 0x068
		public TESValueForm,		  // 0x078
		public TESModel,			  // 0x088
		public TESFullName,			  // 0x0B8
		public TESIcon,				  // 0x0C8
		public BGSPickupPutdownSounds // 0x0D8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSNote;
		inline static constexpr const auto& VTABLE = VTABLE::BGSNote;
		inline static constexpr auto FORM_TYPE = FormType::Note;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Read = static_cast<std::uint32_t>(1) << 31
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

		enum class NOTE_TYPE : std::int8_t
		{
			Voice = 0,
			Scene = 1,
			Program = 2,
			Terminal = 3
		};

		[[nodiscard]]
		auto GetHasNoteBeenRead() const noexcept -> bool;
		void SetHasNoteBeenRead(bool a_value) noexcept;

		[[nodiscard]]
		auto GetNoteVoice() const -> BGSSoundDescriptorForm*;
		void SetNoteVoice(BGSSoundDescriptorForm* a_voice);

		[[nodiscard]]
		auto GetNoteScene() const -> BGSScene*;
		void SetNoteScene(BGSScene* a_scene);

		[[nodiscard]]
		auto GetNoteProgram() const -> BSFixedString;
		void SetNoteProgram(const BSFixedString& a_program);

		[[nodiscard]]
		auto GetNoteTerminal() const -> BGSTerminal*;
		void SetNoteTerminal(BGSTerminal* a_terminal);

		void ClearNote();

		// members
		BSFixedString programFile; // 0x0F0

		union
		{
		public:
			BGSSoundDescriptorForm* noteSound;
			TESFormID noteFormID;
		}; // 0x0F8

		REX::Enum<NOTE_TYPE, std::int8_t> type; // 0x100
		bool hasBeenRead;						// 0x101
	};

	static_assert(sizeof(BGSNote) == 0x108);
}
