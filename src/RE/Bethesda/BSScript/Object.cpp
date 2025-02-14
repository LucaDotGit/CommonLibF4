#include "RE/Bethesda/BSScript/Object.hpp"
#include "RE/Bethesda/BSScript/Internal/VirtualMachine.hpp"

namespace RE::BSScript
{
	Object::~Object()
	{
		if (IsConstructed()) {
			const auto size = type ? type->GetVariableCount() : 0;
			for (auto i = 0ui32; i < size; ++i) {
				variables[i].reset();
			}

			constructed = false;
			initialized = false;
		}

		auto lock = reinterpret_cast<std::uintptr_t>(lockStructure) & ~static_cast<std::uintptr_t>(1);
		if (lock) {
			stl::atomic_ref l{ lock };
			--l;
		}
	}
	ObjectTypeInfo* Object::GetTypeInfo()
	{
		return type.get();
	}

	const ObjectTypeInfo* Object::GetTypeInfo() const
	{
		return type.get();
	}

	void* Object::Resolve(VMTypeID a_typeID) const
	{
		auto vm = Internal::VirtualMachine::GetSingleton();
		if (!vm) {
			return nullptr;
		}
		IObjectHandlePolicy& policy = vm->GetObjectHandlePolicy();
		auto myHandle = GetHandle();
		if (policy.HandleIsType(a_typeID, myHandle) && policy.IsHandleObjectAvailable(myHandle)) {
			return policy.GetObjectForHandle(a_typeID, myHandle);
		}
		else {
			return nullptr;
		}
	}
	Variable* Object::GetProperty(const BSFixedString& a_name)
	{
		return const_cast<Variable*>(
			const_cast<const Object*>(this)->GetProperty(a_name));
	}

	const Variable* Object::GetProperty(const BSFixedString& a_name) const
	{
		constexpr auto INVALID = static_cast<std::uint32_t>(-1);

		auto index = INVALID;
		for (auto cls = type.get(); cls && index == INVALID; cls = cls->GetParent()) {
			index = cls->GetPropertyIndex(a_name);
		}

		return index != INVALID ? std::addressof(variables[index]) : nullptr;
	}

}