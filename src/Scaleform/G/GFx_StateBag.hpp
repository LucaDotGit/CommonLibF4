#pragma once

#include "Scaleform/G/GFx_FileTypeConstants.hpp"
#include "Scaleform/G/GFx_State.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx::Impl
{
	template <class T>
	concept StateConstraint = std::derived_from<T, State> &&
							  !REX::pointer<T> &&
							  !REX::reference<T> &&
							  std::same_as<std::remove_cv_t<decltype(T::STATE_TYPE)>, State::StateType>;
}

namespace Scaleform::GFx
{
	class __declspec(novtable) StateBag : public FileTypeConstants // 0x00
	{
	protected:
		// add
		virtual auto GetStateBagImpl() const -> StateBag*; // 0x00 - { return nullptr; }

	public:
		virtual ~StateBag() = default; // 0x01

		// add
		virtual void SetState(State::StateType a_stateType, State* a_state);	   // 0x02
		virtual auto GetStateAddRef(State::StateType a_stateType) const -> State*; // 0x03
		virtual void GetStatesAddRef(State** a_states, const State::StateType* a_stateTypes, std::uint32_t a_count)
			const; // 0x04

		template <Impl::StateConstraint T>
		[[nodiscard]]
		auto GetStateAddRef() const -> Ptr<T>
		{
			return Ptr(static_cast<T*>(GetStateAddRef(T::STATE_TYPE)));
		}
	};

	static_assert(sizeof(StateBag) == 0x08);
}
