#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) NiBinaryStream
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiBinaryStream };
		inline static constexpr auto VTABLE{ VTABLE::NiBinaryStream };

		class BufferInfo
		{
		public:
			std::byte* buffer{ nullptr };	  // 00
			std::size_t fileSize{ 0 };		  // 08
			std::size_t bufferAllocSize{ 0 }; // 10
			std::size_t bufferReadSize{ 0 };  // 18
			std::size_t pos{ 0 };			  // 20
			std::size_t absCurrentPos{ 0 };	  // 28
		};
		static_assert(sizeof(BufferInfo) == 0x30);

		NiBinaryStream();

		NiBinaryStream(const NiBinaryStream&) = delete;
		NiBinaryStream(NiBinaryStream&&) noexcept = default;

		NiBinaryStream& operator=(const NiBinaryStream&) = delete;
		NiBinaryStream& operator=(NiBinaryStream&&) noexcept = default;

		virtual ~NiBinaryStream() = default; // 00

		// add
		virtual explicit operator bool() const = 0;									   // 01
		virtual void Seek(std::ptrdiff_t a_numBytes) = 0;							   // 02
		virtual std::size_t GetPosition() const { return absoluteCurrentPos; }		   // 03
		virtual void GetBufferInfo(BufferInfo& a_info);								   // 04
		virtual std::size_t DoRead(void* a_buffer, std::size_t a_numBytes) = 0;		   // 05
		virtual std::size_t DoWrite(const void* a_buffer, std::size_t a_numBytes) = 0; // 06

		GAME_HEAP_REDEFINE_NEW(NiBinaryStream);

		[[nodiscard]] std::size_t BinaryRead(std::byte* a_buffer, std::size_t a_size);
		[[nodiscard]] std::size_t BinaryWrite(const std::byte* a_buffer, std::size_t a_size);

		// members
		std::size_t absoluteCurrentPos{ 0 }; // 08
	};
	static_assert(sizeof(NiBinaryStream) == 0x10);
}
