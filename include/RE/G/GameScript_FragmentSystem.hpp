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
		class Fragment
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSFixedString scriptName;	// 08
			BSFixedString functionName; // 10
		};
		static_assert(sizeof(Fragment) == 0x18);

		class QuestStageFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> itemFragments; // 08
		};
		static_assert(sizeof(QuestStageFragments) == 0x38);

		class QuestFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<QuestStageFragments>> stageFragments; // 08
		};
		static_assert(sizeof(QuestFragments) == 0x38);

		class BeginEndFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTSmartPointer<Fragment> beginFragment; // 08
			BSTSmartPointer<Fragment> endFragment;	 // 10
		};
		static_assert(sizeof(BeginEndFragments) == 0x18);

		class SceneFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTSmartPointer<Fragment> beginFragment;									  // 08
			BSTSmartPointer<Fragment> endFragment;										  // 10
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> actionFragments;		  // 18
			BSTHashMap<std::uint32_t, BSTSmartPointer<BeginEndFragments>> phaseFragments; // 48
		};
		static_assert(sizeof(SceneFragments) == 0x78);

		class PackageFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTSmartPointer<Fragment> beginFragment;  // 08
			BSTSmartPointer<Fragment> endFragment;	  // 10
			BSTSmartPointer<Fragment> changeFragment; // 18
		};
		static_assert(sizeof(PackageFragments) == 0x20);

		class PerkFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> entryFragments; // 08
		};
		static_assert(sizeof(PerkFragments) == 0x38);

		class TerminalFragments
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSmartPointer<Fragment>> menuItemFragments; // 08
		};
		static_assert(sizeof(TerminalFragments) == 0x38);

		// members
		BSTHashMap<std::uint32_t, BSTSmartPointer<QuestFragments>> questFragments;		  // 000
		mutable BSSpinLock questFragmentSpinLock;										  // 030
		BSTHashMap<std::uint32_t, BSTSmartPointer<BeginEndFragments>> topicInfoFragments; // 038
		mutable BSSpinLock topicInfoFragmentSpinLock;									  // 068
		BSTHashMap<std::uint32_t, BSTSmartPointer<SceneFragments>> sceneFragments;		  // 070
		mutable BSSpinLock sceneFragmentSpinLock;										  // 0A0
		BSTHashMap<std::uint32_t, BSTSmartPointer<PackageFragments>> packageFragments;	  // 0A8
		mutable BSSpinLock packageFragmentSpinLock;										  // 0D8
		BSTHashMap<std::uint32_t, BSTSmartPointer<PerkFragments>> perkFragments;		  // 0E0
		mutable BSSpinLock perkFragmentSpinLock;										  // 110
		BSTHashMap<std::uint32_t, BSTSmartPointer<TerminalFragments>> terminalFragments;  // 118
		mutable BSSpinLock terminalFragmentSpinLock;									  // 148
		BSTHashMap<std::uint32_t, BSTSmartPointer<BSScript::BoundScript>> boundScripts;	  // 150
		mutable BSSpinLock bindInfoSpinLock;											  // 180
	};
	static_assert(sizeof(FragmentSystem) == 0x188);
}
