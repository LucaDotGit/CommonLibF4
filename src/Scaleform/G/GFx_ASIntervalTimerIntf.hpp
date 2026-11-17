#pragma once

#include "Scaleform/G/GFx_StatMovieView.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class MovieDefImpl;
	class MovieImpl;

	class __declspec(novtable) ASIntervalTimerIntf :
		public RefCountBase<ASIntervalTimerIntf, StatMV_ActionScript_Mem> // 0x00
	{
	public:
		~ASIntervalTimerIntf() override = default; // 0x00

		// add
		virtual void Start(MovieImpl* a_root) = 0;									  // 0x01
		virtual auto Invoke(MovieImpl* a_root, REX::Float32 a_frameTime) -> bool = 0; // 0x02
		virtual auto IsActive() const -> bool = 0;									  // 0x03
		virtual void Clear() = 0;													  // 0x04
		virtual auto ClearFor(MovieImpl* a_root, MovieDefImpl* a_def) -> bool = 0;	  // 0x05
		virtual auto GetNextInvokeTime() const -> std::uint64_t = 0;				  // 0x06
		virtual void SetId(std::int32_t a_id) = 0;									  // 0x07
		virtual auto GetId() const -> std::int32_t = 0;								  // 0x08
	};

	static_assert(sizeof(ASIntervalTimerIntf) == 0x10);
}
