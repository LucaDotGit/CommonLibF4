#include "RE/B/BSScript_ObjectTypeInfo.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_LinkValidState.hpp"

namespace RE::BSScript
{
	auto ObjectTypeInfo::UserFlagInfo::GetUserFlag() const noexcept -> BSFixedString
	{
		auto sanitizedType = data & ~SET_ON_OBJECT_FLAG;
		return *reinterpret_cast<BSFixedString*>(std::addressof(sanitizedType));
	}

	auto ObjectTypeInfo::NamedStateInfo::GetMemberFunctionIt() noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		return std::bit_cast<FunctionInfo*>(std::bit_cast<std::uintptr_t>(this) + memberFunctionOffset);
	}

	auto ObjectTypeInfo::NamedStateInfo::GetMemberFunctionIt() const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		return std::bit_cast<const FunctionInfo*>(std::bit_cast<std::uintptr_t>(this) + memberFunctionOffset);
	}

	auto ObjectTypeInfo::NamedStateInfo::GetMemberFunctions() noexcept -> std::span<ObjectTypeInfo::FunctionInfo>
	{
		return {GetMemberFunctionIt(), GetMemberFunctionCount()};
	}

	auto ObjectTypeInfo::NamedStateInfo::GetMemberFunctions() const noexcept
		-> std::span<const ObjectTypeInfo::FunctionInfo>
	{
		return {GetMemberFunctionIt(), GetMemberFunctionCount()};
	}

	auto ObjectTypeInfo::GetEmptyStateName() -> const BSFixedString&
	{
		static const auto EMPTY_STATE_NAME = BSFixedString(""sv);
		return EMPTY_STATE_NAME;
	}

	auto ObjectTypeInfo::IsLinked() const noexcept -> bool
	{
		switch (linkedValid) {
			case LinkValidState::LinkedValid:
			case LinkValidState::LinkedInvalid: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto ObjectTypeInfo::IsLinkedValid() const noexcept -> bool
	{
		return linkedValid == LinkValidState::LinkedValid;
	}

	auto ObjectTypeInfo::IsLinkedInvalid() const noexcept -> bool
	{
		return linkedValid == LinkValidState::LinkedInvalid;
	}

	auto ObjectTypeInfo::IsConst() const noexcept -> bool
	{
		return isConst != 0;
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	auto ObjectTypeInfo::GetParentTypeInfoIt() noexcept -> ObjectTypeInfo*
	{
		return parentTypeInfo.get();
	}

	auto ObjectTypeInfo::GetParentTypeInfoIt() const noexcept -> const ObjectTypeInfo*
	{
		return parentTypeInfo.get();
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	auto ObjectTypeInfo::GetThisUnlinkedNativeFunctionIt() noexcept -> ObjectTypeInfo::UnlinkedNativeFunction*
	{
		REX::Assert(!IsLinked());
		return reinterpret_cast<UnlinkedNativeFunction*>(data);
	}

	auto ObjectTypeInfo::GetThisUnlinkedNativeFunctionIt() const noexcept
		-> const ObjectTypeInfo::UnlinkedNativeFunction*
	{
		REX::Assert(!IsLinked());
		return reinterpret_cast<const UnlinkedNativeFunction*>(data);
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	auto ObjectTypeInfo::GetThisUserFlagIt() noexcept -> ObjectTypeInfo::UserFlagInfo*
	{
		REX::Assert(IsLinked());
		return reinterpret_cast<UserFlagInfo*>(data);
	}

	auto ObjectTypeInfo::GetThisUserFlagIt() const noexcept -> const ObjectTypeInfo::UserFlagInfo*
	{
		REX::Assert(IsLinked());
		return reinterpret_cast<const UserFlagInfo*>(data);
	}

	auto ObjectTypeInfo::GetThisUserFlags() noexcept -> std::span<ObjectTypeInfo::UserFlagInfo>
	{
		return {GetThisUserFlagIt(), GetThisUserFlagCount()};
	}

	auto ObjectTypeInfo::GetThisUserFlags() const noexcept -> std::span<const ObjectTypeInfo::UserFlagInfo>
	{
		return {GetThisUserFlagIt(), GetThisUserFlagCount()};
	}

	auto ObjectTypeInfo::GetVariableCount() const noexcept -> std::uint32_t
	{
		auto numVars = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			numVars += typeIt->GetThisVariableCount();
		}

		return numVars;
	}

	auto ObjectTypeInfo::GetThisVariableIt() noexcept -> ObjectTypeInfo::VariableInfo*
	{
		return reinterpret_cast<VariableInfo*>(GetThisUserFlagIt() + GetThisUserFlagCount());
	}

	auto ObjectTypeInfo::GetThisVariableIt() const noexcept -> const ObjectTypeInfo::VariableInfo*
	{
		return reinterpret_cast<const VariableInfo*>(GetThisUserFlagIt() + GetThisUserFlagCount());
	}

	auto ObjectTypeInfo::GetThisVariables() noexcept -> std::span<ObjectTypeInfo::VariableInfo>
	{
		return {GetThisVariableIt(), GetThisVariableCount()};
	}

	auto ObjectTypeInfo::GetThisVariables() const noexcept -> std::span<const ObjectTypeInfo::VariableInfo>
	{
		return {GetThisVariableIt(), GetThisVariableCount()};
	}

	auto ObjectTypeInfo::GetInitialValueCount() const noexcept -> std::uint32_t
	{
		auto numInitialValues = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			numInitialValues += typeIt->GetThisInitialValueCount();
		}

		return numInitialValues;
	}

	auto ObjectTypeInfo::GetThisInitialValueIt() noexcept -> ObjectTypeInfo::InitialValueInfo*
	{
		return reinterpret_cast<InitialValueInfo*>(GetThisVariableIt() + GetThisVariableCount());
	}

	auto ObjectTypeInfo::GetThisInitialValueIt() const noexcept -> const ObjectTypeInfo::InitialValueInfo*
	{
		return reinterpret_cast<const InitialValueInfo*>(GetThisVariableIt() + GetThisVariableCount());
	}

	auto ObjectTypeInfo::GetThisInitialValues() noexcept -> std::span<ObjectTypeInfo::InitialValueInfo>
	{
		return {GetThisInitialValueIt(), GetThisInitialValueCount()};
	}

	auto ObjectTypeInfo::GetThisInitialValues() const noexcept -> std::span<const ObjectTypeInfo::InitialValueInfo>
	{
		return {GetThisInitialValueIt(), GetThisInitialValueCount()};
	}

	auto ObjectTypeInfo::GetPropertyCount() const noexcept -> std::uint32_t
	{
		auto numProps = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			numProps += typeIt->GetThisPropertyCount();
		}

		return numProps;
	}

	auto ObjectTypeInfo::GetThisPropertyIt() noexcept -> ObjectTypeInfo::PropertyInfo*
	{
		return reinterpret_cast<PropertyInfo*>(GetThisInitialValueIt() + GetThisInitialValueCount());
	}

	auto ObjectTypeInfo::GetThisPropertyIt() const noexcept -> const ObjectTypeInfo::PropertyInfo*
	{
		return reinterpret_cast<const PropertyInfo*>(GetThisInitialValueIt() + GetThisInitialValueCount());
	}

	auto ObjectTypeInfo::GetThisProperties() noexcept -> std::span<ObjectTypeInfo::PropertyInfo>
	{
		return {GetThisPropertyIt(), GetThisPropertyCount()};
	}

	auto ObjectTypeInfo::GetThisProperties() const noexcept -> std::span<const ObjectTypeInfo::PropertyInfo>
	{
		return {GetThisPropertyIt(), GetThisPropertyCount()};
	}

	auto ObjectTypeInfo::GetStaticFunctionCount() const noexcept -> std::uint32_t
	{
		auto numStaticFunctions = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			numStaticFunctions += typeIt->GetThisStaticFunctionCount();
		}

		return numStaticFunctions;
	}

	auto ObjectTypeInfo::GetThisStaticFunctionIt() noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		return reinterpret_cast<FunctionInfo*>(GetThisPropertyIt() + GetThisPropertyCount());
	}

	auto ObjectTypeInfo::GetThisStaticFunctionIt() const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		return reinterpret_cast<const FunctionInfo*>(GetThisPropertyIt() + GetThisPropertyCount());
	}

	auto ObjectTypeInfo::GetThisStaticFunctions() noexcept -> std::span<ObjectTypeInfo::FunctionInfo>
	{
		return {GetThisStaticFunctionIt(), GetThisStaticFunctionCount()};
	}

	auto ObjectTypeInfo::GetThisStaticFunctions() const noexcept -> std::span<const ObjectTypeInfo::FunctionInfo>
	{
		return {GetThisStaticFunctionIt(), GetThisStaticFunctionCount()};
	}

	auto ObjectTypeInfo::GetMemberFunctionCount() const noexcept -> std::uint32_t
	{
		auto numMemberFunctions = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			numMemberFunctions += typeIt->GetThisMemberFunctionCount();
		}

		return numMemberFunctions;
	}

	auto ObjectTypeInfo::GetThisMemberFunctionIt() noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		return reinterpret_cast<FunctionInfo*>(GetThisStaticFunctionIt() + GetThisStaticFunctionCount());
	}

	auto ObjectTypeInfo::GetThisMemberFunctionIt() const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		return reinterpret_cast<const FunctionInfo*>(GetThisStaticFunctionIt() + GetThisStaticFunctionCount());
	}

	auto ObjectTypeInfo::GetThisMemberFunctions() noexcept -> std::span<ObjectTypeInfo::FunctionInfo>
	{
		return {GetThisMemberFunctionIt(), GetThisMemberFunctionCount()};
	}

	auto ObjectTypeInfo::GetThisMemberFunctions() const noexcept -> std::span<const ObjectTypeInfo::FunctionInfo>
	{
		return {GetThisMemberFunctionIt(), GetThisMemberFunctionCount()};
	}

	auto ObjectTypeInfo::GetNamedStateCount() const noexcept -> std::uint32_t
	{
		auto numNamedStates = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			numNamedStates += typeIt->GetThisNamedStateCount();
		}

		return numNamedStates;
	}

	auto ObjectTypeInfo::GetThisNamedStateIt() noexcept -> ObjectTypeInfo::NamedStateInfo*
	{
		return reinterpret_cast<ObjectTypeInfo::NamedStateInfo*>(
			GetThisMemberFunctionIt() + GetThisMemberFunctionCount());
	}

	auto ObjectTypeInfo::GetThisNamedStateIt() const noexcept -> const ObjectTypeInfo::NamedStateInfo*
	{
		return reinterpret_cast<const NamedStateInfo*>(GetThisMemberFunctionIt() + GetThisMemberFunctionCount());
	}

	auto ObjectTypeInfo::GetThisNamedStates() noexcept -> std::span<ObjectTypeInfo::NamedStateInfo>
	{
		return {GetThisNamedStateIt(), GetThisNamedStateCount()};
	}

	auto ObjectTypeInfo::GetThisNamedStates() const noexcept -> std::span<const ObjectTypeInfo::NamedStateInfo>
	{
		return {GetThisNamedStateIt(), GetThisNamedStateCount()};
	}

	auto ObjectTypeInfo::GetDefaultStateInfo() noexcept -> ObjectTypeInfo::NamedStateInfo*
	{
		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* stateInfo = typeIt->GetThisDefaultStateInfo();
			if (stateInfo) {
				return stateInfo;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetDefaultStateInfo() const noexcept -> const ObjectTypeInfo::NamedStateInfo*
	{
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* stateInfo = typeIt->GetThisDefaultStateInfo();
			if (stateInfo) {
				return stateInfo;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisDefaultStateInfo() noexcept -> ObjectTypeInfo::NamedStateInfo*
	{
		const auto stateIndex = initialState;
		if (stateIndex >= GetThisNamedStateCount()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		auto* stateIt = GetThisNamedStateIt();
		return std::addressof(stateIt[stateIndex]);
	}

	auto ObjectTypeInfo::GetThisDefaultStateInfo() const noexcept -> const ObjectTypeInfo::NamedStateInfo*
	{
		const auto stateIndex = initialState;
		if (stateIndex >= GetThisNamedStateCount()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto* stateIt = GetThisNamedStateIt();
		return std::addressof(stateIt[stateIndex]);
	}

	auto ObjectTypeInfo::GetVariableInfoByName(const BSFixedString& a_name) noexcept -> ObjectTypeInfo::VariableInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* varIt = typeIt->GetThisVariableInfoByName(a_name);
			if (varIt) {
				return varIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetVariableInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::VariableInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* varIt = typeIt->GetThisVariableInfoByName(a_name);
			if (varIt) {
				return varIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisVariableInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::VariableInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* varBegin = GetThisVariableIt();
		auto* varEnd = varBegin + GetThisVariableCount();

		auto* varIt = std::lower_bound(
			varBegin,
			varEnd,
			a_name,
			[](const VariableInfo& a_varInfo, const BSFixedString& a_varName) noexcept -> bool {
				return a_varInfo.name < a_varName;
			});

		if (varIt == varEnd || varIt->name != a_name) {
			return nullptr;
		}

		return varIt;
	}

	auto ObjectTypeInfo::GetThisVariableInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::VariableInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* varBegin = GetThisVariableIt();
		const auto* varEnd = varBegin + GetThisVariableCount();

		const auto* varIt = std::lower_bound(
			varBegin,
			varEnd,
			a_name,
			[](const VariableInfo& a_varInfo, const BSFixedString& a_varName) noexcept -> bool {
				return a_varInfo.name < a_varName;
			});

		if (varIt == varEnd || varIt->name != a_name) {
			return nullptr;
		}

		return varIt;
	}

	auto ObjectTypeInfo::GetPropertyInfoByName(const BSFixedString& a_name) noexcept -> ObjectTypeInfo::PropertyInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* propIt = typeIt->GetThisPropertyInfoByName(a_name);
			if (propIt) {
				return propIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetPropertyInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::PropertyInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* propIt = typeIt->GetThisPropertyInfoByName(a_name);
			if (propIt) {
				return propIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisPropertyInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::PropertyInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* propBegin = GetThisPropertyIt();
		auto* propEnd = propBegin + GetThisPropertyCount();

		auto* propIt = std::lower_bound(
			propBegin,
			propEnd,
			a_name,
			[](const PropertyInfo& a_propInfo, const BSFixedString& a_propName) noexcept -> bool {
				return a_propInfo.name < a_propName;
			});

		if (propIt == propEnd || propIt->name != a_name) {
			return nullptr;
		}

		return propIt;
	}

	auto ObjectTypeInfo::GetThisPropertyInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::PropertyInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* propBegin = GetThisPropertyIt();
		const auto* propEnd = propBegin + GetThisPropertyCount();

		const auto* propIt = std::lower_bound(
			propBegin,
			propEnd,
			a_name,
			[](const PropertyInfo& a_propInfo, const BSFixedString& a_propName) noexcept -> bool {
				return a_propInfo.name < a_propName;
			});

		if (propIt == propEnd || propIt->name != a_name) {
			return nullptr;
		}

		return propIt;
	}

	auto ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name) noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* memberFunction = GetThisMemberFunctionInfoByName(a_name);
		if (memberFunction) {
			return memberFunction;
		}

		auto* staticFunction = GetThisStaticFunctionInfoByName(a_name);
		if (staticFunction) {
			return staticFunction;
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* memberFunction = GetThisMemberFunctionInfoByName(a_name);
		if (memberFunction) {
			return memberFunction;
		}

		const auto* staticFunction = GetThisStaticFunctionInfoByName(a_name);
		if (staticFunction) {
			return staticFunction;
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) noexcept
		-> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName)
		const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName)
		noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* memberFunction = GetThisMemberFunctionInfoByName(a_name, a_stateName);
		if (memberFunction) {
			return memberFunction;
		}

		if (a_stateName != GetEmptyStateName()) {
			return nullptr;
		}

		auto* staticFunction = GetThisStaticFunctionInfoByName(a_name);
		if (staticFunction) {
			return staticFunction;
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName)
		const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* memberFunction = GetThisMemberFunctionInfoByName(a_name, a_stateName);
		if (memberFunction) {
			return memberFunction;
		}

		if (a_stateName != GetEmptyStateName()) {
			return nullptr;
		}

		const auto* staticFunction = GetThisStaticFunctionInfoByName(a_name);
		if (staticFunction) {
			return staticFunction;
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetStaticFunctionInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* funcIt = typeIt->GetThisStaticFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetStaticFunctionInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* funcIt = typeIt->GetThisStaticFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisStaticFunctionInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* funcBegin = GetThisStaticFunctionIt();
		auto* funcEnd = funcBegin + GetThisStaticFunctionCount();

		auto* funcIt = std::lower_bound(
			funcBegin,
			funcEnd,
			a_name,
			[](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) noexcept -> bool {
				const auto func = a_funcInfo.func;
				return func ? func->GetName() < a_funcName : false;
			});

		if (funcIt == funcEnd) {
			return nullptr;
		}

		const auto& func = funcIt->func;
		if (!func || func->GetName() != a_name) {
			return nullptr;
		}

		return funcIt;
	}

	auto ObjectTypeInfo::GetThisStaticFunctionInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* funcBegin = GetThisStaticFunctionIt();
		const auto* funcEnd = funcBegin + GetThisStaticFunctionCount();

		const auto* funcIt = std::lower_bound(
			funcBegin,
			funcEnd,
			a_name,
			[](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) noexcept -> bool {
				const auto func = a_funcInfo.func;
				return func ? func->GetName() < a_funcName : false;
			});

		if (funcIt == funcEnd) {
			return nullptr;
		}

		const auto& func = funcIt->func;
		if (!func || func->GetName() != a_name) {
			return nullptr;
		}

		return funcIt;
	}

	auto ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisMemberFunctionInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* funcBegin = GetThisMemberFunctionIt();
		auto* funcEnd = funcBegin + GetThisMemberFunctionCount();

		auto* funcIt = std::lower_bound(
			funcBegin,
			funcEnd,
			a_name,
			[](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) noexcept -> bool {
				const auto func = a_funcInfo.func;
				return func ? func->GetName() < a_funcName : false;
			});

		if (funcIt == funcEnd) {
			return nullptr;
		}

		const auto& func = funcIt->func;
		if (!func || func->GetName() != a_name) {
			return nullptr;
		}

		return funcIt;
	}

	auto ObjectTypeInfo::GetThisMemberFunctionInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* funcBegin = GetThisMemberFunctionIt();
		const auto* funcEnd = funcBegin + GetThisMemberFunctionCount();

		const auto* funcIt = std::lower_bound(
			funcBegin,
			funcEnd,
			a_name,
			[](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) noexcept -> bool {
				const auto func = a_funcInfo.func;
				return func ? func->GetName() < a_funcName : false;
			});

		if (funcIt == funcEnd) {
			return nullptr;
		}

		const auto& func = funcIt->func;
		if (!func || func->GetName() != a_name) {
			return nullptr;
		}

		return funcIt;
	}

	auto ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName)
		noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		if (a_funcName.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_funcName, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName)
		const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_funcName.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_funcName, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisMemberFunctionInfoByName(
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) noexcept -> ObjectTypeInfo::FunctionInfo*
	{
		if (a_funcName.empty()) {
			return nullptr;
		}

		if (a_stateName == GetEmptyStateName()) {
			return GetThisMemberFunctionInfoByName(a_funcName);
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* stateBegin = GetThisNamedStateIt();
		auto* stateEnd = stateBegin + GetThisNamedStateCount();

		auto* stateIt = std::lower_bound(
			stateBegin,
			stateEnd,
			a_stateName,
			[](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) noexcept -> bool {
				return a_stateInfo.name < a_stateName;
			});

		if (stateIt == stateEnd || stateIt->name != a_stateName) {
			return nullptr;
		}

		auto* funcBegin = stateIt->GetMemberFunctionIt();
		auto* funcEnd = funcBegin + stateIt->GetMemberFunctionCount();

		auto* funcIt = std::lower_bound(
			funcBegin,
			funcEnd,
			a_funcName,
			[](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) noexcept -> bool {
				const auto func = a_funcInfo.func;
				return func ? func->GetName() < a_funcName : false;
			});

		if (funcIt == funcEnd) {
			return nullptr;
		}

		const auto& func = funcIt->func;
		if (!func || func->GetName() != a_funcName) {
			return nullptr;
		}

		return funcIt;
	}

	auto ObjectTypeInfo::GetThisMemberFunctionInfoByName(
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) const noexcept -> const ObjectTypeInfo::FunctionInfo*
	{
		if (a_funcName.empty()) {
			return nullptr;
		}

		if (a_stateName == GetEmptyStateName()) {
			return GetThisMemberFunctionInfoByName(a_funcName);
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* stateBegin = GetThisNamedStateIt();
		const auto* stateEnd = stateBegin + GetThisNamedStateCount();

		const auto* stateIt = std::lower_bound(
			stateBegin,
			stateEnd,
			a_stateName,
			[](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) noexcept -> bool {
				return a_stateInfo.name < a_stateName;
			});

		if (stateIt == stateEnd || stateIt->name != a_stateName) {
			return nullptr;
		}

		const auto* funcBegin = stateIt->GetMemberFunctionIt();
		const auto* funcEnd = funcBegin + stateIt->GetMemberFunctionCount();

		const auto* funcIt = std::lower_bound(
			funcBegin,
			funcEnd,
			a_funcName,
			[](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) noexcept -> bool {
				const auto func = a_funcInfo.func;
				return func ? func->GetName() < a_funcName : false;
			});

		if (funcIt == funcEnd) {
			return nullptr;
		}

		const auto& func = funcIt->func;
		if (!func || func->GetName() != a_funcName) {
			return nullptr;
		}

		return funcIt;
	}

	auto ObjectTypeInfo::GetNamedStateInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::NamedStateInfo*
	{
		if (a_name == GetEmptyStateName()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			auto* stateIt = typeIt->GetThisNamedStateInfoByName(a_name);
			if (stateIt) {
				return stateIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetNamedStateInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::NamedStateInfo*
	{
		if (a_name == GetEmptyStateName()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* stateIt = typeIt->GetThisNamedStateInfoByName(a_name);
			if (stateIt) {
				return stateIt;
			}
		}

		return nullptr;
	}

	auto ObjectTypeInfo::GetThisNamedStateInfoByName(const BSFixedString& a_name) noexcept
		-> ObjectTypeInfo::NamedStateInfo*
	{
		if (a_name == GetEmptyStateName()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* stateBegin = GetThisNamedStateIt();
		auto* stateEnd = stateBegin + GetThisNamedStateCount();

		auto* stateIt = std::lower_bound(
			stateBegin,
			stateEnd,
			a_name,
			[](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) noexcept -> bool {
				return a_stateInfo.name < a_stateName;
			});

		if (stateIt == stateEnd || stateIt->name != a_name) {
			return nullptr;
		}

		return stateIt;
	}

	auto ObjectTypeInfo::GetThisNamedStateInfoByName(const BSFixedString& a_name) const noexcept
		-> const ObjectTypeInfo::NamedStateInfo*
	{
		if (a_name == GetEmptyStateName()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* stateBegin = GetThisNamedStateIt();
		const auto* stateEnd = stateBegin + GetThisNamedStateCount();

		const auto* stateIt = std::lower_bound(
			stateBegin,
			stateEnd,
			a_name,
			[](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) noexcept -> bool {
				return a_stateInfo.name < a_stateName;
			});

		if (stateIt == stateEnd || stateIt->name != a_name) {
			return nullptr;
		}

		return stateIt;
	}

	auto ObjectTypeInfo::ForEachUserFlagInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const UserFlagInfo&) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* flagBegin = typeIt->GetThisUserFlagIt();
			const auto* flagEnd = flagBegin + typeIt->GetThisUserFlagCount();

			for (const auto* flagIt = flagBegin; flagIt != flagEnd; flagIt++) {
				if (std::invoke(a_predicate.get(), *flagIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::ForEachVariableInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const VariableInfo&) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* varBegin = typeIt->GetThisVariableIt();
			const auto* varEnd = varBegin + typeIt->GetThisVariableCount();

			for (const auto* varIt = varBegin; varIt != varEnd; varIt++) {
				if (std::invoke(a_predicate.get(), *varIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::ForEachPropertyInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const PropertyInfo&) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* propBegin = typeIt->GetThisPropertyIt();
			const auto* propEnd = propBegin + typeIt->GetThisPropertyCount();

			for (const auto* propIt = propBegin; propIt != propEnd; propIt++) {
				if (std::invoke(a_predicate.get(), *propIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::ForEachFunctionInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const FunctionInfo&) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* staticFuncBegin = typeIt->GetThisStaticFunctionIt();
			const auto* staticFuncEnd = staticFuncBegin + typeIt->GetThisStaticFunctionCount();

			for (const auto* funcIt = staticFuncBegin; funcIt != staticFuncEnd; funcIt++) {
				if (std::invoke(a_predicate.get(), *funcIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}

			const auto* memberFuncBegin = typeIt->GetThisMemberFunctionIt();
			const auto* memberFuncEnd = memberFuncBegin + typeIt->GetThisMemberFunctionCount();

			for (const auto* funcIt = memberFuncBegin; funcIt != memberFuncEnd; funcIt++) {
				if (std::invoke(a_predicate.get(), *funcIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::ForEachMemberFunctionInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const FunctionInfo&) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* memberFuncBegin = typeIt->GetThisMemberFunctionIt();
			const auto* memberFuncEnd = memberFuncBegin + typeIt->GetThisMemberFunctionCount();

			for (const auto* funcIt = memberFuncBegin; funcIt != memberFuncEnd; funcIt++) {
				if (std::invoke(a_predicate.get(), *funcIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::ForEachStaticFunctionInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const FunctionInfo&) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* staticFuncBegin = typeIt->GetThisStaticFunctionIt();
			const auto* staticFuncEnd = staticFuncBegin + typeIt->GetThisStaticFunctionCount();

			for (const auto* funcIt = staticFuncBegin; funcIt != staticFuncEnd; funcIt++) {
				if (std::invoke(a_predicate.get(), *funcIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::ForEachNamedStateInfo(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NamedStateInfo&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (!IsLinked()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto* stateBegin = typeIt->GetThisNamedStateIt();
			const auto* stateEnd = stateBegin + typeIt->GetThisNamedStateCount();

			for (const auto* stateIt = stateBegin; stateIt != stateEnd; stateIt++) {
				if (std::invoke(a_predicate.get(), *stateIt) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ObjectTypeInfo::GetVariableIndexByName(const BSFixedString& a_name) const noexcept
		-> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		if (!IsLinked()) {
			return std::nullopt;
		}

		auto indexOffset = static_cast<std::uint32_t>(0);
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto varIndex = typeIt->GetThisVariableIndexByName(a_name);
			if (varIndex.has_value()) {
				return indexOffset + varIndex.value();
			}

			indexOffset += typeIt->GetThisVariableCount();
		}

		return std::nullopt;
	}

	auto ObjectTypeInfo::GetThisVariableIndexByName(const BSFixedString& a_name) const noexcept
		-> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		if (!IsLinked()) {
			return std::nullopt;
		}

		const auto* varBegin = GetThisVariableIt();
		const auto* varEnd = varBegin + GetThisVariableCount();

		const auto* varIt = std::lower_bound(
			varBegin,
			varEnd,
			a_name,
			[](const VariableInfo& a_varInfo, const BSFixedString& a_varName) noexcept -> bool {
				return a_varInfo.name < a_varName;
			});

		if (varIt == varEnd || varIt->name != a_name) {
			return std::nullopt;
		}

		return static_cast<std::uint32_t>(std::distance(varBegin, varIt));
	}

	auto ObjectTypeInfo::GetPropertyIndexByName(const BSFixedString& a_name) const noexcept
		-> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		if (!IsLinked()) {
			return std::nullopt;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeInfoIt()) {
			const auto propIndex = typeIt->GetThisPropertyIndexByName(a_name);
			if (propIndex.has_value()) {
				return propIndex;
			}
		}

		return std::nullopt;
	}

	auto ObjectTypeInfo::GetThisPropertyIndexByName(const BSFixedString& a_name) const noexcept
		-> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		if (!IsLinked()) {
			return std::nullopt;
		}

		const auto* propBegin = GetThisPropertyIt();
		const auto* propEnd = propBegin + GetThisPropertyCount();

		const auto* propIt = std::lower_bound(
			propBegin,
			propEnd,
			a_name,
			[](const PropertyInfo& a_propInfo, const BSFixedString& a_propName) noexcept -> bool {
				return a_propInfo.name < a_propName;
			});

		if (propIt == propEnd || propIt->name != a_name) {
			return std::nullopt;
		}

		const auto varIndex = propIt->info.autoVarIndex;
		if (varIndex == std::numeric_limits<decltype(varIndex)>::max()) {
			return std::nullopt;
		}

		return varIndex;
	}

	auto ObjectTypeInfo::IsChildOf(const ObjectTypeInfo* a_parentTypeInfo) const noexcept -> bool
	{
		if (!a_parentTypeInfo) {
			return false;
		}

		if (this == a_parentTypeInfo) {
			return true;
		}

		for (auto typeInfoIt = GetParentTypeInfo(); typeInfoIt; typeInfoIt = typeInfoIt->GetParentTypeInfo()) {
			if (typeInfoIt == a_parentTypeInfo) {
				return true;
			}
		}

		return false;
	}

	auto ObjectTypeInfo::IsChildOf(const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) const noexcept -> bool
	{
		return IsChildOf(a_parentTypeInfo.get());
	}

	auto ObjectTypeInfo::IsParentOf(const ObjectTypeInfo* a_childTypeInfo) const noexcept -> bool
	{
		if (!a_childTypeInfo) {
			return false;
		}

		if (this == a_childTypeInfo) {
			return true;
		}

		for (auto typeInfoIt = a_childTypeInfo->GetParentTypeInfo(); typeInfoIt;
			 typeInfoIt = typeInfoIt->GetParentTypeInfo()) {
			if (typeInfoIt == this) {
				return true;
			}
		}

		return false;
	}

	auto ObjectTypeInfo::IsParentOf(const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo) const noexcept -> bool
	{
		return IsParentOf(a_childTypeInfo.get());
	}
}
