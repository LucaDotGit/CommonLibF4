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
	class __declspec(novtable) IFuncCallQuery : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__Internal__IFuncCallQuery;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__Internal__IFuncCallQuery;

		enum class CallType : std::int32_t
		{
			Member = 0,
			Static = 1,
			Getter = 2,
			Setter = 3
		};

		virtual ~IFuncCallQuery() = default; // 0x00

		// add
		virtual auto GetFunctionCallInfo(
			CallType& a_outCallType,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo,
			BSFixedString& a_outName,
			Variable& a_outSelf,
			BSScrapArray<Variable>& a_outArgs) const -> bool = 0; // 0x01
	};

	static_assert(sizeof(IFuncCallQuery) == 0x10);
}
