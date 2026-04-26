#include "RE/B/BSResourceNiBinaryStream.hpp"

namespace RE
{
	BSResourceNiBinaryStream::BSResourceNiBinaryStream()
	{
		REL::EmplaceVtable(this);
	}

	BSResourceNiBinaryStream::BSResourceNiBinaryStream(const char* a_name, bool a_writeable, BSResource::Location* a_optionalStart, bool a_fullReadHint)
	{
		using FuncType = void (BSResourceNiBinaryStream::*)(const char*, bool, BSResource::Location*, bool);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::ctor };
		FUNC(this, a_name, a_writeable, a_optionalStart, a_fullReadHint);
	}

	BSResourceNiBinaryStream::~BSResourceNiBinaryStream()
	{
		using FuncType = void (BSResourceNiBinaryStream::*)();
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::dtor };
		FUNC(this);
	}

	void BSResourceNiBinaryStream::Seek(std::ptrdiff_t a_numBytes)
	{
		using FuncType = decltype(&BSResourceNiBinaryStream::Seek);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::Seek };
		FUNC(this, a_numBytes);
	}

	void BSResourceNiBinaryStream::GetBufferInfo(BufferInfo& a_buffer)
	{
		using FuncType = decltype(&BSResourceNiBinaryStream::GetBufferInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::GetBufferInfo };
		FUNC(this, a_buffer);
	}

	std::size_t BSResourceNiBinaryStream::DoRead(void* a_buffer, std::size_t a_toRead)
	{
		using FuncType = decltype(&BSResourceNiBinaryStream::DoRead);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::DoRead };
		return std::invoke(FUNC, this, a_buffer, a_toRead);
	}

	std::size_t BSResourceNiBinaryStream::DoWrite(const void* a_buffer, std::size_t a_toWrite)
	{
		using FuncType = decltype(&BSResourceNiBinaryStream::DoWrite);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::DoWrite };
		return std::invoke(FUNC, this, a_buffer, a_toWrite);
	}

	BSResourceNiBinaryStream* BinaryStreamWithRescan(const char* a_fileName)
	{
		using FuncType = decltype(&BinaryStreamWithRescan);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResourceNiBinaryStream::BinaryStreamWithRescan };
		return std::invoke(FUNC, a_fileName);
	}
}
