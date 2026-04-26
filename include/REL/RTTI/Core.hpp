#pragma once

#include "REL/Id.hpp"

#include "REX/Concepts.hpp"

namespace REL::RTTI
{
	template <class T>
	concept valid_target =
		std::is_polymorphic_v<REX::remove_cvpr_t<T>> ||
		std::same_as<void*, std::remove_cv_t<T>>;

	template <class From, class To>
	concept compatible_type =
		std::is_pointer_v<From> &&
		std::is_pointer_v<To> &&
		((!std::is_const_v<std::remove_pointer_t<From>>) ||
			(std::is_const_v<std::remove_pointer_t<To>> &&
				std::is_const_v<std::remove_pointer_t<From>>) ||
			(std::is_volatile_v<std::remove_pointer_t<From>> &&
				std::is_volatile_v<std::remove_pointer_t<To>>) ||
			(std::is_const_v<std::remove_pointer_t<From>> &&
				std::is_volatile_v<std::remove_pointer_t<From>> &&
				std::is_const_v<std::remove_pointer_t<To>> &&
				std::is_volatile_v<std::remove_pointer_t<To>>));

	template <class T>
	concept has_rtti =
		std::derived_from<decltype(REX::remove_cvpr_t<T>::RTTI), REL::IId>;

	template <class From, class To>
	concept valid_cast =
		compatible_type<From, To> &&
		valid_target<To> &&
		has_rtti<From> &&
		has_rtti<To>;
}
