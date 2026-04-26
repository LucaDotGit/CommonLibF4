#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IAnimationGraphManagerHolder.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSAnimationGraphManager;
	class SimpleAnimationGraphManagerLoadingTask;

	class __declspec(novtable) SimpleAnimationGraphManagerHolder
		: public IAnimationGraphManagerHolder // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SimpleAnimationGraphManagerHolder };
		inline static constexpr auto VTABLE{ VTABLE::SimpleAnimationGraphManagerHolder };

		~SimpleAnimationGraphManagerHolder() override; // 00

		// add
		virtual void BackgroundTaskFinishedLoading(); // 01 - { return; }

		// members
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager; // 08
		NiPointer<SimpleAnimationGraphManagerLoadingTask> loadingTask;	// 10
	};
	static_assert(sizeof(SimpleAnimationGraphManagerHolder) == 0x18);
}
