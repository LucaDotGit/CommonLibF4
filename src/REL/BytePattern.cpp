#include "REL/BytePattern.hpp"

namespace REL
{
	static_assert(
		CreateBytePattern<"40 10 F2 ??">()
			.Match(
				CreateByteArray(0x40, 0x10, 0xF2, 0x41)));

	static_assert(
		CreateBytePattern<"B8 D0 ?? ?? D4 6E">()
			.Match(
				CreateByteArray(0xB8, 0xD0, 0x35, 0x2A, 0xD4, 0x6E)));
}
