#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_Internal_IFuncCallQuery.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class __declspec(novtable) RawFuncCallQuery
		: public IFuncCallQuery // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__RawFuncCallQuery };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__RawFuncCallQuery };

		~RawFuncCallQuery() override; // 00

		// override (IFuncCallQuery)
		bool GetFunctionCallInfo(CallType& a_callType, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo, BSFixedString& a_name, Variable& a_self, BSScrapArray<Variable>& a_args) const override; // 01

		// members
		REX::Enum<CallType, std::int32_t> callType; // 10
		BSTSmartPointer<ObjectTypeInfo> objType;	// 18
		BSFixedString name;							// 20
		Variable self;								// 28
		BSTArray<Variable> args;					// 38
	};
	static_assert(sizeof(RawFuncCallQuery) == 0x50);
}
