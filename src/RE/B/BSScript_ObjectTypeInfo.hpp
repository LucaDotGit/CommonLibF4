#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_PropertyGroupInfo.hpp"
#include "RE/B/BSScript_PropertyTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE::BSScript
{
	enum class LinkValidState : std::uint32_t;

	class IFunction;

	class __declspec(novtable) ObjectTypeInfo : public IComplexType // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__ObjectTypeInfo;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__ObjectTypeInfo;

		class UnlinkedNativeFunction
		{
		public:
			// members
			UnlinkedNativeFunction* next;	 // 0x00
			BSTSmartPointer<IFunction> func; // 0x08
		};

		static_assert(sizeof(UnlinkedNativeFunction) == 0x10);

		class UserFlagInfo
		{
		public:
			inline static constexpr auto SET_ON_OBJECT_FLAG = static_cast<std::uintptr_t>(1) << 0;

			[[nodiscard]]
			auto GetUserFlag() const noexcept -> BSFixedString;

			// members
			std::uintptr_t data; // 0x00
		};

		static_assert(sizeof(UserFlagInfo) == 0x08);

		class VariableInfo
		{
		public:
			// members
			BSFixedString name; // 0x00
			TypeInfo type;		// 0x08
			bool isConst;		// 0x10
		};

		static_assert(sizeof(VariableInfo) == 0x18);

		class InitialValueInfo
		{
		public:
			// members
			std::uint32_t variableIndex; // 0x00
			Variable initialValue;		 // 0x08
		};

		static_assert(sizeof(InitialValueInfo) == 0x18);

		class PropertyInfo
		{
		public:
			// members
			BSFixedString name;	   // 0x00
			PropertyTypeInfo info; // 0x08
		};

		static_assert(sizeof(PropertyInfo) == 0x48);

		class FunctionInfo
		{
		public:
			// members
			BSTSmartPointer<IFunction> func; // 0x00
		};

		static_assert(sizeof(FunctionInfo) == 0x08);

		class NamedStateInfo
		{
		public:
			[[nodiscard]]
			auto GetMemberFunctionCount() const noexcept -> std::uint32_t
			{
				return memberFunctionCount;
			}

			[[nodiscard]]
			auto GetMemberFunctionIt() noexcept -> FunctionInfo*;
			[[nodiscard]]
			auto GetMemberFunctionIt() const noexcept -> const FunctionInfo*;

			[[nodiscard]]
			auto GetMemberFunctions() noexcept -> std::span<FunctionInfo>;
			[[nodiscard]]
			auto GetMemberFunctions() const noexcept -> std::span<const FunctionInfo>;

			// members
			BSFixedString name;						 // 0x00
			std::uint32_t memberFunctionCount  : 9;	 // 0x08:00
			std::uint32_t memberFunctionOffset : 23; // 0x08:09
		};

		static_assert(sizeof(NamedStateInfo) == 0x10);

		~ObjectTypeInfo() override; // 0x00

		// override (IComplexType)
		auto GetRawType() const -> TypeInfo::RawType override // 0x01
		{
			return TypeInfo::RawType::Object;
		}

		[[nodiscard]]
		static auto GetEmptyStateName() -> const BSFixedString&;

		[[nodiscard]]
		auto GetName() const noexcept -> BSFixedString
		{
			return name;
		}

		[[nodiscard]]
		auto GetParentTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>
		{
			return parentTypeInfo;
		}

		[[nodiscard]]
		auto IsLinked() const noexcept -> bool;
		[[nodiscard]]
		auto IsLinkedValid() const noexcept -> bool;
		[[nodiscard]]
		auto IsLinkedInvalid() const noexcept -> bool;

		[[nodiscard]]
		auto IsConst() const noexcept -> bool;

		[[nodiscard]]
		auto GetParentTypeInfoIt() noexcept -> ObjectTypeInfo*;
		[[nodiscard]]
		auto GetParentTypeInfoIt() const noexcept -> const ObjectTypeInfo*;

		[[nodiscard]]
		auto GetThisUnlinkedNativeFunctionIt() noexcept -> UnlinkedNativeFunction*;
		[[nodiscard]]
		auto GetThisUnlinkedNativeFunctionIt() const noexcept -> const UnlinkedNativeFunction*;

		[[nodiscard]]
		auto GetThisUserFlagCount() const noexcept -> std::uint32_t
		{
			return userFlagCount;
		}

		[[nodiscard]]
		auto GetThisUserFlagIt() noexcept -> UserFlagInfo*;
		[[nodiscard]]
		auto GetThisUserFlagIt() const noexcept -> const UserFlagInfo*;

		[[nodiscard]]
		auto GetThisUserFlags() noexcept -> std::span<UserFlagInfo>;
		[[nodiscard]]
		auto GetThisUserFlags() const noexcept -> std::span<const UserFlagInfo>;

		[[nodiscard]]
		auto GetVariableCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetThisVariableCount() const noexcept -> std::uint32_t
		{
			return variableCount;
		}

		[[nodiscard]]
		auto GetThisVariableIt() noexcept -> VariableInfo*;
		[[nodiscard]]
		auto GetThisVariableIt() const noexcept -> const VariableInfo*;

		[[nodiscard]]
		auto GetThisVariables() noexcept -> std::span<VariableInfo>;
		[[nodiscard]]
		auto GetThisVariables() const noexcept -> std::span<const VariableInfo>;

		[[nodiscard]]
		auto GetInitialValueCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetThisInitialValueCount() const noexcept -> std::uint32_t
		{
			return initialValueCount;
		}

		[[nodiscard]]
		auto GetThisInitialValueIt() noexcept -> InitialValueInfo*;
		[[nodiscard]]
		auto GetThisInitialValueIt() const noexcept -> const InitialValueInfo*;

		[[nodiscard]]
		auto GetThisInitialValues() noexcept -> std::span<InitialValueInfo>;
		[[nodiscard]]
		auto GetThisInitialValues() const noexcept -> std::span<const InitialValueInfo>;

		[[nodiscard]]
		auto GetPropertyCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetThisPropertyCount() const noexcept -> std::uint32_t
		{
			return propertyCount;
		}

		[[nodiscard]]
		auto GetThisPropertyIt() noexcept -> PropertyInfo*;
		[[nodiscard]]
		auto GetThisPropertyIt() const noexcept -> const PropertyInfo*;

		[[nodiscard]]
		auto GetThisProperties() noexcept -> std::span<PropertyInfo>;
		[[nodiscard]]
		auto GetThisProperties() const noexcept -> std::span<const PropertyInfo>;

		[[nodiscard]]
		auto GetStaticFunctionCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetThisStaticFunctionCount() const noexcept -> std::uint32_t
		{
			return staticFunctionCount;
		}

		[[nodiscard]]
		auto GetThisStaticFunctionIt() noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetThisStaticFunctionIt() const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisStaticFunctions() noexcept -> std::span<FunctionInfo>;
		[[nodiscard]]
		auto GetThisStaticFunctions() const noexcept -> std::span<const FunctionInfo>;

		[[nodiscard]]
		auto GetMemberFunctionCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetThisMemberFunctionCount() const noexcept -> std::uint32_t
		{
			return emptyStateMemberFunctionCount;
		}

		[[nodiscard]]
		auto GetThisMemberFunctionIt() noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetThisMemberFunctionIt() const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisMemberFunctions() noexcept -> std::span<FunctionInfo>;
		[[nodiscard]]
		auto GetThisMemberFunctions() const noexcept -> std::span<const FunctionInfo>;

		[[nodiscard]]
		auto GetNamedStateCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetThisNamedStateCount() const noexcept -> std::uint32_t
		{
			return namedStateCount;
		}

		[[nodiscard]]
		auto GetThisNamedStateIt() noexcept -> NamedStateInfo*;
		[[nodiscard]]
		auto GetThisNamedStateIt() const noexcept -> const NamedStateInfo*;

		[[nodiscard]]
		auto GetThisNamedStates() noexcept -> std::span<NamedStateInfo>;
		[[nodiscard]]
		auto GetThisNamedStates() const noexcept -> std::span<const NamedStateInfo>;

		[[nodiscard]]
		auto GetDefaultStateInfo() noexcept -> NamedStateInfo*;
		[[nodiscard]]
		auto GetDefaultStateInfo() const noexcept -> const NamedStateInfo*;

		[[nodiscard]]
		auto GetThisDefaultStateInfo() noexcept -> NamedStateInfo*;
		[[nodiscard]]
		auto GetThisDefaultStateInfo() const noexcept -> const NamedStateInfo*;

		[[nodiscard]]
		auto GetVariableInfoByName(const BSFixedString& a_name) noexcept -> VariableInfo*;
		[[nodiscard]]
		auto GetVariableInfoByName(const BSFixedString& a_name) const noexcept -> const VariableInfo*;

		[[nodiscard]]
		auto GetThisVariableInfoByName(const BSFixedString& a_name) noexcept -> VariableInfo*;
		[[nodiscard]]
		auto GetThisVariableInfoByName(const BSFixedString& a_name) const noexcept -> const VariableInfo*;

		[[nodiscard]]
		auto GetPropertyInfoByName(const BSFixedString& a_name) noexcept -> PropertyInfo*;
		[[nodiscard]]
		auto GetPropertyInfoByName(const BSFixedString& a_name) const noexcept -> const PropertyInfo*;

		[[nodiscard]]
		auto GetThisPropertyInfoByName(const BSFixedString& a_name) noexcept -> PropertyInfo*;
		[[nodiscard]]
		auto GetThisPropertyInfoByName(const BSFixedString& a_name) const noexcept -> const PropertyInfo*;

		[[nodiscard]]
		auto GetFunctionInfoByName(const BSFixedString& a_name) noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetFunctionInfoByName(const BSFixedString& a_name) const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisFunctionInfoByName(const BSFixedString& a_name) noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetThisFunctionInfoByName(const BSFixedString& a_name) const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) noexcept
			-> FunctionInfo*;
		[[nodiscard]]
		auto GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) const noexcept
			-> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) noexcept
			-> FunctionInfo*;
		[[nodiscard]]
		auto GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) const noexcept
			-> const FunctionInfo*;

		[[nodiscard]]
		auto GetStaticFunctionInfoByName(const BSFixedString& a_name) noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetStaticFunctionInfoByName(const BSFixedString& a_name) const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisStaticFunctionInfoByName(const BSFixedString& a_name) noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetThisStaticFunctionInfoByName(const BSFixedString& a_name) const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetMemberFunctionInfoByName(const BSFixedString& a_name) noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetMemberFunctionInfoByName(const BSFixedString& a_name) const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisMemberFunctionInfoByName(const BSFixedString& a_name) noexcept -> FunctionInfo*;
		[[nodiscard]]
		auto GetThisMemberFunctionInfoByName(const BSFixedString& a_name) const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName) noexcept
			-> FunctionInfo*;
		[[nodiscard]]
		auto GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName)
			const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetThisMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName) noexcept
			-> FunctionInfo*;
		[[nodiscard]]
		auto GetThisMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName)
			const noexcept -> const FunctionInfo*;

		[[nodiscard]]
		auto GetNamedStateInfoByName(const BSFixedString& a_name) noexcept -> NamedStateInfo*;
		[[nodiscard]]
		auto GetNamedStateInfoByName(const BSFixedString& a_name) const noexcept -> const NamedStateInfo*;

		[[nodiscard]]
		auto GetThisNamedStateInfoByName(const BSFixedString& a_name) noexcept -> NamedStateInfo*;
		[[nodiscard]]
		auto GetThisNamedStateInfoByName(const BSFixedString& a_name) const noexcept -> const NamedStateInfo*;

		[[nodiscard]]
		auto ForEachUserFlagInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const UserFlagInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;
		[[nodiscard]]
		auto ForEachVariableInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const VariableInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;
		[[nodiscard]]
		auto ForEachPropertyInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const PropertyInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;
		[[nodiscard]]
		auto ForEachFunctionInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const FunctionInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;
		[[nodiscard]]
		auto ForEachMemberFunctionInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const FunctionInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;
		[[nodiscard]]
		auto ForEachStaticFunctionInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const FunctionInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;
		[[nodiscard]]
		auto ForEachNamedStateInfo(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NamedStateInfo&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;

		[[nodiscard]]
		auto GetVariableIndexByName(const BSFixedString& a_name) const noexcept -> std::optional<std::uint32_t>;
		[[nodiscard]]
		auto GetThisVariableIndexByName(const BSFixedString& a_name) const noexcept -> std::optional<std::uint32_t>;

		[[nodiscard]]
		auto GetPropertyIndexByName(const BSFixedString& a_name) const noexcept -> std::optional<std::uint32_t>;
		[[nodiscard]]
		auto GetThisPropertyIndexByName(const BSFixedString& a_name) const noexcept -> std::optional<std::uint32_t>;

		[[nodiscard]]
		auto IsChildOf(const ObjectTypeInfo* a_parentTypeInfo) const noexcept -> bool;
		[[nodiscard]]
		auto IsChildOf(const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) const noexcept -> bool;

		[[nodiscard]]
		auto IsParentOf(const ObjectTypeInfo* a_childTypeInfo) const noexcept -> bool;
		[[nodiscard]]
		auto IsParentOf(const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo) const noexcept -> bool;

		// members
		BSFixedString name;											 // 0x10
		BSTSmartPointer<ObjectTypeInfo> parentTypeInfo;				 // 0x18
		BSFixedString docString;									 // 0x20
		BSTArray<BSTSmartPointer<PropertyGroupInfo>> propertyGroups; // 0x28
		LinkValidState linkedValid					: 2;			 // 0x40:00
		std::uint32_t isConst						: 1;			 // 0x40:02
		std::uint32_t userFlagCount					: 5;			 // 0x40:03
		std::uint32_t variableCount					: 10;			 // 0x40:08
		std::uint32_t variableUserFlagCount			: 6;			 // 0x40:18
		std::uint32_t initialValueCount				: 10;			 // 0x44:00
		std::uint32_t propertyCount					: 10;			 // 0x44:10
		std::uint32_t staticFunctionCount			: 9;			 // 0x44:20
		std::uint32_t emptyStateMemberFunctionCount : 11;			 // 0x48:00
		std::uint32_t namedStateCount				: 7;			 // 0x48:11
		std::uint32_t initialState					: 7;			 // 0x48:18
		std::byte* data;											 // 0x50
	};

	static_assert(sizeof(ObjectTypeInfo) == 0x58);
}
