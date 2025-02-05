#pragma once

#include "RE/Bethesda/BSSystemFile.hpp"
#include "RE/NetImmerse/NiBinaryStream.hpp"

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
			kReadOnly,
			kWriteOnly,
			kAppendOnly,
			kReadWrite,
		};

		// members
		std::size_t bufferAllocSize;			 // 10
		std::size_t bufferReadSize;				 // 18
		std::size_t pos;						 // 20
		std::size_t currentFilePos;				 // 28
		char* buffer;							 // 30
		BSSystemFile systemFile;				 // 38
		REX::Enum<OpenMode, std::uint32_t> mode; // 48
		bool good;								 // 4C
	};
	static_assert(sizeof(NiFile) == 0x50);
}
