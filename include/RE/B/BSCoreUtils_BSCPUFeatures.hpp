#pragma once

namespace RE::BSCoreUtils
{
	class BSCPUFeatures
	{
	public:
		// members
		bool x64;	   // 00
		bool fpu;	   // 01
		bool mmx;	   // 02
		bool mmxExt;   // 03
		bool sse;	   // 04
		bool sse2;	   // 05
		bool sse3;	   // 06
		bool ssse3;	   // 07
		bool ssse41;   // 08
		bool sse42;	   // 09
		bool sse4a;	   // 0A
		bool avx;	   // 0B
		bool avx2;	   // 0C
		bool avx512;   // 0D
		bool avx512DQ; // 0E
		bool avx512PF; // 0F
		bool avx512ER; // 10
		bool avx512CD; // 11
		bool avx512BW; // 12
		bool avx512VL; // 13
		bool aes;	   // 14
		bool adx;	   // 15
		bool sha;	   // 16
		bool xop;	   // 17
		bool fma3;	   // 18
		bool fma4;	   // 19
	};
	static_assert(sizeof(BSCPUFeatures) == 0x1A);
}
