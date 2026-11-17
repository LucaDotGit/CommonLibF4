#pragma once

#include "RE/N/NiBinaryStream.hpp"

namespace RE
{
	class __declspec(novtable) NiMemStream : public NiBinaryStream // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiMemStream;
		inline static constexpr const auto& VTABLE = VTABLE::NiMemStream;

		~NiMemStream() override; // 0x00

		// override (NiBinaryStream)
		explicit operator bool() const noexcept override // 0x01
		{
			return good;
		}

		void Seek(std::ptrdiff_t a_numBytes) override; // 0x02

		auto GetPosition() const -> std::size_t override // 0x03
		{
			return position;
		}

		void GetBufferInfo(BufferInfo& a_info) override;									// 0x04
		auto DoRead(void* a_buffer, std::size_t a_numBytes) -> std::size_t override;		// 0x05
		auto DoWrite(const void* a_buffer, std::size_t a_numBytes) -> std::size_t override; // 0x06

		// members
		std::byte* buffer;				  // 0x10
		std::size_t position;			  // 0x18
		std::size_t bufferAllocationSize; // 0x20
		std::size_t currentFilePosition;  // 0x28
		bool good;						  // 0x30
	};

	static_assert(sizeof(NiMemStream) == 0x38);
}
