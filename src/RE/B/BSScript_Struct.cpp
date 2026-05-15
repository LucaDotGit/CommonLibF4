#include "RE/B/BSScript_Struct.hpp"

#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"

namespace RE::BSScript
{
	Struct::Struct() noexcept = default;

	Struct::~Struct() noexcept
	{
		if (!IsConstructed()) {
			return;
		}

		const auto memberSize = type ? type->variables.size() : 0;
		for (auto i = 0ui32; i < memberSize; i++) {
			variables[i].reset();
		}

		constructed = false;
	}

	bool Struct::Equals(const Struct& a_rhs) const noexcept
	{
		return RefEquals(a_rhs);
	}

	bool Struct::RefEquals(const Struct& a_rhs) const noexcept
	{
		return this == std::addressof(a_rhs);
	}

	bool Struct::DeepEquals(const Struct& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftType = type;
		const auto rightType = a_rhs.type;

		if (!leftType || !rightType) {
			return false;
		}

		if (leftType != rightType) {
			return false;
		}

		const auto leftMemberLock = BSAutoLock(structLock);
		const auto rightMemberLock = BSAutoLock(a_rhs.structLock);

		const auto leftMemberSize = type->variables.size();
		const auto rightMemberSize = a_rhs.type->variables.size();

		if (leftMemberSize != rightMemberSize) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		for (auto i = 0ui32; i < leftMemberSize; i++) {
			const auto& leftVar = variables[i];
			const auto& rightVar = a_rhs.variables[i];

			if (!leftVar.DeepEquals(rightVar)) {
				return false;
			}
		}

		return true;
	}

	std::strong_ordering Struct::Compare(const Struct& a_rhs) const noexcept
	{
		return RefCompare(a_rhs);
	}

	std::strong_ordering Struct::RefCompare(const Struct& a_rhs) const noexcept
	{
		return this <=> std::addressof(a_rhs);
	}

	std::partial_ordering Struct::DeepCompare(const Struct& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftType = type;
		const auto rightType = a_rhs.type;

		if (!leftType || !rightType) {
			return leftType <=> rightType;
		}

		const auto typeComparison = leftType <=> rightType;
		if (typeComparison != std::strong_ordering::equal) {
			return typeComparison;
		}

		const auto leftMemberLock = BSAutoLock(structLock);
		const auto rightMemberLock = BSAutoLock(a_rhs.structLock);

		const auto leftMemberSize = type->variables.size();
		const auto rightMemberSize = a_rhs.type->variables.size();

		if (leftMemberSize != rightMemberSize) [[unlikely]] {
			REX::Assert(false);
			return leftMemberSize <=> rightMemberSize;
		}

		for (auto i = 0ui32; i < leftMemberSize; i++) {
			const auto& leftVar = variables[i];
			const auto& rightVar = a_rhs.variables[i];

			const auto varComparison = leftVar.DeepCompare(rightVar);
			if (varComparison != std::partial_ordering::equivalent) {
				return varComparison;
			}
		}

		return std::partial_ordering::equivalent;
	}

	BSTSmartPointer<StructTypeInfo> Struct::GetTypeInfo() const noexcept
	{
		return type;
	}

	auto Struct::GetTypeInfoName() const noexcept
		-> std::optional<BSFixedString>
	{
		if (!type) {
			return std::nullopt;
		}

		return type->GetName();
	}

	auto Struct::GetVariables() noexcept
		-> std::span<Variable>
	{
		if (!type) {
			return {};
		}

		return { static_cast<Variable*>(variables), type->variables.size() };
	}

	auto Struct::GetVariables() const noexcept
		-> std::span<const Variable>
	{
		if (!type) {
			return {};
		}

		return { static_cast<const Variable*>(variables), type->variables.size() };
	}

	Variable* Struct::GetVariable(const BSFixedString& a_name)
	{
		if (!type) {
			return nullptr;
		}

		const auto& memberPairMap = type->varNameIndexMap;

		const auto varIt = memberPairMap.find(a_name);
		if (varIt == memberPairMap.end()) {
			return nullptr;
		}

		const auto varIndex = varIt->second;
		if (varIndex >= type->variables.size()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return std::addressof(variables[varIndex]);
	}

	const Variable* Struct::GetVariable(const BSFixedString& a_name) const
	{
		if (!type) {
			return nullptr;
		}

		const auto& memberPairMap = type->varNameIndexMap;

		const auto varIt = memberPairMap.find(a_name);
		if (varIt == memberPairMap.end()) {
			return nullptr;
		}

		const auto varIndex = varIt->second;
		if (varIndex >= type->variables.size()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return std::addressof(variables[varIndex]);
	}

	bool Struct::SetVariable(const BSFixedString& a_name, const Variable& a_value)
	{
		auto* variable = GetVariable(a_name);
		if (!variable) {
			return false;
		}

		*variable = a_value;
		return true;
	}

	BSTSmartPointer<Struct> Struct::Clone(IVirtualMachine& a_vm) const
	{
		const auto memberLock = BSAutoLock(structLock);
		const auto memberSize = type->variables.size();

		auto result = BSTSmartPointer<Struct>();
		if (!a_vm.CreateStruct(type->GetName(), result) || !result) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto otherMemberLock = BSAutoLock(result->structLock);

		for (auto i = 0ui32; i < memberSize; i++) {
			result->variables[i] = variables[i].Clone(a_vm);
		}

		return result;
	}

	BSTSmartPointer<Struct> Struct::DeepClone(IVirtualMachine& a_vm) const
	{
		const auto memberLock = BSAutoLock(structLock);
		const auto memberSize = type->variables.size();

		auto result = BSTSmartPointer<Struct>();
		if (!a_vm.CreateStruct(type->GetName(), result) || !result) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto otherMemberLock = BSAutoLock(result->structLock);

		for (auto i = 0ui32; i < memberSize; i++) {
			result->variables[i] = variables[i].DeepClone(a_vm);
		}

		return result;
	}

	std::string Struct::ToString() const
	{
		if (!type) {
			return std::string(BSScript::NONE_STRING);
		}

		const auto memberLock = BSAutoLock(structLock);
		const auto memberSize = type->variables.size();

		const auto& memberPairMap = type->varNameIndexMap;

		auto result = std::string("["sv);

		for (auto i = 0ui32; i < memberSize; i++) {
			const auto pairIt = std::ranges::find_if(memberPairMap, [i](const BSTPair<const BSFixedString, std::uint32_t>& a_pair) -> bool {
				return a_pair.second == i;
			});

			if (pairIt == memberPairMap.end()) [[unlikely]] {
				REX::Assert(false);
				continue;
			}

			const auto& varKey = pairIt->first;
			const auto& varValue = variables[i];

			result += REX::Format("{} = {}"sv,
				varKey, varValue.ToString());

			if (i < memberSize - 1) {
				result += ", "sv;
			}
		}

		result += "]"sv;
		return result;
	}
}
