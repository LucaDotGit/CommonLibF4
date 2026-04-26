#pragma once

#include "RE/B/BSSystemFile.hpp"
#include "RE/N/NiBinaryStream.hpp"

namespace RE
{
	class __declspec(novtable) NiFile
		: public NiBinaryStream // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiFile };
		inline static constexpr auto VTABLE{ VTABLE::NiFile };

		enum class OpenMode : std::int32_t
		{
			kReadOnly = 0,
			kWriteOnly = 1,
			kAppendOnly = 2,
			kReadWrite = 3
		};

		~NiFile() override; // 00

		// override (NiBinaryStream)
		explicit operator bool() const override;									// 01
		void Seek(std::ptrdiff_t a_numBytes) override;								// 02
		std::size_t GetPosition() const override;									// 03
		void GetBufferInfo(BufferInfo& a_info) override;							// 04
		std::size_t DoRead(void* a_buffer, std::size_t a_numBytes) override;		// 05
		std::size_t DoWrite(const void* a_buffer, std::size_t a_numBytes) override; // 06

		// add
		virtual void Seek(std::ptrdiff_t a_numBytes, std::size_t a_trueFilePosition = 0); // 07
		virtual std::size_t GetFileSize() const;										  // 08

		// members
		std::size_t bufferAllocSize;			// 10
		std::size_t bufferReadSize;				// 18
		std::size_t pos;						// 20
		std::size_t currentFilePos;				// 28
		std::byte* buffer;						// 30
		BSSystemFile systemFile;				// 38
		REX::Enum<OpenMode, std::int32_t> mode; // 48
		bool good;								// 4C
	};
	static_assert(sizeof(NiFile) == 0x50);
}
