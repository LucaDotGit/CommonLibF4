#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	const hkClass* hkReferencedObject::GetClassType() const
	{
		return nullptr;
	}

	void hkReferencedObject::DeleteThisReferencedObject() const
	{
		delete this;
	}

	std::int32_t hkReferencedObject::GetAllocatedSize() const noexcept
	{
		return memSize & MEM_SIZE_MASK;
	}

	std::int32_t hkReferencedObject::GetReferenceCount() const noexcept
	{
		return refCount;
	}

	void hkReferencedObject::AddReference()
	{
		using FuncType = decltype(&hkReferencedObject::AddReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkReferencedObject::AddReference };
		std::invoke(FUNC, this);
	}

	void hkReferencedObject::RemoveReference()
	{
		using FuncType = decltype(&hkReferencedObject::RemoveReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkReferencedObject::RemoveReference };
		std::invoke(FUNC, this);
	}
}
