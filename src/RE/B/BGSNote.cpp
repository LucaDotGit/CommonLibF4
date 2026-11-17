#include "RE/B/BGSNote.hpp"

#include "RE/B/BGSScene.hpp"
#include "RE/B/BGSTerminal.hpp"

namespace RE
{
	auto BGSNote::GetHasNoteBeenRead() const noexcept -> bool
	{
		return hasBeenRead;
	}

	void BGSNote::SetHasNoteBeenRead(bool a_value) noexcept
	{
		hasBeenRead = a_value;
		AddChange(ChangeFlags::Read);
	}

	auto BGSNote::GetNoteVoice() const -> BGSSoundDescriptorForm*
	{
		if (type != NOTE_TYPE::Voice) {
			return nullptr;
		}

		return noteSound;
	}

	void BGSNote::SetNoteVoice(BGSSoundDescriptorForm* a_voice)
	{
		ClearNote();
		noteSound = a_voice;
		type = NOTE_TYPE::Voice;
	}

	auto BGSNote::GetNoteScene() const -> BGSScene*
	{
		if (type != NOTE_TYPE::Scene) {
			return nullptr;
		}

		return TESForm::FindFormByNumericID<BGSScene>(noteFormID);
	}

	void BGSNote::SetNoteScene(BGSScene* a_scene)
	{
		ClearNote();
		noteFormID = a_scene ? a_scene->GetFormID() : 0;
		type = NOTE_TYPE::Scene;
	}

	auto BGSNote::GetNoteProgram() const -> BSFixedString
	{
		if (type != NOTE_TYPE::Program) {
			return {};
		}

		return programFile;
	}

	void BGSNote::SetNoteProgram(const BSFixedString& a_program)
	{
		ClearNote();
		programFile = a_program;
		type = NOTE_TYPE::Program;
	}

	auto BGSNote::GetNoteTerminal() const -> BGSTerminal*
	{
		if (type != NOTE_TYPE::Terminal) {
			return nullptr;
		}

		return TESForm::FindFormByNumericID<BGSTerminal>(noteFormID);
	}

	void BGSNote::SetNoteTerminal(BGSTerminal* a_terminal)
	{
		ClearNote();
		noteFormID = a_terminal ? a_terminal->GetFormID() : 0;
		type = NOTE_TYPE::Terminal;
	}

	void BGSNote::ClearNote()
	{
		switch (type.get()) {
			case NOTE_TYPE::Voice: {
				noteSound = nullptr;
				break;
			}
			case NOTE_TYPE::Scene:
			case NOTE_TYPE::Terminal: {
				noteFormID = 0;
				break;
			}
			case NOTE_TYPE::Program: {
				programFile.clear();
				break;
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				break;
			}
		}
	}
}
