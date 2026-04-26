#pragma once

#include "Scaleform/G/GFx_FileTypeConstants.hpp"
#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx::Impl
{
	template <class T>
	concept StateConstraint =
		std::derived_from<T, State> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::STATE_TYPE)>, State::StateType>;
}

namespace Scaleform::GFx
{
	class __declspec(novtable) StateBag
		: public FileTypeConstants // 00
	{
	protected:
		// add
		virtual StateBag* GetStateBagImpl() const; // 00 - { return nullptr; }

	public:
		virtual ~StateBag() = default; // 01

		// add
		virtual void SetState(State::StateType a_stateType, State* a_state);											   // 02
		virtual State* GetStateAddRef(State::StateType a_stateType) const;												   // 03
		virtual void GetStatesAddRef(State** a_states, const State::StateType* a_stateTypes, std::uint32_t a_count) const; // 04

		template <Impl::StateConstraint T>
		[[nodiscard]] T* GetStateAddRef() const
		{
			return static_cast<T*>(GetStateAddRef(T::STATE_TYPE));
		}
	};
	static_assert(sizeof(StateBag) == 0x08);
}
