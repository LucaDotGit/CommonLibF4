#pragma once

#include "RE/C/ConcreteFormFactory.hpp"

namespace RE
{
	template <class T, FormType ID, OBJECT_TYPE TYPE, OBJECT_CATEGORY_TYPE CATEGORY>
	class __declspec(novtable) ConcreteObjectFormFactory
		: public ConcreteFormFactory<T, ID> // 00
	{
	public:
	};
}
