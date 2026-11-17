#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IAnimationGraphManagerHolder.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSAnimationGraphManager;
	class SimpleAnimationGraphManagerLoadingTask;

	class __declspec(novtable) SimpleAnimationGraphManagerHolder : public IAnimationGraphManagerHolder // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SimpleAnimationGraphManagerHolder;
		inline static constexpr const auto& VTABLE = VTABLE::SimpleAnimationGraphManagerHolder;

		~SimpleAnimationGraphManagerHolder() override; // 0x00

		// add
		virtual void BackgroundTaskFinishedLoading(); // 0x01 - { return; }

		// members
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager; // 0x08
		NiPointer<SimpleAnimationGraphManagerLoadingTask> loadingTask;	// 0x10
	};

	static_assert(sizeof(SimpleAnimationGraphManagerHolder) == 0x18);
}
