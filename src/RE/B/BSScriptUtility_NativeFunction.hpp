#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScriptUtility_LatentResult.hpp"
#include "RE/B/BSScript_NF_util_NativeFunctionBase.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Stack.hpp"
#include "RE/B/BSScript_StackFrame.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::BSScript::Internal
{
	class VirtualMachine;
}

namespace RE::BSScript::Impl
{
	template <class FuncType, class StackType, class SelfType, class... Args, std::size_t... Indexes>
	[[nodiscard]]
	auto DispatchHelper(
		Variable& a_self,
		Internal::VirtualMachine& a_vm,
		StackID a_stackID,
		const StackFrame& a_stackFrame,
		const Stack& a_stack,
		const REX::NotNull<std::move_only_function<FuncType>>& a_callback,
		[[maybe_unused]] std::index_sequence<Indexes...> a_indexes) -> decltype(auto)
	{
		const auto getSelf = [&a_vm, &a_self]() -> SelfType {
			using self_type = std::remove_cvref_t<SelfType>;

			if constexpr (Impl::static_tag<SelfType>) {
				return StaticTag();
			}
			else if constexpr (Impl::form_pointer<self_type>) {
				auto form = Impl::UnpackVariable<self_type>(a_vm, a_self);
				REX::Ensure(form.has_value() && static_cast<bool>(form.value()));
				return std::move(form).value();
			}
			else if constexpr (Impl::inventory_object<self_type> ||
							   Impl::vm_object_pointer<self_type> ||
							   Impl::vm_object_wrapper<self_type>) {
				auto object = Impl::UnpackVariable<self_type>(a_vm, a_self);
				REX::Ensure(object.has_value() && static_cast<bool>(object.value()));
				return std::move(object).value();
			}
			else {
				static_assert(false, "The self type is invalid.");
			}
		};

		const auto getArgs = [&a_vm, &a_stackFrame, &a_stack]<class T>(
								 [[maybe_unused]]
								 std::in_place_type_t<T> a_inPlaceType,
								 std::size_t a_index) -> T {
			const auto stackFrameSize = a_stackFrame.size;
			REX::Ensure(a_index < stackFrameSize);

			const auto stackPage = a_stack.GetPageForFrame(std::addressof(a_stackFrame));
			const auto& stackFrameVariable = a_stack.GetStackFrameVariable(
				std::addressof(a_stackFrame),
				static_cast<std::uint32_t>(a_index),
				stackPage);

			auto variable = Impl::UnpackVariable<T>(a_vm, stackFrameVariable);
			REX::Ensure(variable.has_value());

			return std::move(variable).value();
		};

		if constexpr (!std::same_as<StackType, std::monostate>) {
			if constexpr (std::same_as<StackType, StackID>) {
				return std::invoke(
					a_callback.get(),
					a_vm,
					a_stackID,
					std::invoke(getSelf),
					std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
			}
			else if constexpr (std::same_as<StackType, Stack>) {
				return std::invoke(
					a_callback.get(),
					a_vm,
					a_stack,
					std::invoke(getSelf),
					std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
			}
			else if constexpr (std::same_as<StackType, StackFrame>) {
				return std::invoke(
					a_callback.get(),
					a_vm,
					a_stackFrame,
					std::invoke(getSelf),
					std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
			}
			else {
				static_assert(false, "The stack type is invalid.");
			}
		}
		else {
			return std::invoke(
				a_callback.get(),
				std::invoke(getSelf),
				std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
		}
	}
}

namespace RE::BSScript
{
	template <class FuncType, class StackType, class ResultType, class SelfType, class... Args>
	class NativeFunction final : public NF_util::NativeFunctionBase
	{
	private:
		using super = NF_util::NativeFunctionBase;

	public:
		using value_type = FuncType;
		using result_type = ResultType;
		using self_type = SelfType;

		static_assert(BSScript::ValidateSelf<SelfType>());
		static_assert(BSScript::ValidateReturn<ResultType>());
		static_assert(((BSScript::ValidateParameter<Args>(), ...), true));

		NativeFunction(
			IVirtualMachine& a_vm,
			BSFixedString a_scriptName,
			BSFixedString a_funcName,
			REX::NotNull<std::move_only_function<FuncType>> a_func) :
			super(std::move(a_scriptName), std::move(a_funcName), sizeof...(Args), Impl::static_tag<SelfType>, false),
			_func(std::move(a_func))
		{
			auto paramIndex = static_cast<decltype(super::descTable)::size_type>(0);
			(REX::Assert(
				 super::descTable.SetNthParamType(
					 paramIndex++,
					 Impl::GetTypeInfo<Args>(a_vm).value_or(RE::BSScript::NONE_TYPE_INFO))),
			 ...);
			super::returnType = Impl::GetTypeInfo<ResultType>(a_vm).value_or(RE::BSScript::NONE_TYPE_INFO);
		}

		~NativeFunction() noexcept override = default; // 0x00

		NativeFunction(const NativeFunction&) = delete;
		NativeFunction(NativeFunction&&) = delete;

		auto operator=(const NativeFunction&) -> NativeFunction& = delete;
		auto operator=(NativeFunction&&) -> NativeFunction& = delete;

		// override (NF_util::NativeFunctionBase)
		[[nodiscard]]
		auto HasStub() const noexcept -> bool override // 0x15
		{
			return true;
		}

		auto MarshallAndDispatch(
			Variable& a_self,
			Internal::VirtualMachine& a_vm,
			StackID a_stackID,
			Variable& a_outResult,
			const StackFrame& a_stackFrame) const -> bool override // 0x16
		{
			const auto* stack = a_stackFrame.parentStack;
			if (!stack) [[unlikely]] {
				REX::Fail(
					R"(Failed to get parent stack for native function "{}" on script "{}".)"sv,
					this->name,
					this->scriptName);
			}

			const auto doInvoke = [this, &a_self, &a_vm, a_stackID, &a_stackFrame, stack]() -> decltype(auto) {
				return Impl::DispatchHelper<FuncType, StackType, SelfType, Args...>(
					a_self,
					a_vm,
					a_stackID,
					a_stackFrame,
					*stack,
					_func,
					std::index_sequence_for<Args...>());
			};

			if constexpr (std::same_as<ResultType, void>) {
				std::invoke(doInvoke);
				a_outResult.SetNone();
				return true;
			}
			else {
				return Impl::PackVariable(a_vm, a_outResult, std::invoke(doInvoke));
			}
		}

	private:
		REX::NotNull<std::move_only_function<FuncType>> _func;
	};

	template <class FuncType, class StackType, class ResultType, class SelfType, class... Args>
	class NativeLatentFunction final : public NF_util::NativeFunctionBase
	{
	private:
		using super = NF_util::NativeFunctionBase;

	public:
		using value_type = FuncType;
		using result_type = ResultType;
		using self_type = SelfType;

		static_assert(BSScript::ValidateSelf<SelfType>());
		static_assert(BSScript::ValidateReturn<ResultType>());
		static_assert(((BSScript::ValidateParameter<Args>(), ...), true));

		NativeLatentFunction(
			IVirtualMachine& a_vm,
			BSFixedString a_scriptName,
			BSFixedString a_funcName,
			REX::NotNull<std::move_only_function<FuncType>> a_func) :
			super(std::move(a_scriptName), std::move(a_funcName), sizeof...(Args), Impl::static_tag<SelfType>, true),
			_func(std::move(a_func))
		{
			auto paramIndex = static_cast<decltype(super::descTable)::size_type>(0);
			(REX::Assert(
				 super::descTable.SetNthParamType(
					 paramIndex++,
					 Impl::GetTypeInfo<Args>(a_vm).value_or(RE::BSScript::NONE_TYPE_INFO))),
			 ...);
			super::returnType = Impl::GetTypeInfo<ResultType>(a_vm).value_or(RE::BSScript::NONE_TYPE_INFO);
		}

		~NativeLatentFunction() noexcept override = default; // 0x00

		NativeLatentFunction(const NativeLatentFunction&) = delete;
		NativeLatentFunction(NativeLatentFunction&&) = delete;

		auto operator=(const NativeLatentFunction&) -> NativeLatentFunction& = delete;
		auto operator=(NativeLatentFunction&&) -> NativeLatentFunction& = delete;

		// override (NF_util::NativeFunctionBase)
		[[nodiscard]]
		auto HasStub() const noexcept -> bool override // 0x15
		{
			return true;
		}

		auto MarshallAndDispatch(
			Variable& a_self,
			Internal::VirtualMachine& a_vm,
			StackID a_stackID,
			Variable& a_outResult,
			const StackFrame& a_stackFrame) const -> bool override // 0x16
		{
			const auto* stack = a_stackFrame.parentStack;
			if (!stack) [[unlikely]] {
				REX::Fail(
					R"(Failed to get parent stack for native function "{}" on script "{}".)"sv,
					this->name,
					this->scriptName);
			}

			const auto doInvoke = [this, &a_self, &a_vm, a_stackID, &a_stackFrame, stack]() -> decltype(auto) {
				return Impl::DispatchHelper<FuncType, StackType, SelfType, Args...>(
					a_self,
					a_vm,
					a_stackID,
					a_stackFrame,
					*stack,
					_func,
					std::index_sequence_for<Args...>());
			};

			a_outResult.SetBool(static_cast<bool>(std::invoke(doInvoke)));
			return true;
		}

	private:
		REX::NotNull<std::move_only_function<FuncType>> _func;
	};

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(IVirtualMachine&, BSFixedString, BSFixedString, ResultType (*)(SelfType, Args...))
		-> NativeFunction<ResultType(SelfType, Args...) const, std::monostate, ResultType, SelfType, Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		ResultType (*)(IVirtualMachine&, StackID, SelfType, Args...))
		-> NativeFunction<
			ResultType(IVirtualMachine&, StackID, SelfType, Args...) const,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		ResultType (*)(Internal::VirtualMachine&, StackID, SelfType, Args...))
		-> NativeFunction<
			ResultType(Internal::VirtualMachine&, StackID, SelfType, Args...) const,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		ResultType (*)(IVirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeFunction<
			ResultType(IVirtualMachine&, const Stack&, SelfType, Args...) const,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		ResultType (*)(Internal::VirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeFunction<
			ResultType(Internal::VirtualMachine&, const Stack&, SelfType, Args...) const,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		ResultType (*)(IVirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeFunction<
			ResultType(IVirtualMachine&, const StackFrame&, SelfType, Args...) const,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		ResultType (*)(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeFunction<
			ResultType(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...) const,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(SelfType, Args...) const,
			std::monostate,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(IVirtualMachine&, StackID, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(IVirtualMachine&, StackID, SelfType, Args...) const,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(Internal::VirtualMachine&, StackID, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(Internal::VirtualMachine&, StackID, SelfType, Args...) const,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(IVirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(IVirtualMachine&, const Stack&, SelfType, Args...) const,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(Internal::VirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(Internal::VirtualMachine&, const Stack&, SelfType, Args...) const,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(IVirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(IVirtualMachine&, const StackFrame&, SelfType, Args...) const,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(
		IVirtualMachine&,
		BSFixedString,
		BSFixedString,
		LatentResult<ResultType> (*)(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...) const,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;
}
