#pragma once

#include "RE/E/EaseOutInterpolator.hpp"
#include "RE/G/GetCurrentPositionFunctor.hpp"

namespace RE
{
	template <class T, class Interpolator, template <class> class GetCurrent>
	class BSTInterpolator
	{
	public:
		// members
		Interpolator interpolate; // 00
		GetCurrent<T> getCurr;	  // ??
		T start;				  // ??
		T finish;				  // ??
		REX::Float32 duration;	  // ??
		REX::Float32 startTime;	  // ??
		bool finished;			  // ??
	};

	extern template class BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor>;
}
