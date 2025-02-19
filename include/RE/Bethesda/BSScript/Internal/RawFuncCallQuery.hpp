#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/Internal/IFuncCallQuery.hpp"
#include "RE/Bethesda/BSScript/ObjectTypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;
}

namespace RE::BSScript::Internal
{
	class __declspec(novtable) RawFuncCallQuery
		: public IFuncCallQuery // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__RawFuncCallQuery };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__RawFuncCallQuery };

		virtual ~RawFuncCallQuery(); // 00

		// override (IFuncCallQuery)
		virtual bool GetFunctionCallInfo(
			CallType& a_callType,
			BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			BSFixedString& a_name,
			Variable& a_self,
			BSScrapArray<Variable>& a_args) const override; // 01

		// members
		CallType callType;						 // 10
		std::uint32_t pad14;					 // 14
		BSTSmartPointer<ObjectTypeInfo> objType; // 18
		BSFixedString name;						 // 20
		Variable self;							 // 28
		BSTArray<Variable> args;				 // 38
	};
	static_assert(sizeof(RawFuncCallQuery) == 0x50);
}
