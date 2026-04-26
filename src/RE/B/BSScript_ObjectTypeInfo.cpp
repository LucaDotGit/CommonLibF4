#include "RE/B/BSScript_ObjectTypeInfo.hpp"

#include "RE/B/BSScript_IFunction.hpp" // IWYU pragma: keep
#include "RE/B/BSScript_LinkValidState.hpp"

namespace RE::BSScript
{
	BSFixedString ObjectTypeInfo::UserFlagInfo::GetUserFlag() const noexcept
	{
		auto sanitizedType = data & ~SET_ON_OBJECT_FLAG;
		return *reinterpret_cast<BSFixedString*>(std::addressof(sanitizedType));
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::NamedStateInfo::GetMemberFunctionIt() noexcept
	{
		return std::bit_cast<FunctionInfo*>(std::bit_cast<std::uintptr_t>(this) + memberFunctionOffset);
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::NamedStateInfo::GetMemberFunctionIt() const noexcept
	{
		return std::bit_cast<const FunctionInfo*>(std::bit_cast<std::uintptr_t>(this) + memberFunctionOffset);
	}

	std::span<ObjectTypeInfo::FunctionInfo> ObjectTypeInfo::NamedStateInfo::GetMemberFunctions() noexcept
	{
		return { GetMemberFunctionIt(), GetNumMemberFunctions() };
	}

	std::span<const ObjectTypeInfo::FunctionInfo> ObjectTypeInfo::NamedStateInfo::GetMemberFunctions() const noexcept
	{
		return { GetMemberFunctionIt(), GetNumMemberFunctions() };
	}

	const BSFixedString& ObjectTypeInfo::GetEmptyStateName()
	{
		static const auto EMPTY_STATE_NAME = BSFixedString(""sv);
		return EMPTY_STATE_NAME;
	}

	bool ObjectTypeInfo::IsLinked() const noexcept
	{
		switch (linkedValid) {
			case LinkValidState::kLinkedValid:
			case LinkValidState::kLinkedInvalid: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool ObjectTypeInfo::IsLinkedValid() const noexcept
	{
		return linkedValid == LinkValidState::kLinkedValid;
	}

	bool ObjectTypeInfo::IsLinkedInvalid() const noexcept
	{
		return linkedValid == LinkValidState::kLinkedInvalid;
	}

	bool ObjectTypeInfo::IsConst() const noexcept
	{
		return isConst != 0;
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	ObjectTypeInfo* ObjectTypeInfo::GetParentTypeIt() noexcept
	{
		return parentTypeInfo.get();
	}

	const ObjectTypeInfo* ObjectTypeInfo::GetParentTypeIt() const noexcept
	{
		return parentTypeInfo.get();
	}

	// NOLINTBEGIN(readability-make-member-function-const)

	ObjectTypeInfo::UnlinkedNativeFunction* ObjectTypeInfo::GetThisUnlinkedNativeFunctionIt() noexcept
	{
		REX::Assert(!IsLinked());
		return reinterpret_cast<UnlinkedNativeFunction*>(data);
	}

	const ObjectTypeInfo::UnlinkedNativeFunction* ObjectTypeInfo::GetThisUnlinkedNativeFunctionIt() const noexcept
	{
		REX::Assert(!IsLinked());
		return reinterpret_cast<const UnlinkedNativeFunction*>(data);
	}

	ObjectTypeInfo::UserFlagInfo* ObjectTypeInfo::GetThisUserFlagIt() noexcept
	{
		REX::Assert(IsLinked());
		return reinterpret_cast<UserFlagInfo*>(data);
	}

	const ObjectTypeInfo::UserFlagInfo* ObjectTypeInfo::GetThisUserFlagIt() const noexcept
	{
		REX::Assert(IsLinked());
		return reinterpret_cast<const UserFlagInfo*>(data);
	}

	std::span<ObjectTypeInfo::UserFlagInfo> ObjectTypeInfo::GetThisUserFlags() noexcept
	{
		return { GetThisUserFlagIt(), GetThisNumUserFlags() };
	}

	std::span<const ObjectTypeInfo::UserFlagInfo> ObjectTypeInfo::GetThisUserFlags() const noexcept
	{
		return { GetThisUserFlagIt(), GetThisNumUserFlags() };
	}

	std::uint32_t ObjectTypeInfo::GetNumVariables() const
	{
		auto numVars = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			numVars += typeIt->GetThisNumVariables();
		}

		return numVars;
	}

	ObjectTypeInfo::VariableInfo* ObjectTypeInfo::GetThisVariableIt() noexcept
	{
		return reinterpret_cast<VariableInfo*>(GetThisUserFlagIt() + GetThisNumUserFlags());
	}

	const ObjectTypeInfo::VariableInfo* ObjectTypeInfo::GetThisVariableIt() const noexcept
	{
		return reinterpret_cast<const VariableInfo*>(GetThisUserFlagIt() + GetThisNumUserFlags());
	}

	std::span<ObjectTypeInfo::VariableInfo> ObjectTypeInfo::GetThisVariables() noexcept
	{
		return { GetThisVariableIt(), GetThisNumVariables() };
	}

	std::span<const ObjectTypeInfo::VariableInfo> ObjectTypeInfo::GetThisVariables() const noexcept
	{
		return { GetThisVariableIt(), GetThisNumVariables() };
	}

	std::uint32_t ObjectTypeInfo::GetNumInitialValues() const
	{
		auto numInitialValues = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			numInitialValues += typeIt->GetThisNumInitialValues();
		}

		return numInitialValues;
	}

	ObjectTypeInfo::InitialValueInfo* ObjectTypeInfo::GetThisInitialValueIt() noexcept
	{
		return reinterpret_cast<InitialValueInfo*>(GetThisVariableIt() + GetThisNumVariables());
	}

	const ObjectTypeInfo::InitialValueInfo* ObjectTypeInfo::GetThisInitialValueIt() const noexcept
	{
		return reinterpret_cast<const InitialValueInfo*>(GetThisVariableIt() + GetThisNumVariables());
	}

	std::span<ObjectTypeInfo::InitialValueInfo> ObjectTypeInfo::GetThisInitialValues() noexcept
	{
		return { GetThisInitialValueIt(), GetThisNumInitialValues() };
	}

	std::span<const ObjectTypeInfo::InitialValueInfo> ObjectTypeInfo::GetThisInitialValues() const noexcept
	{
		return { GetThisInitialValueIt(), GetThisNumInitialValues() };
	}

	std::uint32_t ObjectTypeInfo::GetNumProperties() const
	{
		auto numProps = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			numProps += typeIt->GetThisNumProperties();
		}

		return numProps;
	}

	ObjectTypeInfo::PropertyInfo* ObjectTypeInfo::GetThisPropertyIt() noexcept
	{
		return reinterpret_cast<PropertyInfo*>(GetThisInitialValueIt() + GetThisNumInitialValues());
	}

	const ObjectTypeInfo::PropertyInfo* ObjectTypeInfo::GetThisPropertyIt() const noexcept
	{
		return reinterpret_cast<const PropertyInfo*>(GetThisInitialValueIt() + GetThisNumInitialValues());
	}

	std::span<ObjectTypeInfo::PropertyInfo> ObjectTypeInfo::GetThisProperties() noexcept
	{
		return { GetThisPropertyIt(), GetThisNumProperties() };
	}

	std::span<const ObjectTypeInfo::PropertyInfo> ObjectTypeInfo::GetThisProperties() const noexcept
	{
		return { GetThisPropertyIt(), GetThisNumProperties() };
	}

	std::uint32_t ObjectTypeInfo::GetNumStaticFunctions() const
	{
		auto numStaticFunctions = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			numStaticFunctions += typeIt->GetThisNumStaticFunctions();
		}

		return numStaticFunctions;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisStaticFunctionIt() noexcept
	{
		return reinterpret_cast<FunctionInfo*>(GetThisPropertyIt() + GetThisNumProperties());
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisStaticFunctionIt() const noexcept
	{
		return reinterpret_cast<const FunctionInfo*>(GetThisPropertyIt() + GetThisNumProperties());
	}

	std::span<ObjectTypeInfo::FunctionInfo> ObjectTypeInfo::GetThisStaticFunctions() noexcept { return { GetThisStaticFunctionIt(), GetThisNumStaticFunctions() }; }

	std::span<const ObjectTypeInfo::FunctionInfo> ObjectTypeInfo::GetThisStaticFunctions() const noexcept { return { GetThisStaticFunctionIt(), GetThisNumStaticFunctions() }; }

	std::uint32_t ObjectTypeInfo::GetNumMemberFunctions() const
	{
		auto numMemberFunctions = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			numMemberFunctions += typeIt->GetThisNumMemberFunctions();
		}

		return numMemberFunctions;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisMemberFunctionIt() noexcept
	{
		return reinterpret_cast<FunctionInfo*>(GetThisStaticFunctionIt() + GetThisNumStaticFunctions());
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisMemberFunctionIt() const noexcept
	{
		return reinterpret_cast<const FunctionInfo*>(GetThisStaticFunctionIt() + GetThisNumStaticFunctions());
	}

	std::span<ObjectTypeInfo::FunctionInfo> ObjectTypeInfo::GetThisMemberFunctions() noexcept
	{
		return { GetThisMemberFunctionIt(), GetThisNumMemberFunctions() };
	}

	std::span<const ObjectTypeInfo::FunctionInfo> ObjectTypeInfo::GetThisMemberFunctions() const noexcept
	{
		return { GetThisMemberFunctionIt(), GetThisNumMemberFunctions() };
	}

	std::uint32_t ObjectTypeInfo::GetNumNamedStates() const
	{
		auto numNamedStates = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			numNamedStates += typeIt->GetThisNumNamedStates();
		}

		return numNamedStates;
	}

	ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetThisNamedStateIt() noexcept
	{
		return reinterpret_cast<ObjectTypeInfo::NamedStateInfo*>(GetThisMemberFunctionIt() + GetThisNumMemberFunctions());
	}

	const ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetThisNamedStateIt() const noexcept
	{
		return reinterpret_cast<const NamedStateInfo*>(GetThisMemberFunctionIt() + GetThisNumMemberFunctions());
	}

	std::span<ObjectTypeInfo::NamedStateInfo> ObjectTypeInfo::GetThisNamedStates() noexcept
	{
		return { GetThisNamedStateIt(), GetThisNumNamedStates() };
	}

	std::span<const ObjectTypeInfo::NamedStateInfo> ObjectTypeInfo::GetThisNamedStates() const noexcept
	{
		return { GetThisNamedStateIt(), GetThisNumNamedStates() };
	}

	// NOLINTEND(readability-make-member-function-const)

	ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetDefaultStateInfo() noexcept
	{
		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* stateIt = typeIt->GetThisDefaultStateInfo();
			if (stateIt) {
				return stateIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetDefaultStateInfo() const noexcept
	{
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* stateIt = typeIt->GetThisDefaultStateInfo();
			if (stateIt) {
				return stateIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetThisDefaultStateInfo()
	{
		if (GetThisNumNamedStates() == 0) {
			return nullptr;
		}

		auto* stateIt = GetThisNamedStateIt();
		return std::addressof(stateIt[initialState]);
	}

	const ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetThisDefaultStateInfo() const
	{
		if (GetThisNumNamedStates() == 0) {
			return nullptr;
		}

		const auto* stateIt = GetThisNamedStateIt();
		return std::addressof(stateIt[initialState]);
	}

	ObjectTypeInfo::VariableInfo* ObjectTypeInfo::GetVariableInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* varIt = typeIt->GetThisVariableInfoByName(a_name);
			if (varIt) {
				return varIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::VariableInfo* ObjectTypeInfo::GetVariableInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* varIt = typeIt->GetThisVariableInfoByName(a_name);
			if (varIt) {
				return varIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::VariableInfo* ObjectTypeInfo::GetThisVariableInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* varBegin = GetThisVariableIt();
		auto* varEnd = varBegin + GetThisNumVariables();

		auto* varIt = std::lower_bound(varBegin, varEnd, a_name, [](const VariableInfo& a_varInfo, const BSFixedString& a_varName) {
			return a_varInfo.name < a_varName;
		});

		if (varIt == varEnd || varIt->name != a_name) {
			return nullptr;
		}

		return varIt;
	}

	const ObjectTypeInfo::VariableInfo* ObjectTypeInfo::GetThisVariableInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* varBegin = GetThisVariableIt();
		const auto* varEnd = varBegin + GetThisNumVariables();

		const auto* varIt = std::lower_bound(varBegin, varEnd, a_name, [](const VariableInfo& a_varInfo, const BSFixedString& a_varName) {
			return a_varInfo.name < a_varName;
		});

		if (varIt == varEnd || varIt->name != a_name) {
			return nullptr;
		}

		return varIt;
	}

	ObjectTypeInfo::PropertyInfo* ObjectTypeInfo::GetPropertyInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* propIt = typeIt->GetThisPropertyInfoByName(a_name);
			if (propIt) {
				return propIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::PropertyInfo* ObjectTypeInfo::GetPropertyInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* propIt = typeIt->GetThisPropertyInfoByName(a_name);
			if (propIt) {
				return propIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::PropertyInfo* ObjectTypeInfo::GetThisPropertyInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* propBegin = GetThisPropertyIt();
		auto* propEnd = propBegin + GetThisNumProperties();

		auto* propIt = std::lower_bound(propBegin, propEnd, a_name, [](const PropertyInfo& a_propInfo, const BSFixedString& a_propName) {
			return a_propInfo.name < a_propName;
		});

		if (propIt == propEnd || propIt->name != a_name) {
			return nullptr;
		}

		return propIt;
	}

	const ObjectTypeInfo::PropertyInfo* ObjectTypeInfo::GetThisPropertyInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* propBegin = GetThisPropertyIt();
		const auto* propEnd = propBegin + GetThisNumProperties();

		const auto* propIt = std::lower_bound(propBegin, propEnd, a_name, [](const PropertyInfo& a_propInfo, const BSFixedString& a_propName) {
			return a_propInfo.name < a_propName;
		});

		if (propIt == propEnd || propIt->name != a_name) {
			return nullptr;
		}

		return propIt;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name)
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

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name) const
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

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* funcIt = typeIt->GetThisFunctionInfoByName(a_name, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName)
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

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisFunctionInfoByName(const BSFixedString& a_name, const BSFixedString& a_stateName) const
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

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetStaticFunctionInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* funcIt = typeIt->GetThisStaticFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetStaticFunctionInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* funcIt = typeIt->GetThisStaticFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisStaticFunctionInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* funcBegin = GetThisStaticFunctionIt();
		auto* funcEnd = funcBegin + GetThisNumStaticFunctions();

		auto* funcIt = std::lower_bound(funcBegin, funcEnd, a_name, [](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) {
			const auto& func = a_funcInfo.func;
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

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisStaticFunctionInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* funcBegin = GetThisStaticFunctionIt();
		const auto* funcEnd = funcBegin + GetThisNumStaticFunctions();

		const auto* funcIt = std::lower_bound(funcBegin, funcEnd, a_name, [](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) {
			const auto& func = a_funcInfo.func;
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

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_name);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisMemberFunctionInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* funcBegin = GetThisMemberFunctionIt();
		auto* funcEnd = funcBegin + GetThisNumMemberFunctions();

		auto* funcIt = std::lower_bound(funcBegin, funcEnd, a_name, [](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) {
			const auto& func = a_funcInfo.func;
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

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisMemberFunctionInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* funcBegin = GetThisMemberFunctionIt();
		const auto* funcEnd = funcBegin + GetThisNumMemberFunctions();

		const auto* funcIt = std::lower_bound(funcBegin, funcEnd, a_name, [](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) {
			const auto& func = a_funcInfo.func;
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

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName)
	{
		if (a_funcName.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_funcName, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName) const
	{
		if (a_funcName.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* funcIt = typeIt->GetThisMemberFunctionInfoByName(a_funcName, a_stateName);
			if (funcIt) {
				return funcIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName)
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
		auto* stateEnd = stateBegin + GetThisNumNamedStates();

		auto* stateIt = std::lower_bound(stateBegin, stateEnd, a_stateName, [](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) {
			return a_stateInfo.name < a_stateName;
		});

		if (stateIt == stateEnd || stateIt->name != a_stateName) {
			return nullptr;
		}

		auto* funcBegin = stateIt->GetMemberFunctionIt();
		auto* funcEnd = funcBegin + stateIt->GetNumMemberFunctions();

		auto* funcIt = std::lower_bound(funcBegin, funcEnd, a_funcName, [](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) {
			const auto& func = a_funcInfo.func;
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

	const ObjectTypeInfo::FunctionInfo* ObjectTypeInfo::GetThisMemberFunctionInfoByName(const BSFixedString& a_funcName, const BSFixedString& a_stateName) const
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
		const auto* stateEnd = stateBegin + GetThisNumNamedStates();

		const auto* stateIt = std::lower_bound(stateBegin, stateEnd, a_stateName, [](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) {
			return a_stateInfo.name < a_stateName;
		});

		if (stateIt == stateEnd || stateIt->name != a_stateName) {
			return nullptr;
		}

		const auto* funcBegin = stateIt->GetMemberFunctionIt();
		const auto* funcEnd = funcBegin + stateIt->GetNumMemberFunctions();

		const auto* funcIt = std::lower_bound(funcBegin, funcEnd, a_funcName, [](const FunctionInfo& a_funcInfo, const BSFixedString& a_funcName) {
			const auto& func = a_funcInfo.func;
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

	ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetNamedStateInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			auto* stateIt = typeIt->GetThisNamedStateInfoByName(a_name);
			if (stateIt) {
				return stateIt;
			}
		}

		return nullptr;
	}

	const ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetNamedStateInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto* stateIt = typeIt->GetThisNamedStateInfoByName(a_name);
			if (stateIt) {
				return stateIt;
			}
		}

		return nullptr;
	}

	ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetThisNamedStateInfoByName(const BSFixedString& a_name)
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		auto* stateBegin = GetThisNamedStateIt();
		auto* stateEnd = stateBegin + GetThisNumNamedStates();

		auto* stateIt = std::lower_bound(stateBegin, stateEnd, a_name, [](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) {
			return a_stateInfo.name < a_stateName;
		});

		if (stateIt == stateEnd || stateIt->name != a_name) {
			return nullptr;
		}

		return stateIt;
	}

	const ObjectTypeInfo::NamedStateInfo* ObjectTypeInfo::GetThisNamedStateInfoByName(const BSFixedString& a_name) const
	{
		if (a_name.empty()) {
			return nullptr;
		}

		if (!IsLinked()) {
			return nullptr;
		}

		const auto* stateBegin = GetThisNamedStateIt();
		const auto* stateEnd = stateBegin + GetThisNumNamedStates();

		const auto* stateIt = std::lower_bound(stateBegin, stateEnd, a_name, [](const NamedStateInfo& a_stateInfo, const BSFixedString& a_stateName) {
			return a_stateInfo.name < a_stateName;
		});

		if (stateIt == stateEnd || stateIt->name != a_name) {
			return nullptr;
		}

		return stateIt;
	}

	auto ObjectTypeInfo::GetVariableIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		if (!IsLinked()) {
			return std::nullopt;
		}

		auto indexOffset = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto varIndex = typeIt->GetThisVariableIndex(a_name);
			if (varIndex) {
				return indexOffset + *varIndex;
			}

			indexOffset += typeIt->GetThisNumVariables();
		}

		return std::nullopt;
	}

	auto ObjectTypeInfo::GetThisVariableIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		const auto* varBegin = GetThisVariableIt();
		const auto* varEnd = varBegin + GetThisNumVariables();

		const auto* varIt = std::lower_bound(varBegin, varEnd, a_name, [](const VariableInfo& a_varInfo, const BSFixedString& a_varName) {
			return a_varInfo.name < a_varName;
		});

		if (varIt == varEnd || varIt->name != a_name) {
			return std::nullopt;
		}

		return static_cast<std::uint32_t>(std::distance(varBegin, varIt));
	}

	auto ObjectTypeInfo::GetPropertyIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		if (!IsLinked()) {
			return std::nullopt;
		}

		auto indexOffset = 0ui32;
		for (const auto* typeIt = this; typeIt; typeIt = typeIt->GetParentTypeIt()) {
			const auto propIndex = typeIt->GetThisPropertyIndex(a_name);
			if (propIndex) {
				return indexOffset + *propIndex;
			}

			indexOffset += typeIt->GetThisNumProperties();
		}

		return std::nullopt;
	}

	auto ObjectTypeInfo::GetThisPropertyIndex(const BSFixedString& a_name) const -> std::optional<std::uint32_t>
	{
		if (a_name.empty()) {
			return std::nullopt;
		}

		const auto* propBegin = GetThisPropertyIt();
		const auto* propEnd = propBegin + GetThisNumProperties();

		const auto* propIt = std::lower_bound(propBegin, propEnd, a_name, [](const PropertyInfo& a_propInfo, const BSFixedString& a_propName) {
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

	bool ObjectTypeInfo::IsChildOf(const ObjectTypeInfo* a_parentTypeInfo) const
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

	bool ObjectTypeInfo::IsChildOf(const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) const
	{
		return IsChildOf(a_parentTypeInfo.get());
	}

	bool ObjectTypeInfo::IsParentOf(const ObjectTypeInfo* a_childTypeInfo) const
	{
		if (!a_childTypeInfo) {
			return false;
		}

		if (this == a_childTypeInfo) {
			return true;
		}

		for (auto typeInfoIt = a_childTypeInfo->GetParentTypeInfo(); typeInfoIt; typeInfoIt = typeInfoIt->GetParentTypeInfo()) {
			if (typeInfoIt == this) {
				return true;
			}
		}

		return false;
	}

	bool ObjectTypeInfo::IsParentOf(const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo) const
	{
		return IsParentOf(a_childTypeInfo.get());
	}
}
