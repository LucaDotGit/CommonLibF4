#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_Internal_IFuncCallQuery.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class __declspec(novtable) RawFuncCallQuery : public IFuncCallQuery // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__Internal__RawFuncCallQuery;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__Internal__RawFuncCallQuery;

		~RawFuncCallQuery() override; // 0x00

		// override (IFuncCallQuery)
		auto GetFunctionCallInfo(
			CallType& a_outCallType,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo,
			BSFixedString& a_outName,
			Variable& a_outSelf,
			BSScrapArray<Variable>& a_outArgs) const -> bool override; // 0x01

		// members
		REX::Enum<CallType, std::int32_t> callType; // 0x10
		BSTSmartPointer<ObjectTypeInfo> objType;	// 0x18
		BSFixedString name;							// 0x20
		Variable self;								// 0x28
		BSTArray<Variable> args;					// 0x38
	};

	static_assert(sizeof(RawFuncCallQuery) == 0x50);
}
