#pragma once

#include "RE/B/BSSystemFile.hpp"
#include "RE/N/NiBinaryStream.hpp"

namespace RE
{
	class __declspec(novtable) NiFile : public NiBinaryStream // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiFile;
		inline static constexpr const auto& VTABLE = VTABLE::NiFile;

		enum class OpenMode : std::int32_t
		{
			ReadOnly = 0,
			WriteOnly = 1,
			AppendOnly = 2,
			ReadWrite = 3
		};

		~NiFile() override; // 0x00

		// override (NiBinaryStream)
		explicit operator bool() const override;											// 0x01
		void Seek(std::ptrdiff_t a_numBytes) override;										// 0x02
		auto GetPosition() const -> std::size_t override;									// 0x03
		void GetBufferInfo(BufferInfo& a_info) override;									// 0x04
		auto DoRead(void* a_buffer, std::size_t a_numBytes) -> std::size_t override;		// 0x05
		auto DoWrite(const void* a_buffer, std::size_t a_numBytes) -> std::size_t override; // 0x06

		// add
		virtual void Seek(std::ptrdiff_t a_numBytes, std::size_t a_trueFilePosition = 0); // 0x07
		virtual auto GetFileSize() const -> std::size_t;								  // 0x08

		// members
		std::size_t bufferAllocationSize;		// 0x10
		std::size_t bufferReadSize;				// 0x18
		std::size_t position;					// 0x20
		std::size_t currentFilePosition;		// 0x28
		std::byte* buffer;						// 0x30
		BSSystemFile systemFile;				// 0x38
		REX::Enum<OpenMode, std::int32_t> mode; // 0x48
		bool good;								// 0x4C
	};

	static_assert(sizeof(NiFile) == 0x50);
}
