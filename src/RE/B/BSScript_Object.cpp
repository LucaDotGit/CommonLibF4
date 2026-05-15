#include "RE/B/BSScript_Object.hpp"

#include "RE/B/BSScript_IObjectHandlePolicy.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::BSScript
{
	Object::Object() noexcept
		: handle(GameScript::HandlePolicy::EMPTY_HANDLE)
	{
	}

	Object::~Object() noexcept
	{
		if (!IsConstructed()) {
			return;
		}

		const auto variableSize = type ? type->GetNumVariables() : 0;
		for (auto i = 0ui32; i < variableSize; i++) {
			variables[i].reset();
		}

		constructed = false;
		initialized = false;
	}

	bool Object::Equals(const Object& a_rhs) const noexcept
	{
		return RefEquals(a_rhs);
	}

	bool Object::RefEquals(const Object& a_rhs) const noexcept
	{
		return this == std::addressof(a_rhs);
	}

	bool Object::DeepEquals(const Object& a_rhs) const noexcept
	{
		return RefEquals(a_rhs);
	}

	std::strong_ordering Object::Compare(const Object& a_rhs) const noexcept
	{
		return RefCompare(a_rhs);
	}

	std::strong_ordering Object::RefCompare(const Object& a_rhs) const noexcept
	{
		return this <=> std::addressof(a_rhs);
	}

	std::strong_ordering Object::DeepCompare(const Object& a_rhs) const noexcept
	{
		return RefCompare(a_rhs);
	}

	BSTSmartPointer<ObjectTypeInfo> Object::GetTypeInfo() const noexcept
	{
		return type;
	}

	auto Object::GetTypeInfoName() const noexcept
		-> std::optional<BSFixedString>
	{
		if (!type) {
			return std::nullopt;
		}

		return type->GetName();
	}

	BSFixedString Object::GetCurrentState() const noexcept
	{
		return currentState;
	}

	ObjectHandle Object::GetHandle() const noexcept
	{
		const auto atomicHandle = REX::AtomicRef(handle);
		return atomicHandle.load(std::memory_order_acquire);
	}

	bool Object::Is(const BSTSmartPointer<BSScript::IVirtualMachine>& a_vm, FormType a_typeID) const
	{
		if (!a_vm) {
			return false;
		}

		const auto& handlePolicy = a_vm->GetObjectHandlePolicy();
		return handlePolicy.HandleIsType(a_typeID, handle);
	}

	void* Object::As(const BSTSmartPointer<BSScript::IVirtualMachine>& a_vm, FormType a_typeID) const
	{
		if (!a_vm) {
			return nullptr;
		}

		const auto& handlePolicy = a_vm->GetObjectHandlePolicy();
		return handlePolicy.GetObjectForHandle(a_typeID, handle);
	}

	auto Object::GetVariables() noexcept
		-> std::span<Variable>
	{
		if (!type) {
			return {};
		}

		return { static_cast<Variable*>(variables), type->GetNumVariables() };
	}

	auto Object::GetVariables() const noexcept
		-> std::span<const Variable>
	{
		if (!type) {
			return {};
		}

		return { static_cast<const Variable*>(variables), type->GetNumVariables() };
	}

	Variable* Object::GetVariable(const BSFixedString& a_name)
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetVariableIndex(a_name);
		if (!varIndex) {
			return nullptr;
		}

		return std::addressof(variables[*varIndex]);
	}

	const Variable* Object::GetVariable(const BSFixedString& a_name) const
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetVariableIndex(a_name);
		if (!varIndex) {
			return nullptr;
		}

		return std::addressof(variables[*varIndex]);
	}

	bool Object::SetVariable(const BSFixedString& a_name, const Variable& a_value)
	{
		auto* variable = GetVariable(a_name);
		if (!variable) {
			return false;
		}

		*variable = a_value;
		return true;
	}

	Variable* Object::GetProperty(const BSFixedString& a_name)
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetPropertyIndex(a_name);
		if (!varIndex) {
			return nullptr;
		}

		return std::addressof(variables[*varIndex]);
	}

	const Variable* Object::GetProperty(const BSFixedString& a_name) const
	{
		if (!type) {
			return nullptr;
		}

		const auto varIndex = type->GetPropertyIndex(a_name);
		if (!varIndex) {
			return nullptr;
		}

		return std::addressof(variables[*varIndex]);
	}

	bool Object::SetProperty(const BSFixedString& a_name, const Variable& a_value)
	{
		auto* variable = GetProperty(a_name);
		if (!variable) {
			return false;
		}

		*variable = a_value;
		return true;
	}

	BSTSmartPointer<Object> Object::Clone([[maybe_unused]] IVirtualMachine& a_vm) noexcept
	{
		return BSTSmartPointer(this);
	}

	BSTSmartPointer<Object> Object::DeepClone([[maybe_unused]] IVirtualMachine& a_vm) noexcept
	{
		return BSTSmartPointer(this);
	}

	std::string Object::ToString() const
	{
		if (!type) {
			return std::string(BSScript::NONE_STRING);
		}

		return REX::Format("[{} ({:X})]"sv,
			type->GetName(), GetHandle());
	}

	bool Object::try_lock() const noexcept
	{
		auto atomicLock = REX::AtomicRef(reinterpret_cast<volatile std::uintptr_t&>(lockStructure));

		const auto previousValue = atomicLock.fetch_or(static_cast<std::uintptr_t>(1), std::memory_order_acq_rel);
		return (previousValue & static_cast<std::uintptr_t>(1)) == 0;
	}

	void Object::lock() const noexcept
	{
		auto atomicLock = REX::AtomicRef(reinterpret_cast<volatile std::uintptr_t&>(lockStructure));
		auto spinCount = 0ui32;

		while (true) {
			auto expectedValue = atomicLock.load(std::memory_order_acquire);
			if ((expectedValue & static_cast<std::uintptr_t>(1)) != 0 ||
				!atomicLock.compare_exchange_weak(expectedValue, expectedValue | static_cast<std::uintptr_t>(1),
					std::memory_order_acq_rel, std::memory_order_relaxed)) {
				REX::W32::Sleep(++spinCount < RE::Impl::SPIN_LOCK_YIELD_COUNT ? RE::Impl::SPIN_LOCK_YIELD_DURATION_MS : RE::Impl::SPIN_LOCK_SLEEP_DURATION_MS);
				continue;
			}

			break;
		}
	}

	void Object::unlock() const noexcept
	{
		auto atomicLock = REX::AtomicRef(reinterpret_cast<volatile std::uintptr_t&>(lockStructure));
		atomicLock.fetch_and(~static_cast<std::uintptr_t>(1), std::memory_order_acq_rel);
	}

	void Object::IncRef() noexcept
	{
		try {
			using FuncType = decltype(&Object::IncRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScript::Object::IncRef };
			std::invoke(FUNC, this);
		}
		catch (...) {
			REX::Fail("Failed to increment script object ref count."sv);
		}
	}

	std::uint32_t Object::DecRef() noexcept
	{
		try {
			using FuncType = decltype(&Object::DecRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScript::Object::DecRef };
			return std::invoke(FUNC, this);
		}
		catch (...) {
			REX::Fail("Failed to decrement script object ref count."sv);
		}
	}
}

namespace RE
{
	template class BSAutoLockDefaultPolicy<BSScript::Object>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSScript::Object>>);

	template class BSAutoLock<BSScript::Object, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoLock<BSScript::Object, BSAutoLockDefaultPolicy>) == 0x08);
}
