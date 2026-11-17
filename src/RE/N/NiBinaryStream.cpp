#include "RE/N/NiBinaryStream.hpp"

namespace RE
{
	void NiBinaryStream::GetBufferInfo(BufferInfo& a_info)
	{
		a_info.buffer = nullptr;
		a_info.fileSize = 0;
		a_info.bufferAllocSize = 0;
		a_info.bufferReadSize = 0;
		a_info.position = 0;
		a_info.absoluteCurrentPosition = absoluteCurrentPosition;
	}

	auto NiBinaryStream::BinaryRead(std::byte* a_buffer, std::size_t a_size) -> std::size_t
	{
		const auto readBytes = DoRead(a_buffer, a_size);
		absoluteCurrentPosition += readBytes;
		return readBytes;
	}

	auto NiBinaryStream::BinaryWrite(const std::byte* a_buffer, std::size_t a_size) -> std::size_t
	{
		const auto writtenBytes = DoWrite(a_buffer, a_size);
		absoluteCurrentPosition += writtenBytes;
		return writtenBytes;
	}
}
