#include "RE/T/TESFile.hpp"

#include "RE/C/CHUNK_ID.hpp"
#include "RE/T/TESDataHandler.hpp"

namespace RE
{
	void TESFile::dtor()
	{
		using FuncType = decltype(&TESFile::dtor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::dtor);
		std::invoke(FUNC, this);
	}

	auto TESFile::IsMaster() const noexcept -> bool
	{
		return flags.any(Flags::Master);
	}

	auto TESFile::IsLocalized() const noexcept -> bool
	{
		return flags.any(Flags::Localized);
	}

	auto TESFile::IsLight() const noexcept -> bool
	{
		return flags.any(Flags::SmallFile);
	}

	auto TESFile::IsActive() const noexcept -> bool
	{
		const auto pluginIndex = static_cast<std::uint32_t>(compileIndex << TESDataHandler::FORM_INDEX_SHIFT);
		return pluginIndex < TESDataHandler::EMPTY_RUNTIME_FORM_ID;
	}

	auto TESFile::IsFormInFile(TESFormID a_formID) const noexcept -> bool
	{
		if (flags.any(Flags::SmallFile)) {
			return ((a_formID & TESDataHandler::FORM_INDEX_MASK) == TESDataHandler::EMPTY_LIGHT_FORM_ID) &&
				   ((a_formID & TESDataHandler::LIGHT_FORM_INDEX_MASK) >> TESDataHandler::LIGHT_FORM_INDEX_SHIFT) ==
					   smallFileCompileIndex;
		}

		return ((a_formID & TESDataHandler::FORM_INDEX_MASK) >> TESDataHandler::FORM_INDEX_SHIFT) == compileIndex;
	}

	auto TESFile::OpenTES(char* a_path, const char* a_filename, NiFile::OpenMode a_accessMode, bool a_lock) -> bool
	{
		using FuncType = bool (TESFile::*)(char*, const char*, NiFile::OpenMode, bool);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::OpenTES);
		return std::invoke(FUNC, this, a_path, a_filename, a_accessMode, a_lock);
	}

	auto TESFile::OpenTES(NiFile::OpenMode a_accessMode, bool a_lock) -> bool
	{
		return OpenTES(path.data(), filename.data(), a_accessMode, a_lock);
	}

	auto TESFile::CloseTES(bool a_forceClose) -> bool
	{
		using FuncType = decltype(&TESFile::CloseTES);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::CloseTES);
		return std::invoke(FUNC, this, a_forceClose);
	}

	auto TESFile::GetTESChunk() -> std::uint32_t
	{
		using FuncType = decltype(&TESFile::GetTESChunk);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::GetTESChunk);
		return std::invoke(FUNC, this);
	}

	auto TESFile::GetChunkData(void* a_data, std::uint32_t a_maxSize) -> bool
	{
		using FuncType = bool (TESFile::*)(void*, uint32_t);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::GetChunkData);
		return std::invoke(FUNC, this, a_data, a_maxSize);
	}

	auto TESFile::NextChunk() -> bool
	{
		using FuncType = decltype(&TESFile::NextChunk);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::NextChunk);
		return std::invoke(FUNC, this);
	}

	auto TESFile::NextGroup() -> bool
	{
		using FuncType = decltype(&TESFile::NextGroup);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::NextGroup);
		return std::invoke(FUNC, this);
	}

	auto TESFile::NextForm(bool a_skipIgnored) -> bool
	{
		using FuncType = decltype(&TESFile::NextForm);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::NextForm);
		return std::invoke(FUNC, this, a_skipIgnored);
	}

	auto TESFile::FindForm(const TESForm* a_form) -> bool
	{
		using FuncType = decltype(&TESFile::FindForm);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::FindForm);
		return std::invoke(FUNC, this, a_form);
	}

	void TESFile::LoadForm(TESForm* a_form)
	{
		using FuncType = decltype(&TESFile::LoadForm);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::LoadForm);
		std::invoke(FUNC, this, a_form);
	}

	void TESFile::TESRewind(bool a_getForm)
	{
		using FuncType = decltype(&TESFile::TESRewind);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::TESRewind);
		std::invoke(FUNC, this, a_getForm);
	}

	void TESFile::TESRewindChunk()
	{
		using FuncType = decltype(&TESFile::TESRewindChunk);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::TESRewindChunk);
		std::invoke(FUNC, this);
	}

	void TESFile::ClearCurrentChunk()
	{
		currentChunkID = CHUNK_ID::None;
		actualChunkSize = 0;
	}

	auto TESFile::HasThreadSafeParent() const noexcept -> bool
	{
		return threadSafeParent != nullptr;
	}

	auto TESFile::HasThreadSafeParent(TESFile* a_parent) const noexcept -> bool
	{
		auto* parentFile = threadSafeParent;
		for (; parentFile; parentFile = parentFile->threadSafeParent) {
			if (parentFile == a_parent) {
				return true;
			}
		}

		return false;
	}

	auto TESFile::GetThreadSafeParent() const noexcept -> TESFile*
	{
		auto* parentFile = threadSafeParent;
		for (; parentFile; parentFile = parentFile->threadSafeParent) {
		}

		return parentFile;
	}

	void TESFile::SetThreadSafeParent(TESFile* a_parent) noexcept
	{
		auto** parentFile = std::addressof(threadSafeParent);
		for (; *parentFile; parentFile = std::addressof((*parentFile)->threadSafeParent)) {
		}

		*parentFile = a_parent;
	}

	auto TESFile::RemoveThreadSafeParent() noexcept -> bool
	{
		auto** parentFile = std::addressof(threadSafeParent);
		for (; *parentFile; parentFile = std::addressof((*parentFile)->threadSafeParent)) {
		}

		*parentFile = nullptr;
		return true;
	}

	auto TESFile::RemoveThreadSafeParent(TESFile* a_parent) noexcept -> bool
	{
		auto** parentFile = std::addressof(threadSafeParent);
		for (; *parentFile; parentFile = std::addressof((*parentFile)->threadSafeParent)) {
			if (*parentFile == a_parent) {
				*parentFile = nullptr;
				return true;
			}
		}

		return false;
	}

	auto TESFile::HasThreadSafeFile() const -> bool
	{
		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		return HasThreadSafeFileForThread(currentThreadID);
	}

	auto TESFile::HasThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID) const -> bool
	{
		return threadSafeFileMap.contains(a_threadID);
	}

	auto TESFile::GetThreadSafeFile(std::uint32_t a_bufferSize) -> TESFile*
	{
		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		return GetThreadSafeFileForThread(currentThreadID, a_bufferSize);
	}

	auto TESFile::GetThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID, std::uint32_t a_bufferSize) -> TESFile*
	{
		using FuncType = decltype(&TESFile::GetThreadSafeFileForThread);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::GetThreadSafeFileForThread);
		return std::invoke(FUNC, this, a_threadID, a_bufferSize);
	}

	auto TESFile::DeleteThreadSafeFile() -> bool
	{
		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		return DeleteThreadSafeFileForThread(currentThreadID);
	}

	auto TESFile::DeleteThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID) -> bool
	{
		const auto fileIt = threadSafeFileMap.find(a_threadID);
		if (fileIt == threadSafeFileMap.end()) {
			return false;
		}

		auto*& oldFile = fileIt->second;
		threadSafeFileMap.erase(fileIt);

		oldFile->dtor();
		free(oldFile);
		oldFile = nullptr;

		return true;
	}

	auto TESFile::GetBufferSize() const noexcept -> std::uint32_t
	{
		return bufferAllocSize;
	}

	auto TESFile::ChangeBufferSize(std::uint32_t a_size) -> bool
	{
		using FuncType = decltype(&TESFile::ChangeBufferSize);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESFile::ChangeBufferSize);
		return std::invoke(FUNC, this, a_size);
	}
}
