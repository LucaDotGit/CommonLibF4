#pragma once

namespace RE
{
	template <class T, class Interpolator, template <class> class GetCurrent>
	class BSTInterpolator
	{
	public:
		// members
		Interpolator interpolate; // 0x00
		GetCurrent<T> getCurr;	  // 0x??
		T start;				  // 0x??
		T finish;				  // 0x??
		REX::Float32 duration;	  // 0x??
		REX::Float32 startTime;	  // 0x??
		bool finished;			  // 0x??
	};
}
