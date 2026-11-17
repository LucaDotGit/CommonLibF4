#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::GameScript
{
	class FragmentSystem
	{
	public:
		class Fragment : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSFixedString scriptName;	// 0x08
			BSFixedString functionName; // 0x10
		};

		static_assert(sizeof(Fragment) == 0x18);

		class QuestStageFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> itemFragments; // 0x08
		};

		static_assert(sizeof(QuestStageFragments) == 0x38);

		class QuestFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<QuestStageFragments>> stageFragments; // 0x08
		};

		static_assert(sizeof(QuestFragments) == 0x38);

		class BeginEndFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTSmartPointer<Fragment> beginFragment; // 0x08
			BSTSmartPointer<Fragment> endFragment;	 // 0x10
		};

		static_assert(sizeof(BeginEndFragments) == 0x18);

		class SceneFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTSmartPointer<Fragment> beginFragment;									  // 0x08
			BSTSmartPointer<Fragment> endFragment;										  // 0x10
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> actionFragments;		  // 0x18
			BSTHashMap<std::uint32_t, BSTSmartPointer<BeginEndFragments>> phaseFragments; // 0x48
		};

		static_assert(sizeof(SceneFragments) == 0x78);

		class PackageFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTSmartPointer<Fragment> beginFragment;  // 0x08
			BSTSmartPointer<Fragment> endFragment;	  // 0x10
			BSTSmartPointer<Fragment> changeFragment; // 0x18
		};

		static_assert(sizeof(PackageFragments) == 0x20);

		class PerkFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> entryFragments; // 0x08
		};

		static_assert(sizeof(PerkFragments) == 0x38);

		class TerminalFragments : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> menuItemFragments; // 0x08
		};

		static_assert(sizeof(TerminalFragments) == 0x38);

		// members
		BSTHashMap<std::uint32_t, BSTSmartPointer<QuestFragments>> questFragments;		  // 0x000
		mutable BSSpinLock questFragmentSpinLock;										  // 0x030
		BSTHashMap<std::uint32_t, BSTSmartPointer<BeginEndFragments>> topicInfoFragments; // 0x038
		mutable BSSpinLock topicInfoFragmentSpinLock;									  // 0x068
		BSTHashMap<std::uint32_t, BSTSmartPointer<SceneFragments>> sceneFragments;		  // 0x070
		mutable BSSpinLock sceneFragmentSpinLock;										  // 0x0A0
		BSTHashMap<std::uint32_t, BSTSmartPointer<PackageFragments>> packageFragments;	  // 0x0A8
		mutable BSSpinLock packageFragmentSpinLock;										  // 0x0D8
		BSTHashMap<std::uint32_t, BSTSmartPointer<PerkFragments>> perkFragments;		  // 0x0E0
		mutable BSSpinLock perkFragmentSpinLock;										  // 0x110
		BSTHashMap<std::uint32_t, BSTSmartPointer<TerminalFragments>> terminalFragments;  // 0x118
		mutable BSSpinLock terminalFragmentSpinLock;									  // 0x148
		BSTHashMap<std::uint32_t, BSTSmartPointer<BSScript::BoundScript>> boundScripts;	  // 0x150
		mutable BSSpinLock bindInfoSpinLock;											  // 0x180
	};

	static_assert(sizeof(FragmentSystem) == 0x188);
}
