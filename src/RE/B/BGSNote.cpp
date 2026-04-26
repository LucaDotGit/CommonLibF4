#include "RE/B/BGSNote.hpp"

#include "RE/B/BGSScene.hpp"
#include "RE/B/BGSTerminal.hpp"

namespace RE
{
	bool BGSNote::GetHasNoteBeenRead() const noexcept
	{
		return hasBeenRead;
	}

	void BGSNote::SetHasNoteBeenRead(bool a_value) noexcept
	{
		hasBeenRead = a_value;
		AddChange(ChangeFlags::kRead);
	}

	BGSSoundDescriptorForm* BGSNote::GetNoteVoice() const
	{
		if (type != NOTE_TYPE::kVoice) {
			return nullptr;
		}

		return noteSound;
	}

	void BGSNote::SetNoteVoice(BGSSoundDescriptorForm* a_voice)
	{
		ClearNote();
		noteSound = a_voice;
		type = NOTE_TYPE::kVoice;
	}

	BGSScene* BGSNote::GetNoteScene() const
	{
		if (type != NOTE_TYPE::kScene) {
			return nullptr;
		}

		return TESForm::FindFormByNumericID<BGSScene>(noteFormID);
	}

	void BGSNote::SetNoteScene(BGSScene* a_scene)
	{
		ClearNote();
		noteFormID = a_scene ? a_scene->GetFormID() : 0;
		type = NOTE_TYPE::kScene;
	}

	BSFixedString BGSNote::GetNoteProgram() const
	{
		if (type != NOTE_TYPE::kProgram) {
			return {};
		}

		return programFile;
	}

	void BGSNote::SetNoteProgram(const BSFixedString& a_program)
	{
		ClearNote();
		programFile = a_program;
		type = NOTE_TYPE::kProgram;
	}

	BGSTerminal* BGSNote::GetNoteTerminal() const
	{
		if (type != NOTE_TYPE::kTerminal) {
			return nullptr;
		}

		return TESForm::FindFormByNumericID<BGSTerminal>(noteFormID);
	}

	void BGSNote::SetNoteTerminal(BGSTerminal* a_terminal)
	{
		ClearNote();
		noteFormID = a_terminal ? a_terminal->GetFormID() : 0;
		type = NOTE_TYPE::kTerminal;
	}

	void BGSNote::ClearNote()
	{
		switch (type.get()) {
			case NOTE_TYPE::kVoice: {
				noteSound = nullptr;
				break;
			}
			case NOTE_TYPE::kScene:
			case NOTE_TYPE::kTerminal: {
				noteFormID = 0;
				break;
			}
			case NOTE_TYPE::kProgram: {
				programFile.clear();
				break;
			}
			[[unlikely]] default: {
				break;
			}
		}
	}
}
