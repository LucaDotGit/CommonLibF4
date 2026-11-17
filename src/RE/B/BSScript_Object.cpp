#include "RE/B/BSScript_Object.hpp"

#include "RE/B/BSScript_IObjectHandlePolicy.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSSpinLockPolicy.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::BSScript
{
	Object::Object() noexcept :
		handle(GameScript::HandlePolicy::EMPTY_HANDLE)
	{
	}

	Object::~Object() noexcept
	{
		if (!IsConstructed()) {
			return;
		}

		const auto variableSize = type ? type->GetVariableCount() : 0;
		for (auto i = static_cast<std::uint32_t>(0); i < variableSize; i++) {
			variables[i].reset();
		}

		constructed = false;
		initialized = false;
	}

	auto Object::Equals(const Object& a_rhs) const noexcept -> bool
	{
		return RefEquals(a_rhs);
	}

	auto Object::RefEquals(const Object& a_rhs) const noexcept -> bool
	{
		return this == std::addressof(a_rhs);
	}

	auto Object::DeepEquals(const Object& a_rhs) const noexcept -> bool
	{
		return RefEquals(a_rhs);
	}

	auto Object::Compare(const Object& a_rhs) const noexcept -> std::strong_ordering
	{
		return RefCompare(a_rhs);
	}

	auto Object::RefCompare(const Object& a_rhs) const noexcept -> std::strong_ordering
	{
		return this <=> std::addressof(a_rhs);
	}

	auto Object::DeepCompare(const Object& a_rhs) const noexcept -> std::strong_ordering
	{
		return RefCompare(a_rhs);
	}

	auto Object::GetTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>
	{
		return type;
	}

	auto Object::GetTypeInfoName() const noexcept -> std::optional<BSFixedString>
	{
		if (!type) {
			return std::nullopt;
		}

		return type->GetName();
	}

	auto Object::GetCurrentState() const noexcept -> BSFixedString
	{
		return currentState;
	}

	auto Object::GetHandle() const noexcept -> ObjectHandle
	{
		const auto atomicHandle = REX::AtomicRef(handle);
		return atomicHandle.load(std::memory_order_acquire);
	}

	auto Object::Is(const BSScript::IVirtualMachine& a_vm, FormType a_typeID) const -> bool
	{
		const auto& handlePolicy = a_vm.GetObjectHandlePolicy();
		return handlePolicy.HandleIsType(a_typeID, handle);
	}

	auto Object::As(const BSScript::IVirtualMachine& a_vm, FormType a_typeID) const -> void*
	{
		const auto& handlePolicy = a_vm.GetObjectHandlePolicy();
		return handlePolicy.GetObjectForHandle(a_typeID, handle);
	}

	auto Object::GetVariables() noexcept -> std::span<Variable>
	{
		if (!type) {
			return {};
		}

		return {static_cast<Variable*>(variables), type->GetVariableCount()};
	}

	auto Object::GetVariables() const noexcept -> std::span<const Variable>
	{
		if (!type) {
			return {};
		}

		return {static_cast<const Variable*>(variables), type->GetVariableCount()};
	}

	auto Object::GetVariable(const BSFixedString& a_name) noexcept -> Variable*
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetVariableIndexByName(a_name);
		if (!varIndex.has_value()) {
			return nullptr;
		}

		return std::addressof(variables[varIndex.value()]);
	}

	auto Object::GetVariable(const BSFixedString& a_name) const noexcept -> const Variable*
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetVariableIndexByName(a_name);
		if (!varIndex.has_value()) {
			return nullptr;
		}

		return std::addressof(variables[varIndex.value()]);
	}

	auto Object::SetVariable(const BSFixedString& a_name, const Variable& a_value) noexcept -> bool
	{
		auto* variable = GetVariable(a_name);
		if (!variable) {
			return false;
		}

		*variable = a_value;
		return true;
	}

	auto Object::GetProperty(const BSFixedString& a_name) noexcept -> Variable*
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetPropertyIndexByName(a_name);
		if (!varIndex.has_value()) {
			return nullptr;
		}

		return std::addressof(variables[varIndex.value()]);
	}

	auto Object::GetProperty(const BSFixedString& a_name) const noexcept -> const Variable*
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetPropertyIndexByName(a_name);
		if (!varIndex.has_value()) {
			return nullptr;
		}

		return std::addressof(variables[varIndex.value()]);
	}

	auto Object::SetProperty(const BSFixedString& a_name, const Variable& a_value) noexcept -> bool
	{
		auto* variable = GetProperty(a_name);
		if (!variable) {
			return false;
		}

		*variable = a_value;
		return true;
	}

	auto Object::Clone([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> BSTSmartPointer<Object>
	{
		return BSTSmartPointer(this);
	}

	auto Object::DeepClone([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> BSTSmartPointer<Object>
	{
		return BSTSmartPointer(this);
	}

	auto Object::ToString() const -> std::string
	{
		if (!type) {
			return std::string(BSScript::NONE_STRING);
		}

		return REX::Format("[{} ({:X})]"sv, type->GetName(), GetHandle());
	}

	auto Object::try_lock() const noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(lockStructure);

		const auto previousValue = atomicLock.fetch_or(static_cast<std::uintptr_t>(1), std::memory_order_acq_rel);
		return (previousValue & static_cast<std::uintptr_t>(1)) == 0;
	}

	void Object::lock() const noexcept
	{
		const auto atomicLock = REX::AtomicRef(lockStructure);
		auto spinCount = static_cast<std::uint32_t>(0);

		while (true) {
			auto expectedValue = atomicLock.load(std::memory_order_acquire);
			if ((expectedValue & static_cast<std::uintptr_t>(1)) != 0 ||
				!atomicLock.compare_exchange_weak(
					expectedValue,
					expectedValue | static_cast<std::uintptr_t>(1),
					std::memory_order_acq_rel,
					std::memory_order_relaxed)) {
				if (++spinCount < RE::Impl::SPIN_LOCK_YIELD_COUNT) {
					std::this_thread::yield();
					continue;
				}

				std::this_thread::sleep_for(RE::Impl::SPIN_LOCK_SLEEP_DURATION);
				continue;
			}

			break;
		}
	}

	void Object::unlock() const noexcept
	{
		const auto atomicLock = REX::AtomicRef(lockStructure);
		atomicLock.fetch_and(~static_cast<std::uintptr_t>(1), std::memory_order_acq_rel);
	}

	void Object::IncRef() const noexcept
	{
		try {
			using FuncType = decltype(&Object::IncRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSScript::Object::IncRef);
			std::invoke(FUNC, this);
		}
		catch (...) {
			REX::Fail("Failed to increment ref count."sv);
		}
	}

	auto Object::DecRef() const noexcept -> std::uint32_t
	{
		try {
			using FuncType = decltype(&Object::DecRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSScript::Object::DecRef);
			return std::invoke(FUNC, this);
		}
		catch (...) {
			REX::Fail("Failed to decrement ref count."sv);
		}
	}
}
