#include "RE/B/BSScript_IFunction.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"

namespace RE::BSScript
{
	auto IFunction::HasNoParams() const -> bool
	{
		return GetParamCount() == 0;
	}

	auto IFunction::HasParamsOfTypes(std::span<const TypeInfo> a_args) const -> bool
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam(
				   [a_args](
					   std::uint32_t a_index,
					   [[maybe_unused]]
					   const BSFixedString& a_paramName,
					   const TypeInfo& paramTypeInfo) noexcept -> BSContainer::ForEachResult {
					   const auto& arg = a_args[a_index];
					   if (arg != paramTypeInfo) {
						   return BSContainer::ForEachResult::Stop;
					   }

					   return BSContainer::ForEachResult::Continue;
				   }) == BSContainer::ForEachResult::Continue;
	}

	auto IFunction::HasParamsOfTypes(std::span<const Variable> a_args) const -> bool
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam(
				   [a_args](
					   std::uint32_t a_index,
					   [[maybe_unused]]
					   const BSFixedString& a_paramName,
					   const TypeInfo& paramTypeInfo) noexcept -> BSContainer::ForEachResult {
					   const auto& arg = a_args[a_index];
					   if (arg.GetTypeInfo() != paramTypeInfo) {
						   return BSContainer::ForEachResult::Stop;
					   }

					   return BSContainer::ForEachResult::Continue;
				   }) == BSContainer::ForEachResult::Continue;
	}

	auto IFunction::HasParamsOfVariadicTypes(std::span<const Variable> a_args) const -> bool
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam(
				   [a_args](
					   std::uint32_t a_index,
					   [[maybe_unused]]
					   const BSFixedString& a_paramName,
					   const TypeInfo& paramTypeInfo) noexcept -> BSContainer::ForEachResult {
					   const auto& arg = a_args[a_index];
					   if (!arg.IsVariant()) {
						   return arg.GetTypeInfo() == paramTypeInfo ? BSContainer::ForEachResult::Continue :
																	   BSContainer::ForEachResult::Stop;
					   }

					   const auto* variant = arg.GetVariant();
					   if (!variant) {
						   return paramTypeInfo.IsVariant() ? BSContainer::ForEachResult::Continue :
															  BSContainer::ForEachResult::Stop;
					   }

					   return variant->GetTypeInfo() == paramTypeInfo ? BSContainer::ForEachResult::Continue :
																		BSContainer::ForEachResult::Stop;
				   }) == BSContainer::ForEachResult::Continue;
	}

	auto IFunction::HasParamsOfVariadicTypes(std::span<const SharedVariant> a_args) const -> bool
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam(
				   [a_args](
					   std::uint32_t a_index,
					   [[maybe_unused]]
					   const BSFixedString& a_paramName,
					   const TypeInfo& paramTypeInfo) noexcept -> BSContainer::ForEachResult {
					   const auto* arg = a_args[a_index];
					   if (!arg) {
						   return paramTypeInfo.IsNone() ? BSContainer::ForEachResult::Continue :
														   BSContainer::ForEachResult::Stop;
					   }

					   if (!arg->IsVariant()) {
						   return arg->GetTypeInfo() == paramTypeInfo ? BSContainer::ForEachResult::Continue :
																		BSContainer::ForEachResult::Stop;
					   }

					   const auto* variant = arg->GetVariant();
					   if (!variant) {
						   return paramTypeInfo.IsVariant() ? BSContainer::ForEachResult::Continue :
															  BSContainer::ForEachResult::Stop;
					   }

					   return variant->GetTypeInfo() == paramTypeInfo ? BSContainer::ForEachResult::Continue :
																		BSContainer::ForEachResult::Stop;
				   }) == BSContainer::ForEachResult::Continue;
	}

	auto IFunction::HasParamsOfVariadicTypes(std::span<const UniqueVariant> a_args) const -> bool
	{
		if (GetParamCount() != a_args.size()) {
			return false;
		}

		return ForEachParam(
				   [a_args](
					   std::uint32_t a_index,
					   [[maybe_unused]]
					   const BSFixedString& a_paramName,
					   const TypeInfo& paramTypeInfo) noexcept -> BSContainer::ForEachResult {
					   const auto& arg = a_args[a_index];
					   if (!arg) {
						   return paramTypeInfo.IsNone() ? BSContainer::ForEachResult::Continue :
														   BSContainer::ForEachResult::Stop;
					   }

					   if (!arg->IsVariant()) {
						   return arg->GetTypeInfo() == paramTypeInfo ? BSContainer::ForEachResult::Continue :
																		BSContainer::ForEachResult::Stop;
					   }

					   const auto* variant = arg->GetVariant();
					   if (!variant) {
						   return paramTypeInfo.IsVariant() ? BSContainer::ForEachResult::Continue :
															  BSContainer::ForEachResult::Stop;
					   }

					   return variant->GetTypeInfo() == paramTypeInfo ? BSContainer::ForEachResult::Continue :
																		BSContainer::ForEachResult::Stop;
				   }) == BSContainer::ForEachResult::Continue;
	}

	auto IFunction::GetParamNames() const -> BSTArray<BSFixedString>
	{
		auto result = BSTArray<BSFixedString>();
		result.reserve(GetParamCount());

		ForEachParam(
			[&result](
				[[maybe_unused]] std::uint32_t a_index,
				const BSFixedString& paramName,
				[[maybe_unused]]
				const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
				result.push_back(paramName);
				return BSContainer::ForEachResult::Continue;
			});

		return result;
	}

	auto IFunction::GetParamTypes() const -> BSTArray<TypeInfo>
	{
		auto result = BSTArray<TypeInfo>();
		result.reserve(GetParamCount());

		ForEachParam(
			[&result](
				[[maybe_unused]] std::uint32_t a_index,
				[[maybe_unused]]
				const BSFixedString& paramName,
				const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
				result.push_back(paramTypeInfo);
				return BSContainer::ForEachResult::Continue;
			});

		return result;
	}

	auto IFunction::GetParams() const -> BSTArray<BSTPair<BSFixedString, TypeInfo>>
	{
		auto result = BSTArray<BSTPair<BSFixedString, TypeInfo>>();
		result.reserve(GetParamCount());

		ForEachParam(
			[&result](
				[[maybe_unused]]
				std::uint32_t a_index,
				const BSFixedString& paramName,
				const TypeInfo& paramTypeInfo) -> BSContainer::ForEachResult {
				result.emplace_back(paramName, paramTypeInfo);
				return BSContainer::ForEachResult::Continue;
			});

		return result;
	}

	auto IFunction::ForEachParam(
		const REX::NotNull<std::move_only_function<
			BSContainer::ForEachResult(std::uint32_t, const BSFixedString&, const TypeInfo&) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		const auto paramCount = GetParamCount();

		for (auto i = static_cast<std::uint32_t>(0); i < paramCount; i++) {
			auto paramName = BSFixedString();
			auto paramTypeInfo = TypeInfo();

			GetParam(i, paramName, paramTypeInfo);

			if (std::invoke(a_predicate.get(), i, paramName, paramTypeInfo) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
