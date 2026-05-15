#include "RE/T/TESFile.hpp"

#include "RE/C/CHUNK_ID.hpp"
#include "RE/T/TESDataHandler.hpp"

namespace RE
{
	void TESFile::dtor()
	{
		using FuncType = decltype(&TESFile::dtor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::dtor };
		std::invoke(FUNC, this);
	}

	bool TESFile::IsMaster() const noexcept
	{
		return flags.any(Flags::kMaster);
	}

	bool TESFile::IsLocalized() const noexcept
	{
		return flags.any(Flags::kLocalized);
	}

	bool TESFile::IsLight() const noexcept
	{
		return flags.any(Flags::kSmallFile);
	}

	bool TESFile::IsActive() const noexcept
	{
		const auto pluginIndex = static_cast<std::uint32_t>(compileIndex << TESDataHandler::FORM_INDEX_SHIFT);
		return pluginIndex < TESDataHandler::EMPTY_RUNTIME_FORM_ID;
	}

	bool TESFile::IsFormInFile(TESFormID a_formID) const noexcept
	{
		switch (flags.get()) {
			case Flags::kSmallFile: {
				return ((a_formID & TESDataHandler::FORM_INDEX_MASK) == TESDataHandler::EMPTY_LIGHT_FORM_ID) &&
					   ((a_formID & TESDataHandler::LIGHT_FORM_INDEX_MASK) >> TESDataHandler::LIGHT_FORM_INDEX_SHIFT) == smallFileCompileIndex;
			}
			default: {
				return ((a_formID & TESDataHandler::FORM_INDEX_MASK) >> TESDataHandler::FORM_INDEX_SHIFT) == compileIndex;
			}
		}
	}

	bool TESFile::OpenTES(char* a_path, const char* a_filename, NiFile::OpenMode a_accessMode, bool a_lock)
	{
		using FuncType = bool (TESFile::*)(char*, const char*, NiFile::OpenMode, bool);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::OpenTES };
		return std::invoke(FUNC, this, a_path, a_filename, a_accessMode, a_lock);
	}

	bool TESFile::OpenTES(NiFile::OpenMode a_accessMode, bool a_lock)
	{
		return OpenTES(path.data(), filename.data(), a_accessMode, a_lock);
	}

	bool TESFile::CloseTES(bool a_forceClose)
	{
		using FuncType = decltype(&TESFile::CloseTES);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::CloseTES };
		return std::invoke(FUNC, this, a_forceClose);
	}

	std::uint32_t TESFile::GetTESChunk()
	{
		using FuncType = decltype(&TESFile::GetTESChunk);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::GetTESChunk };
		return std::invoke(FUNC, this);
	}

	bool TESFile::GetChunkData(void* a_data, std::uint32_t a_maxSize)
	{
		using FuncType = bool (TESFile::*)(void*, uint32_t);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::GetChunkData };
		return std::invoke(FUNC, this, a_data, a_maxSize);
	}

	bool TESFile::NextChunk()
	{
		using FuncType = decltype(&TESFile::NextChunk);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::NextChunk };
		return std::invoke(FUNC, this);
	}

	bool TESFile::NextGroup()
	{
		using FuncType = decltype(&TESFile::NextGroup);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::NextGroup };
		return std::invoke(FUNC, this);
	}

	bool TESFile::NextForm(bool a_skipIgnored)
	{
		using FuncType = decltype(&TESFile::NextForm);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::NextForm };
		return std::invoke(FUNC, this, a_skipIgnored);
	}

	bool TESFile::FindForm(const TESForm* a_form)
	{
		using FuncType = decltype(&TESFile::FindForm);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::FindForm };
		return std::invoke(FUNC, this, a_form);
	}

	void TESFile::LoadForm(TESForm* a_form)
	{
		using FuncType = decltype(&TESFile::LoadForm);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::LoadForm };
		std::invoke(FUNC, this, a_form);
	}

	void TESFile::TESRewind(bool a_getForm)
	{
		using FuncType = decltype(&TESFile::TESRewind);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::TESRewind };
		std::invoke(FUNC, this, a_getForm);
	}

	void TESFile::TESRewindChunk()
	{
		using FuncType = decltype(&TESFile::TESRewindChunk);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::TESRewindChunk };
		std::invoke(FUNC, this);
	}

	void TESFile::ClearCurrentChunk()
	{
		currentChunkID = CHUNK_ID::kNone;
		actualChunkSize = 0;
	}

	bool TESFile::HasThreadSafeParent() const noexcept
	{
		return threadSafeParent != nullptr;
	}

	bool TESFile::HasThreadSafeParent(TESFile* a_parent) const noexcept
	{
		auto* parentFile = threadSafeParent;
		for (; parentFile; parentFile = parentFile->threadSafeParent) {
			if (parentFile == a_parent) {
				return true;
			}
		}

		return false;
	}

	TESFile* TESFile::GetThreadSafeParent() const noexcept
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

	bool TESFile::RemoveThreadSafeParent() noexcept
	{
		auto** parentFile = std::addressof(threadSafeParent);
		for (; *parentFile; parentFile = std::addressof((*parentFile)->threadSafeParent)) {
		}

		*parentFile = nullptr;
		return true;
	}

	bool TESFile::RemoveThreadSafeParent(TESFile* a_parent) noexcept
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

	bool TESFile::HasThreadSafeFile() const
	{
		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		return HasThreadSafeFileForThread(currentThreadID);
	}

	bool TESFile::HasThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID) const
	{
		return threadSafeFileMap.contains(a_threadID);
	}

	TESFile* TESFile::GetThreadSafeFile(std::uint32_t a_fileBufferSize)
	{
		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		return GetThreadSafeFileForThread(currentThreadID, a_fileBufferSize);
	}

	TESFile* TESFile::GetThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID, std::uint32_t a_fileBufferSize)
	{
		using FuncType = decltype(&TESFile::GetThreadSafeFileForThread);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::GetThreadSafeFileForThread };
		return std::invoke(FUNC, this, a_threadID, a_fileBufferSize);
	}

	bool TESFile::DeleteThreadSafeFile()
	{
		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		return DeleteThreadSafeFileForThread(currentThreadID);
	}

	bool TESFile::DeleteThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID)
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

	std::uint32_t TESFile::GetBufferSize() const noexcept
	{
		return bufferAllocSize;
	}

	bool TESFile::ChangeBufferSize(std::uint32_t a_size)
	{
		using FuncType = decltype(&TESFile::ChangeBufferSize);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFile::ChangeBufferSize };
		return std::invoke(FUNC, this, a_size);
	}
}
