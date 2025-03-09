#include "RE/Bethesda/Script.hpp"

namespace RE
{
	SCRIPT_FUNCTION::StringChunk* SCRIPT_FUNCTION::Chunk::AsString()
	{
		return static_cast<StringChunk*>(this);
	}

	SCRIPT_FUNCTION::IntegerChunk* SCRIPT_FUNCTION::Chunk::AsInteger()
	{
		return static_cast<IntegerChunk*>(this);
	}

	const SCRIPT_FUNCTION::StringChunk* SCRIPT_FUNCTION::Chunk::AsString() const
	{
		return static_cast<const StringChunk*>(this);
	}

	const SCRIPT_FUNCTION::IntegerChunk* SCRIPT_FUNCTION::Chunk::AsInteger() const
	{
		return static_cast<const IntegerChunk*>(this);
	}

	std::string SCRIPT_FUNCTION::StringChunk::GetString() const
	{
		return length ? std::string(str, length) : "";
	}

	SCRIPT_FUNCTION::Chunk* SCRIPT_FUNCTION::StringChunk::GetNext()
	{
		return reinterpret_cast<Chunk*>(str + length);
	}

	const SCRIPT_FUNCTION::Chunk* SCRIPT_FUNCTION::StringChunk::GetNext() const
	{
		return reinterpret_cast<const Chunk*>(str + length);
	}

	int SCRIPT_FUNCTION::IntegerChunk::GetInteger() const
	{
		return *(int*)((std::uintptr_t)this + 1);
	}

	SCRIPT_FUNCTION::Chunk* SCRIPT_FUNCTION::IntegerChunk::GetNext()
	{
		return reinterpret_cast<Chunk*>(this + 1);
	}

	const SCRIPT_FUNCTION::Chunk* SCRIPT_FUNCTION::IntegerChunk::GetNext() const
	{
		return reinterpret_cast<const Chunk*>(this + 1);
	}

	SCRIPT_FUNCTION::Chunk* SCRIPT_FUNCTION::ScriptData::GetChunk()
	{
		return reinterpret_cast<Chunk*>(this + 1);
	}

	SCRIPT_FUNCTION::StringChunk* SCRIPT_FUNCTION::ScriptData::GetStringChunk()
	{
		return static_cast<StringChunk*>(GetChunk());
	}

	SCRIPT_FUNCTION::IntegerChunk* SCRIPT_FUNCTION::ScriptData::GetIntegerChunk()
	{
		return static_cast<IntegerChunk*>(GetChunk());
	}

	const SCRIPT_FUNCTION::Chunk* SCRIPT_FUNCTION::ScriptData::GetChunk() const
	{
		return reinterpret_cast<const Chunk*>(this + 1);
	}

	const SCRIPT_FUNCTION::StringChunk* SCRIPT_FUNCTION::ScriptData::GetStringChunk() const
	{
		return static_cast<const StringChunk*>(GetChunk());
	}

	const SCRIPT_FUNCTION::IntegerChunk* SCRIPT_FUNCTION::ScriptData::GetIntegerChunk() const
	{
		return static_cast<const IntegerChunk*>(GetChunk());
	}

	void Script::SetText(std::string_view a_text)
	{
		if (text) {
			free(text);
			text = nullptr;
		}

		text = calloc<char>(a_text.length() + 1);
		std::memset(text, '\0', a_text.length() + 1);
		std::memcpy(text, a_text.data(), a_text.length());
	}
}
