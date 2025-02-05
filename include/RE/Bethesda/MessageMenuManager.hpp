#pragma once

#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/UIMessage.hpp"

namespace RE
{
	enum class UI_DEPTH_PRIORITY;

	enum class WARNING_TYPE
	{
		kDefault,
		kSystem,
		kCombat,
		kAnimation,
		kAI,
		kScripts,
		kSaveLoad,
		kDialogue,
		kQuests,
		kPackages,
		kEditor,
		kModels,
		kTextures,
		kPlugins,
		kMasterFile,
		kForms,
		kMagic,
		kShaders,
		kRendering,
		kPathfinding,
		kMenus,
		kAudio,
		kCells,
		kHavok,
		kFaceGen,
		kWater,
		kInGameMessage,
		kMemory,
		kPerformance,
		kLootJoy,
		kVATS,
		kDismember,
		kCompanion,
		kWorkshop,
	};

	class alignas(0x10) IMessageBoxCallback
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMessageBoxCallback };
		inline static constexpr auto VTABLE{ VTABLE::IMessageBoxCallback };

		virtual ~IMessageBoxCallback() = default; // 00

		// add
		virtual void operator()(std::uint8_t a_buttonIdx) = 0; // 01
	};
	static_assert(sizeof(IMessageBoxCallback) == 0x10);

	class __declspec(novtable) MessageBoxData
		: public IUIMessageData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MessageBoxData };
		inline static constexpr auto VTABLE{ VTABLE::MessageBoxData };

		// members
		BSString headerText;								   // 18
		BSString bodyText;									   // 28
		BSTArray<BSString> buttonText;						   // 38
		REX::Enum<WARNING_TYPE, std::uint32_t> warningContext; // 50
		BSTSmartPointer<IMessageBoxCallback> callback;		   // 58
		REX::Enum<UI_DEPTH_PRIORITY, std::uint32_t> menuDepth; // 60
		bool modal;											   // 64
		bool ensureUnique;									   // 65
	};
	static_assert(sizeof(MessageBoxData) == 0x68);

	class MessageMenuManager
		: public BSTSingletonSDM<MessageMenuManager> // 00
	{
	public:
		[[nodiscard]] static MessageMenuManager* GetSingleton()
		{
			static REL::Relocation<MessageMenuManager**> singleton{ REL::RelocationID(959572, 2689087) };
			return *singleton;
		}

		void Create(
			const char* a_headerText,
			const char* a_bodyText,
			IMessageBoxCallback* a_callback,
			WARNING_TYPE a_warningContext,
			const char* a_button1Text = nullptr,
			const char* a_button2Text = nullptr,
			const char* a_button3Text = nullptr,
			const char* a_button4Text = nullptr,
			bool a_ensureUnique = false)
		{
			using func_t = decltype(&MessageMenuManager::Create);
			static REL::Relocation<func_t> func{ REL::RelocationID(89563, 2249456) };
			return func(this, a_headerText, a_bodyText, a_callback, a_warningContext, a_button1Text, a_button2Text, a_button3Text, a_button4Text, a_ensureUnique);
		}

		// members
		mutable BSReadWriteLock messageRWLock;						  // 04
		BSTArray<MessageBoxData*> messages;							  // 10
		REX::Enum<WARNING_TYPE, std::uint32_t> currentWarningContext; // 28
		bool disabledWarnings[34];									  // 2C
	};
	static_assert(sizeof(MessageMenuManager) == 0x50);
}
