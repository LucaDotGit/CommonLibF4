#include "RE/N/NiBinaryStream.hpp"

namespace RE
{
	void NiBinaryStream::GetBufferInfo(BufferInfo& a_info)
	{
		a_info.buffer = nullptr;
		a_info.fileSize = 0;
		a_info.bufferAllocSize = 0;
		a_info.bufferReadSize = 0;
		a_info.pos = 0;
		a_info.absCurrentPos = absoluteCurrentPos;
	}

	std::size_t NiBinaryStream::BinaryRead(std::byte* a_buffer, std::size_t a_size)
	{
		const auto readBytes = DoRead(a_buffer, a_size);
		absoluteCurrentPos += readBytes;
		return readBytes;
	}

	std::size_t NiBinaryStream::BinaryWrite(const std::byte* a_buffer, std::size_t a_size)
	{
		const auto writtenBytes = DoWrite(a_buffer, a_size);
		absoluteCurrentPos += writtenBytes;
		return writtenBytes;
	}
}
