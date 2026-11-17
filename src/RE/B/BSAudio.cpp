#include "RE/B/BSAudio.hpp"

namespace RE
{
	auto BSAudio::GetSoundDescriptor(TESFormID a_formID) -> BGSSoundDescriptorForm*
	{
		using FuncType = BGSSoundDescriptorForm* (*)(TESFormID);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSAudio::GetSoundDescriptor01);
		return std::invoke(FUNC, a_formID);
	}

	auto BSAudio::GetSoundDescriptor(const char* a_formEditorId) -> BGSSoundDescriptorForm*
	{
		using FuncType = BGSSoundDescriptorForm* (*)(const char*);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSAudio::GetSoundDescriptor02);
		return std::invoke(FUNC, a_formEditorId);
	}

	auto BSAudio::GetUIOutputModel() -> const BGSSoundOutput*
	{
		using FuncType = const BGSSoundOutput* (*)();
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSAudio::GetUIOutputModel);
		return std::invoke(FUNC);
	}
}
