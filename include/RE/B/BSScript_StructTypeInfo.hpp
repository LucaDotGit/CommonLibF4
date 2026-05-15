#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	enum class LinkValidState : std::uint32_t;
	enum class UserFlags : std::uint32_t;

	class ObjectTypeInfo;

	class __declspec(novtable) StructTypeInfo
		: public IComplexType // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__StructTypeInfo };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__StructTypeInfo };

		class StructVar
		{
		public:
			// members
			Variable initialValue;							  // 00
			TypeInfo varType;								  // 10
			BSFixedString docString;						  // 18
			REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 20
			bool isConst;									  // 24
		};
		static_assert(sizeof(StructVar) == 0x28);

		~StructTypeInfo() override; // 00

		// override (IComplexType)
		TypeInfo::RawType GetRawType() const override { return TypeInfo::RawType::kStruct; } // 01

		[[nodiscard]] const RE::BSFixedString& GetName() const noexcept { return name; }
		[[nodiscard]] BSTSmartPointer<ObjectTypeInfo> GetParentTypeInfo() const noexcept;

		[[nodiscard]] bool IsLinked() const noexcept;
		[[nodiscard]] bool IsLinkedValid() const noexcept;
		[[nodiscard]] bool IsLinkedInvalid() const noexcept;

		[[nodiscard]] auto GetVariableIndex(const BSFixedString& a_name) const
			-> std::optional<std::uint32_t>;

		// members
		BSFixedString name;										  // 10
		BSTSmartPointer<ObjectTypeInfo> containingObjTypeInfo;	  // 18
		BSTArray<StructVar> variables;							  // 20
		BSTHashMap<BSFixedString, std::uint32_t> varNameIndexMap; // 38
		REX::Enum<LinkValidState, std::int32_t> linkedValid;	  // 68
	};
	static_assert(sizeof(StructTypeInfo) == 0x70);
}
