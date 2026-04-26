#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;
	class Variable;
}

namespace RE::BSScript::Internal
{
	class __declspec(novtable) IFuncCallQuery
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__IFuncCallQuery };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__IFuncCallQuery };

		enum class CallType : std::int32_t
		{
			kMember = 0,
			kStatic = 1,
			kGetter = 2,
			kSetter = 3
		};

		virtual ~IFuncCallQuery() = default; // 00

		// add
		virtual bool GetFunctionCallInfo(CallType& a_callType, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo, BSFixedString& a_name, Variable& a_self, BSScrapArray<Variable>& a_args) const = 0; // 01
	};
	static_assert(sizeof(IFuncCallQuery) == 0x10);
}
