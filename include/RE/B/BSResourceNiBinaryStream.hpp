#pragma once

#include "RE/B/BSResource_ErrorCode.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiBinaryStream.hpp"

namespace RE::BSResource
{
	class Location;
}

namespace RE
{
	class __declspec(novtable) BSResourceNiBinaryStream
		: public NiBinaryStream // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResourceNiBinaryStream };
		inline static constexpr auto VTABLE{ VTABLE::BSResourceNiBinaryStream };

		class BufferType;

		BSResourceNiBinaryStream();
		BSResourceNiBinaryStream(const char* a_name, bool a_writeable = false, BSResource::Location* a_optionalStart = nullptr, bool a_fullReadHint = false);

		BSResourceNiBinaryStream(const BSResourceNiBinaryStream&) = delete;
		BSResourceNiBinaryStream(BSResourceNiBinaryStream&&) noexcept = default;

		BSResourceNiBinaryStream& operator=(const BSResourceNiBinaryStream&) = delete;
		BSResourceNiBinaryStream& operator=(BSResourceNiBinaryStream&&) noexcept = default;

		~BSResourceNiBinaryStream() override; // 00

		// override (NiBinaryStream)
		explicit operator bool() const noexcept override { return good(); }		   // 01
		void Seek(std::ptrdiff_t a_numBytes) override;							   // 02
		std::size_t GetPosition() const noexcept override { return streamPos; }	   // 03
		void GetBufferInfo(BufferInfo& a_buffer) override;						   // 04
		std::size_t DoRead(void* a_buffer, std::size_t a_toRead) override;		   // 05
		std::size_t DoWrite(const void* a_buffer, std::size_t a_toWrite) override; // 05

		[[nodiscard]] bool good() const { return static_cast<bool>(stream); }

		// members
		BSTSmartPointer<BSResource::Stream> stream;						 // 10
		BufferType* buffer{ nullptr };									 // 18
		std::size_t streamPos{ 0 };										 // 20
		BSResource::ErrorCode lastError{ BSResource::ErrorCode::kNone }; // 28
	};
	static_assert(sizeof(BSResourceNiBinaryStream) == 0x30);

	[[nodiscard]] BSResourceNiBinaryStream* BinaryStreamWithRescan(const char* a_fileName);
}
