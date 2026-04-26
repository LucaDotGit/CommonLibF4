#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_PropertyGroupInfo.hpp"
#include "RE/B/BSScript_PropertyTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	enum class LinkValidState : std::uint32_t;

	class IFunction;

	class __declspec(novtable) ObjectTypeInfo
		: public IComplexType // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ObjectTypeInfo };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ObjectTypeInfo };

		class UnlinkedNativeFunction
		{
		public:
			// members
			UnlinkedNativeFunction* next;	 // 00
			BSTSmartPointer<IFunction> func; // 08
		};
		static_assert(sizeof(UnlinkedNativeFunction) == 0x10);

		class UserFlagInfo
		{
		public:
			inline static constexpr auto SET_ON_OBJECT_FLAG = static_cast<std::uintptr_t>(1) << 0;

			[[nodiscard]] BSFixedString GetUserFlag() const noexcept;

			// members
			std::uintptr_t data; // 00
		};
		static_assert(sizeof(UserFlagInfo) == 0x08);

		class VariableInfo
		{
		public:
			// members
			BSFixedString name; // 00
			TypeInfo type;		// 08
			bool isConst;		// 10
		};
		static_assert(sizeof(VariableInfo) == 0x18);

		class InitialValueInfo
		{
		public:
			// members
			std::uint32_t variableIndex; // 00
			Variable initialValue;		 // 08
		};
		static_assert(sizeof(InitialValueInfo) == 0x18);

		class PropertyInfo
		{
		public:
			// members
			BSFixedString name;	   // 00
			PropertyTypeInfo info; // 08
		};
		static_assert(sizeof(PropertyInfo) == 0x48);

		class FunctionInfo
		{
		public:
			// members
			BSTSmartPointer<IFunction> func; // 00
		};
		static_assert(sizeof(FunctionInfo) == 0x08);

		class NamedStateInfo
		{
		public:
			[[nodiscard]] std::uint32_t GetNumMemberFunctions() const noexcept { return memberFunctionCount; }
			[[nodiscard]] FunctionInfo* GetMemberFunctionIt() noexcept;
			[[nodiscard]] const FunctionInfo* GetMemberFunctionIt() const noexcept;

			[[nodiscard]] std::span<FunctionInfo> GetMemberFunctions() noexcept;
			[[nodiscard]] std::span<const FunctionInfo> GetMemberFunctions() const noexcept;

			// members
			BSFixedString name;						 // 00
			std::uint32_t memberFunctionCount  : 9;	 // 08:00
			std::uint32_t memberFunctionOffset : 23; // 08:09
		};
		static_assert(sizeof(NamedStateInfo) == 0x10);

		~ObjectTypeInfo() override; // 00

		// override (IComplexType)
		TypeInfo::RawType GetRawType() const override { return TypeInfo::RawType::kObject; } // 01

		[[nodiscard]] static const BSFixedString& GetEmptyStateName();

		[[nodiscard]] const BSFixedString& GetName() const noexcept { return name; }
		[[nodiscard]] BSTSmartPointer<ObjectTypeInfo> GetParentTypeInfo() const noexcept { return parentTypeInfo; }

		[[nodiscard]] bool IsLinked() const noexcept;
		[[nodiscard]] bool IsLinkedValid() const noexcept;
		[[nodiscard]] bool IsLinkedInvalid() const noexcept;

		[[nodiscard]] bool IsConst() const noexcept;

		[[nodiscard]] ObjectTypeInfo* GetParentTypeIt() noexcept;
		[[nodiscard]] const ObjectTypeInfo* GetParentTypeIt() const noexcept;

		[[nodiscard]] UnlinkedNativeFunction* GetThisUnlinkedNativeFunctionIt() noexcept;
		[[nodiscard]] const UnlinkedNativeFunction* GetThisUnlinkedNativeFunctionIt() const noexcept;

		[[nodiscard]] std::uint32_t GetThisNumUserFlags() const noexcept { return userFlagCount; }
		[[nodiscard]] UserFlagInfo* GetThisUserFlagIt() noexcept;
		[[nodiscard]] const UserFlagInfo* GetThisUserFlagIt() const noexcept;

		[[nodiscard]] std::span<UserFlagInfo> GetThisUserFlags() noexcept;
		[[nodiscard]] std::span<const UserFlagInfo> GetThisUserFlags() const noexcept;

		[[nodiscard]] std::uint32_t GetNumVariables() const;

		[[nodiscard]] std::uint32_t GetThisNumVariables() const noexcept { return variableCount; }
		[[nodiscard]] VariableInfo* GetThisVariableIt() noexcept;
		[[nodiscard]] const VariableInfo* GetThisVariableIt() const noexcept;

		[[nodiscard]] std::span<VariableInfo> GetThisVariables() noexcept;
		[[nodiscard]] std::span<const VariableInfo> GetThisVariables() const noexcept;

		[[nodiscard]] std::uint32_t GetNumInitialValues() const;

		[[nodiscard]] std::uint32_t GetThisNumInitialValues() const noexcept { return initialValueCount; }
		[[nodiscard]] InitialValueInfo* GetThisInitialValueIt() noexcept;
		[[nodiscard]] const InitialValueInfo* GetThisInitialValueIt() const noexcept;

		[[nodiscard]] std::span<InitialValueInfo> GetThisInitialValues() noexcept;
		[[nodiscard]] std::span<const InitialValueInfo> GetThisInitialValues() const noexcept;

		[[nodiscard]] std::uint32_t GetNumProperties() const;

		[[nodiscard]] std::uint32_t GetThisNumProperties() const noexcept { return propertyCount; }
		[[nodiscard]] PropertyInfo* GetThisPropertyIt() noexcept;
		[[nodiscard]] const PropertyInfo* GetThisPropertyIt() const noexcept;

		[[nodiscard]] std::span<PropertyInfo> GetThisProperties() noexcept;
		[[nodiscard]] std::span<const PropertyInfo> GetThisProperties() const noexcept;

		[[nodiscard]] std::uint32_t GetNumStaticFunctions() const;

		[[nodiscard]] std::uint32_t GetThisNumStaticFunctions() const noexcept { return staticFunctionCount; }
		[[nodiscard]] FunctionInfo* GetThisStaticFunctionIt() noexcept;
		[[nodiscard]] const FunctionInfo* GetThisStaticFunctionIt() const noexcept;

		[[nodiscard]] std::span<FunctionInfo> GetThisStaticFunctions() noexcept;
		[[nodiscard]] std::span<const FunctionInfo> GetThisStaticFunctions() const noexcept;

		[[nodiscard]] std::uint32_t GetNumMemberFunctions() const;

		[[nodiscard]] std::uint32_t GetThisNumMemberFunctions() const noexcept { return emptyStateMemberFunctionCount; }
		[[nodiscard]] FunctionInfo* GetThisMemberFunctionIt() noexcept;
		[[nodiscard]] const FunctionInfo* GetThisMemberFunctionIt() const noexcept;

		[[nodiscard]] std::span<FunctionInfo> GetThisMemberFunctions() noexcept;
		[[nodiscard]] std::span<const FunctionInfo> GetThisMemberFunctions() const noexcept;

		[[nodiscard]] std::uint32_t GetNumNamedStates() const;

		[[nodiscard]] std::uint32_t GetThisNumNamedStates() const noexcept { return namedStateCount; }
		[[nodiscard]] NamedStateInfo* GetThisNamedStateIt() noexcept;
		[[nodiscard]] const NamedStateInfo* GetThisNamedStateIt() const noexcept;

		[[nodiscard]] std::span<NamedStateInfo> GetThisNamedStates() noexcept;
		[[nodiscard]] std::span<const NamedStateInfo> GetThisNamedStates() const noexcept;

		[[nodiscard]] NamedStateInfo* GetDefaultStateInfo() noexcept;
		[[nodiscard]] const NamedStateInfo* GetDefaultStateInfo() const noexcept;

		[[nodiscard]] NamedStateInfo* GetThisDefaultStateInfo();
		[[nodiscard]] const NamedStateInfo* GetThisDefaultStateInfo() const;

		[[nodiscard]] VariableInfo* GetVariableInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const VariableInfo* GetVariableInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] VariableInfo* GetThisVariableInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const VariableInfo* GetThisVariableInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] PropertyInfo* GetPropertyInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const PropertyInfo* GetPropertyInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] PropertyInfo* GetThisPropertyInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const PropertyInfo* GetThisPropertyInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetFunctionInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const FunctionInfo* GetFunctionInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetThisFunctionInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const FunctionInfo* GetThisFunctionInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName);
		[[nodiscard]] const FunctionInfo* GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) const;

		[[nodiscard]] FunctionInfo* GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName);
		[[nodiscard]] const FunctionInfo* GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) const;

		[[nodiscard]] FunctionInfo* GetStaticFunctionInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const FunctionInfo* GetStaticFunctionInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetThisStaticFunctionInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const FunctionInfo* GetThisStaticFunctionInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetMemberFunctionInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const FunctionInfo* GetMemberFunctionInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetThisMemberFunctionInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const FunctionInfo* GetThisMemberFunctionInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] FunctionInfo* GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName);
		[[nodiscard]] const FunctionInfo* GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName) const;

		[[nodiscard]] FunctionInfo* GetThisMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName);
		[[nodiscard]] const FunctionInfo* GetThisMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName) const;

		[[nodiscard]] NamedStateInfo* GetNamedStateInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const NamedStateInfo* GetNamedStateInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] NamedStateInfo* GetThisNamedStateInfoByName(const BSFixedString& a_name);
		[[nodiscard]] const NamedStateInfo* GetThisNamedStateInfoByName(const BSFixedString& a_name) const;

		[[nodiscard]] auto GetVariableIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>;
		[[nodiscard]] auto GetThisVariableIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>;

		[[nodiscard]] auto GetPropertyIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>;
		[[nodiscard]] auto GetThisPropertyIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>;

		[[nodiscard]] bool IsChildOf(const ObjectTypeInfo* a_parentTypeInfo) const;
		[[nodiscard]] bool IsChildOf(const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) const;

		[[nodiscard]] bool IsParentOf(const ObjectTypeInfo* a_childTypeInfo) const;
		[[nodiscard]] bool IsParentOf(const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo) const;

		// members
		BSFixedString name;											 // 10
		BSTSmartPointer<ObjectTypeInfo> parentTypeInfo;				 // 18
		BSFixedString docString;									 // 20
		BSTArray<BSTSmartPointer<PropertyGroupInfo>> propertyGroups; // 28
		LinkValidState linkedValid					: 2;			 // 40:00
		std::uint32_t isConst						: 1;			 // 40:02
		std::uint32_t userFlagCount					: 5;			 // 40:03
		std::uint32_t variableCount					: 10;			 // 40:08
		std::uint32_t variableUserFlagCount			: 6;			 // 40:18
		std::uint32_t initialValueCount				: 10;			 // 44:00
		std::uint32_t propertyCount					: 10;			 // 44:10
		std::uint32_t staticFunctionCount			: 9;			 // 44:20
		std::uint32_t emptyStateMemberFunctionCount : 11;			 // 48:00
		std::uint32_t namedStateCount				: 7;			 // 48:11
		std::uint32_t initialState					: 7;			 // 48:18
		std::byte* data;											 // 50
	};
	static_assert(sizeof(ObjectTypeInfo) == 0x58);
}
