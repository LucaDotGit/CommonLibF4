#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) State : public RefCountBase<State, 2> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__GFx__State;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__GFx__State;

		enum class StateType : std::int32_t
		{
			None = 0,

			Translator,
			Log,
			ActionControl,
			UserEventHandler,
			FSCommandHandler,
			ExternalInterface,
			MultitouchInterface,
			VirtualKeyboardInterface,

			FileOpener,
			URLBuilder,
			ImageCreator,
			ImageFileHandlerRegistry,
			ParseControl,
			ProgressHandler,
			ImportVisitor,
			FontPackParams,
			FontLib,
			FontProvider,
			FontMap,
			TaskManager,
			TextClipboard,
			TextKeyMap,
			IMEManager,
			XMLSupport,
			ZlibSupport,
			FontCompactorParams,
			ImagePackerParams,
			Audio,
			Video,
			TestStream,
			SharedObject,
			LocSupport,

			AS2Support,
			AS3Support
		};

		explicit State(StateType a_type = StateType::None) :
			stateType(a_type)
		{
			REL::EmplaceVtable(this);
		}

		~State() override; // 0x00

		[[nodiscard]]
		constexpr auto GetStateType() const noexcept -> StateType
		{
			return stateType.get();
		}

		// members
		REX::Enum<StateType, std::int32_t> stateType; // 0x10
	};

	static_assert(sizeof(State) == 0x18);
}
