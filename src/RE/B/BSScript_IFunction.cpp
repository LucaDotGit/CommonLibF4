#include "RE/B/BSScript_IFunction.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"

namespace RE::BSScript
{
	bool IFunction::HasNoParams() const
	{
		return GetParamCount() == 0;
	}

	bool IFunction::HasParamsOfTypes(std::span<const TypeInfo> a_args) const
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam([a_args](std::uint32_t a_index, [[maybe_unused]] const BSFixedString& a_paramName, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			const auto& arg = a_args[a_index];
			if (arg != paramTypeInfo) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kContinue;
	}

	bool IFunction::HasParamsOfTypes(std::span<const Variable> a_args) const
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam([a_args](std::uint32_t a_index, [[maybe_unused]] const BSFixedString& a_paramName, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			const auto& arg = a_args[a_index];
			if (arg.GetTypeInfo() != paramTypeInfo) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kContinue;
	}

	bool IFunction::HasParamsOfVariadicTypes(std::span<const Variable> a_args) const
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam([a_args](std::uint32_t a_index, [[maybe_unused]] const BSFixedString& a_paramName, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			const auto& arg = a_args[a_index];
			if (!arg.IsVar()) {
				return arg.GetTypeInfo() == paramTypeInfo ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			const auto* var = arg.GetVar();
			if (!var) {
				return paramTypeInfo.IsVar() ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			return var->GetTypeInfo() == paramTypeInfo ?
					   BSContainer::ForEachResult::kContinue :
					   BSContainer::ForEachResult::kStop;
		}) == BSContainer::ForEachResult::kContinue;
	}

	bool IFunction::HasParamsOfVariadicTypes(std::span<const SharedVariant> a_args) const
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam([a_args](std::uint32_t a_index, [[maybe_unused]] const BSFixedString& a_paramName, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			const auto* arg = a_args[a_index];
			if (!arg) {
				return paramTypeInfo.IsNone() ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			if (!arg->IsVar()) {
				return arg->GetTypeInfo() == paramTypeInfo ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			const auto* var = arg->GetVar();
			if (!var) {
				return paramTypeInfo.IsVar() ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			return var->GetTypeInfo() == paramTypeInfo ?
					   BSContainer::ForEachResult::kContinue :
					   BSContainer::ForEachResult::kStop;
		}) == BSContainer::ForEachResult::kContinue;
	}

	bool IFunction::HasParamsOfVariadicTypes(std::span<const UniqueVariant> a_args) const
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam([a_args](std::uint32_t a_index, [[maybe_unused]] const BSFixedString& a_paramName, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			const auto& arg = a_args[a_index];
			if (!arg) {
				return paramTypeInfo.IsNone() ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			if (!arg->IsVar()) {
				return arg->GetTypeInfo() == paramTypeInfo ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			const auto* var = arg->GetVar();
			if (!var) {
				return paramTypeInfo.IsVar() ?
						   BSContainer::ForEachResult::kContinue :
						   BSContainer::ForEachResult::kStop;
			}

			return var->GetTypeInfo() == paramTypeInfo ?
					   BSContainer::ForEachResult::kContinue :
					   BSContainer::ForEachResult::kStop;
		}) == BSContainer::ForEachResult::kContinue;
	}

	auto IFunction::GetParamNames() const
		-> std::vector<BSFixedString>
	{
		auto paramNames = std::vector<BSFixedString>();
		paramNames.reserve(GetParamCount());

		ForEachParam([&paramNames](std::uint32_t, const BSFixedString& paramName, [[maybe_unused]] const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			paramNames.push_back(paramName);
			return BSContainer::ForEachResult::kContinue;
		});

		return paramNames;
	}

	auto IFunction::GetParamTypes() const
		-> std::vector<TypeInfo>
	{
		auto paramTypes = std::vector<TypeInfo>();
		paramTypes.reserve(GetParamCount());

		ForEachParam([&paramTypes](std::uint32_t, [[maybe_unused]] const BSFixedString&, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			paramTypes.push_back(paramTypeInfo);
			return BSContainer::ForEachResult::kContinue;
		});

		return paramTypes;
	}

	auto IFunction::GetParams() const
		-> std::vector<std::pair<BSFixedString, TypeInfo>>
	{
		auto params = std::vector<std::pair<BSFixedString, TypeInfo>>();
		params.reserve(GetParamCount());

		ForEachParam([&params](std::uint32_t, const BSFixedString& paramName, const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
			params.emplace_back(paramName, paramTypeInfo);
			return BSContainer::ForEachResult::kContinue;
		});

		return params;
	}

	BSContainer::ForEachResult IFunction::ForEachParam(
		const REX::NotNull<std::function<BSContainer::ForEachResult(std::uint32_t, const BSFixedString&, const TypeInfo&)>>& a_predicate) const
	{
		const auto paramCount = GetParamCount();

		for (auto i = 0ui32; i < paramCount; i++) {
			auto paramName = BSFixedString();
			auto paramTypeInfo = TypeInfo();

			GetParam(i, paramName, paramTypeInfo);

			if (std::invoke(*a_predicate, i, paramName, paramTypeInfo) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
