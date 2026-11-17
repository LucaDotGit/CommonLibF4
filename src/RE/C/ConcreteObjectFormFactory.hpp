#pragma once

#include "RE/C/ConcreteFormFactory.hpp"

namespace RE
{
	enum class OBJECT_CATEGORY_TYPE : std::int32_t;
	enum class OBJECT_TYPE : std::int32_t;

	template <class T, OBJECT_TYPE Type, OBJECT_CATEGORY_TYPE Category>
	class __declspec(novtable) ConcreteObjectFormFactory : public ConcreteFormFactory<T> // 0x00
	{
	public:
	};
}
