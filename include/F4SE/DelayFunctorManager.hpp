#pragma once

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace F4SE
{
	class IDelayFunctor;

#if _MSC_VER > 0l
#pragma warning(push)
#pragma warning(disable : 4265) // 'class': class has virtual functions, but destructor is not virtual
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class DelayFunctorManager // final
	{
	public:
		inline static constexpr auto RUN_DIRECTLY_DELAY = -1i32;
		inline static constexpr auto RUN_ON_NEXT_FRAME_DELAY = 0i32;

		DelayFunctorManager() = delete;
		~DelayFunctorManager() = delete;

		DelayFunctorManager(const DelayFunctorManager&) = delete;
		DelayFunctorManager(DelayFunctorManager&&) = delete;

		DelayFunctorManager& operator=(const DelayFunctorManager&) = delete;
		DelayFunctorManager& operator=(DelayFunctorManager&&) = delete;

		// add
		virtual void Enqueue([[maybe_unused]] REX::NotNull<REX::Owner<IDelayFunctor*>> a_functor, [[maybe_unused]] std::int32_t a_delayMS = RUN_ON_NEXT_FRAME_DELAY) const { return; } // 00
	};
	static_assert(sizeof(DelayFunctorManager) == 0x08);

#if _MSC_VER > 0l
#pragma warning(pop)
#endif
}
