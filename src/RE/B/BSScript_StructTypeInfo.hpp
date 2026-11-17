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

	class __declspec(novtable) StructTypeInfo : public IComplexType // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__StructTypeInfo;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__StructTypeInfo;

		class StructVar
		{
		public:
			// members
			Variable initialValue;							  // 0x00
			TypeInfo varType;								  // 0x10
			BSFixedString docString;						  // 0x18
			REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 0x20
			bool isConst;									  // 0x24
		};

		static_assert(sizeof(StructVar) == 0x28);

		~StructTypeInfo() override; // 0x00

		// override (IComplexType)
		auto GetRawType() const -> TypeInfo::RawType override // 0x01
		{
			return TypeInfo::RawType::Struct;
		}

		[[nodiscard]]
		auto GetName() const noexcept -> const BSFixedString&
		{
			return name;
		}

		[[nodiscard]]
		auto GetParentTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>;

		[[nodiscard]]
		auto IsLinked() const noexcept -> bool;
		[[nodiscard]]
		auto IsLinkedValid() const noexcept -> bool;
		[[nodiscard]]
		auto IsLinkedInvalid() const noexcept -> bool;

		[[nodiscard]]
		auto GetVariableIndexByName(const BSFixedString& a_name) const -> std::optional<std::uint32_t>;

		// members
		BSFixedString name;										  // 0x10
		BSTSmartPointer<ObjectTypeInfo> containingObjTypeInfo;	  // 0x18
		BSTArray<StructVar> variables;							  // 0x20
		BSTHashMap<BSFixedString, std::uint32_t> varNameIndexMap; // 0x38
		REX::Enum<LinkValidState, std::int32_t> linkedValid;	  // 0x68
	};

	static_assert(sizeof(StructTypeInfo) == 0x70);
}
