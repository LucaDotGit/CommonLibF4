#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) State
		: public RefCountBase<State, 2> // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__GFx__State };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__GFx__State };

		enum class StateType : std::int32_t
		{
			kNone = 0,

			kTranslator,
			kLog,
			kActionControl,
			kUserEventHandler,
			kFSCommandHandler,
			kExternalInterface,
			kMultitouchInterface,
			kVirtualKeyboardInterface,

			kFileOpener,
			kURLBuilder,
			kImageCreator,
			kImageFileHandlerRegistry,
			kParseControl,
			kProgressHandler,
			kImportVisitor,
			kFontPackParams,
			kFontLib,
			kFontProvider,
			kFontMap,
			kTaskManager,
			kTextClipboard,
			kTextKeyMap,
			kIMEManager,
			kXMLSupport,
			kZlibSupport,
			kFontCompactorParams,
			kImagePackerParams,
			kAudio,
			kVideo,
			kTestStream,
			kSharedObject,
			kLocSupport,

			kAS2Support,
			kAS3Support
		};

		explicit State(StateType a_type = StateType::kNone)
			: stateType(a_type)
		{
			REL::EmplaceVtable(this);
		}

		~State() override; // 00

		[[nodiscard]] constexpr StateType GetStateType() const noexcept { return stateType.get(); }

		// members
		REX::Enum<StateType, std::int32_t> stateType; // 10
	};
	static_assert(sizeof(State) == 0x18);
}
