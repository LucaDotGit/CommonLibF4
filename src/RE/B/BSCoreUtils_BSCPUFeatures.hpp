#pragma once

namespace RE::BSCoreUtils
{
	class BSCPUFeatures
	{
	public:
		// members
		bool x64;	   // 0x00
		bool fpu;	   // 0x01
		bool mmx;	   // 0x02
		bool mmxExt;   // 0x03
		bool sse;	   // 0x04
		bool sse2;	   // 0x05
		bool sse3;	   // 0x06
		bool ssse3;	   // 0x07
		bool ssse41;   // 0x08
		bool sse42;	   // 0x09
		bool sse4a;	   // 0x0A
		bool avx;	   // 0x0B
		bool avx2;	   // 0x0C
		bool avx512;   // 0x0D
		bool avx512DQ; // 0x0E
		bool avx512PF; // 0x0F
		bool avx512ER; // 0x10
		bool avx512CD; // 0x11
		bool avx512BW; // 0x12
		bool avx512VL; // 0x13
		bool aes;	   // 0x14
		bool adx;	   // 0x15
		bool sha;	   // 0x16
		bool xop;	   // 0x17
		bool fma3;	   // 0x18
		bool fma4;	   // 0x19
	};

	static_assert(sizeof(BSCPUFeatures) == 0x1A);
}
