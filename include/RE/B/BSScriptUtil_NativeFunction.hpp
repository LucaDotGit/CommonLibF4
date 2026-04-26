#pragma once

#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScriptUtil_LatentResult.hpp"
#include "RE/B/BSScript_NF_util_NativeFunctionBase.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Stack.hpp"
#include "RE/B/BSScript_StackFrame.hpp"
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
	template <bool IsLong, class VMType, class StackType, class SelfType, class... Args, class FuncT, std::size_t... Indexes>
	[[nodiscard]] decltype(auto) DispatchHelper(
		Variable& a_self,
		Internal::VirtualMachine& a_vm,
		StackID a_stackID,
		const StackFrame& a_stackFrame,
		const Stack& a_stack,
		const REX::NotNull<std::function<FuncT>>& a_callback,
		[[maybe_unused]] std::index_sequence<Indexes...> a_indexes)
	{
		const auto getSelf = [&a_self]() -> SelfType {
			using self_type = std::remove_cvref_t<SelfType>;

			if constexpr (Impl::static_tag<SelfType>) {
				return StaticTag();
			}
			else if constexpr (Impl::form_ptr<self_type>) {
				auto* form = Impl::UnpackVariable<self_type>(a_self);
				REX::Assert(static_cast<bool>(form));
				return form;
			}
			else if constexpr (Impl::inventory_object<self_type>) {
				auto object = Impl::UnpackVariable<self_type>(a_self);
				REX::Assert(static_cast<bool>(object));
				return object;
			}
			else if constexpr (Impl::vm_object_ptr<self_type>) {
				auto object = a_self.GetObject();
				REX::Assert(static_cast<bool>(object));
				return object;
			}
			else if constexpr (Impl::vm_object_wrapper<self_type>) {
				auto object = a_self.GetObject();
				REX::Assert(static_cast<bool>(object));
				return self_type(object);
			}
			else {
				static_assert(false, "The self type is invalid.");
			}
		};

		const auto getArgs = [&a_stackFrame, &a_stack]<class T>([[maybe_unused]] std::in_place_type_t<T> a_inPlaceType, std::size_t a_index) {
			if (a_stackFrame.size <= a_index) [[unlikely]] {
				REX::Assert(false);
				return T();
			}

			const auto stackPage = a_stack.GetPageForFrame(std::addressof(a_stackFrame));
			return Impl::UnpackVariable<T>(
				a_stack.GetStackFrameVariable(
					std::addressof(a_stackFrame),
					static_cast<std::uint32_t>(a_index),
					stackPage));
		};

		if constexpr (IsLong) {
			auto* scriptVM = DynamicCast<VMType*>(std::addressof(a_vm));
			if (!scriptVM) [[unlikely]] {
				REX::Fail("Failed to cast the script VM to the expected type."sv);
			}

			if constexpr (std::same_as<StackType, StackID>) {
				return (*a_callback)(
					*scriptVM,
					a_stackID,
					std::invoke(getSelf),
					std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
			}
			else if constexpr (std::same_as<StackType, Stack>) {
				return (*a_callback)(
					*scriptVM,
					a_stack,
					std::invoke(getSelf),
					std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
			}
			else if constexpr (std::same_as<StackType, StackFrame>) {
				return (*a_callback)(
					*scriptVM,
					a_stackFrame,
					std::invoke(getSelf),
					std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
			}
			else {
				static_assert(false, "The stack type is invalid.");
			}
		}
		else {
			return (*a_callback)(
				std::invoke(getSelf),
				std::invoke(getArgs, std::in_place_type_t<Args>(), Indexes)...);
		}
	}
}

namespace RE::BSScript
{
	template <class FuncT, bool IsLong, class VMType, class StackType, class ResultType, class SelfType, class... Args>
	class NativeFunction final
		: public NF_util::NativeFunctionBase
	{
	private:
		using super = NF_util::NativeFunctionBase;

	public:
		static_assert(BSScript::ValidateSelf<SelfType>());
		static_assert(BSScript::ValidateReturn<ResultType>());
		static_assert(((BSScript::ValidateParameter<Args>(), ...), true));

		NativeFunction(std::string_view a_scriptName, std::string_view a_funcName, const FuncT& a_func)
			: super(a_scriptName, a_funcName, sizeof...(Args), Impl::static_tag<SelfType>, false),
			  _stub(a_func)
		{
			REX::Assert(super::descTable.GetParamCount() == sizeof...(Args));
			auto paramIndex = static_cast<Internal::VDescTable::size_type>(0);
			((super::descTable.SetNthParamType(paramIndex++, Impl::GetTypeInfo<Args>().value_or(nullptr))), ...);
			super::returnType = Impl::GetTypeInfo<ResultType>().value_or(nullptr);
		}

		~NativeFunction() noexcept override = default; // 00

		NativeFunction(const NativeFunction&) = delete;
		NativeFunction(NativeFunction&&) = delete;

		NativeFunction& operator=(const NativeFunction&) = delete;
		NativeFunction& operator=(NativeFunction&&) = delete;

		// override (NF_util::NativeFunctionBase)
		[[nodiscard]] bool HasStub() const noexcept override { return true; } // 15

		bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine& a_vm, StackID a_stackID, Variable& a_outResult, const StackFrame& a_stackFrame) const override // 16
		{
			const auto* stack = a_stackFrame.parentStack;
			if (!stack) [[unlikely]] {
				REX::Fail(R"(Failed to get parent stack for native function "{}" on script "{}".)"sv,
					this->name, this->scriptName);
			}

			const auto doInvoke = [this, &a_self, &a_vm, a_stackID, &a_stackFrame, stack]() -> decltype(auto) {
				return Impl::DispatchHelper<IsLong, VMType, StackType, SelfType, Args...>(
					a_self,
					a_vm,
					a_stackID,
					a_stackFrame,
					*stack,
					_stub,
					std::index_sequence_for<Args...>());
			};

			if constexpr (std::same_as<ResultType, void>) {
				std::invoke(doInvoke);
				a_outResult.SetNone();
				return true;
			}
			else {
				Impl::PackVariable(a_outResult, std::invoke(doInvoke));
				return true;
			}
		}

	private:
		REX::NotNull<std::function<FuncT>> _stub;
	};

	template <class FuncT, bool IsLong, class VMType, class StackType, class ResultType, class SelfType, class... Args>
	class NativeLatentFunction final
		: public NF_util::NativeFunctionBase
	{
	private:
		using super = NF_util::NativeFunctionBase;

	public:
		static_assert(BSScript::ValidateSelf<SelfType>());
		static_assert(BSScript::ValidateReturn<ResultType>());
		static_assert(((BSScript::ValidateParameter<Args>(), ...), true));

		NativeLatentFunction(std::string_view a_scriptName, std::string_view a_funcName, const FuncT& a_func)
			: super(a_scriptName, a_funcName, sizeof...(Args), Impl::static_tag<SelfType>, true),
			  _stub(a_func)
		{
			REX::Assert(super::descTable.GetParamCount() == sizeof...(Args));
			auto paramIndex = static_cast<Internal::VDescTable::size_type>(0);
			((super::descTable.SetNthParamType(paramIndex++, Impl::GetTypeInfo<Args>().value_or(nullptr))), ...);
			super::returnType = Impl::GetTypeInfo<ResultType>().value_or(nullptr);
		}

		~NativeLatentFunction() noexcept override = default; // 00

		NativeLatentFunction(const NativeLatentFunction&) = delete;
		NativeLatentFunction(NativeLatentFunction&&) = delete;

		NativeLatentFunction& operator=(const NativeLatentFunction&) = delete;
		NativeLatentFunction& operator=(NativeLatentFunction&&) = delete;

		// override (NF_util::NativeFunctionBase)
		[[nodiscard]] bool HasStub() const noexcept override { return true; } // 15

		bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine& a_vm, StackID a_stackID, Variable& a_outResult, const StackFrame& a_stackFrame) const override // 16
		{
			const auto* stack = a_stackFrame.parentStack;
			if (!stack) [[unlikely]] {
				REX::Fail(R"(Failed to get parent stack for native function "{}" on script "{}".)"sv,
					this->name, this->scriptName);
			}

			const auto doInvoke = [this, &a_self, &a_vm, a_stackID, &a_stackFrame, stack]() -> decltype(auto) {
				return Impl::DispatchHelper<IsLong, VMType, StackType, SelfType, Args...>(
					a_self,
					a_vm,
					a_stackID,
					a_stackFrame,
					*stack,
					_stub,
					std::index_sequence_for<Args...>());
			};

			a_outResult.SetBool(static_cast<bool>(std::invoke(doInvoke)));
			return true;
		}

	private:
		REX::NotNull<std::function<FuncT>> _stub;
	};

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(SelfType, Args...))
		-> NativeFunction<
			ResultType(SelfType, Args...),
			false,
			std::monostate,
			std::monostate,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(IVirtualMachine&, StackID, SelfType, Args...))
		-> NativeFunction<
			ResultType(IVirtualMachine&, StackID, SelfType, Args...),
			true,
			IVirtualMachine,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(Internal::VirtualMachine&, StackID, SelfType, Args...))
		-> NativeFunction<
			ResultType(Internal::VirtualMachine&, StackID, SelfType, Args...),
			true,
			Internal::VirtualMachine,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(IVirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeFunction<
			ResultType(IVirtualMachine&, const Stack&, SelfType, Args...),
			true,
			IVirtualMachine,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(Internal::VirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeFunction<
			ResultType(Internal::VirtualMachine&, const Stack&, SelfType, Args...),
			true,
			Internal::VirtualMachine,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(IVirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeFunction<
			ResultType(IVirtualMachine&, const StackFrame&, SelfType, Args...),
			true,
			IVirtualMachine,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeFunction(std::string_view, std::string_view, ResultType (*)(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeFunction<
			ResultType(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...),
			true,
			Internal::VirtualMachine,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(SelfType, Args...),
			false,
			std::monostate,
			std::monostate,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(IVirtualMachine&, StackID, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(IVirtualMachine&, StackID, SelfType, Args...),
			true,
			IVirtualMachine,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(Internal::VirtualMachine&, StackID, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(Internal::VirtualMachine&, StackID, SelfType, Args...),
			true,
			Internal::VirtualMachine,
			StackID,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(IVirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(IVirtualMachine&, const Stack&, SelfType, Args...),
			true,
			IVirtualMachine,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(Internal::VirtualMachine&, const Stack&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(Internal::VirtualMachine&, const Stack&, SelfType, Args...),
			true,
			Internal::VirtualMachine,
			Stack,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(IVirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(IVirtualMachine&, const StackFrame&, SelfType, Args...),
			true,
			IVirtualMachine,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;

	template <class ResultType, class SelfType, class... Args>
	NativeLatentFunction(std::string_view, std::string_view, LatentResult<ResultType> (*)(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...))
		-> NativeLatentFunction<
			LatentResult<ResultType>(Internal::VirtualMachine&, const StackFrame&, SelfType, Args...),
			true,
			Internal::VirtualMachine,
			StackFrame,
			ResultType,
			SelfType,
			Args...>;
}
