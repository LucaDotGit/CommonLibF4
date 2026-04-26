#pragma once

namespace msvc
{
#define MSVC_NON_MEMBER_CALL(a_func, a_cvOpt, a_refOpt, a_noexceptOpt) \
	_NON_MEMBER_CALL(a_func, a_cvOpt, a_refOpt, a_noexceptOpt)

	template <class... Args>
	struct arg_types
		: public std::_Arg_types<Args...>
	{
	};

	template <class T>
	struct is_member_function_ptr
		: public std::_Is_memfunptr<T>
	{
	};
}
