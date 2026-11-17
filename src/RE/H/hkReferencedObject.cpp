#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	auto hkReferencedObject::GetClassType() const -> const hkClass*
	{
		return nullptr;
	}

	void hkReferencedObject::DeleteThisReferencedObject() const
	{
		delete this;
	}

	auto hkReferencedObject::GetAllocatedSize() const noexcept -> std::int32_t
	{
		return memSize & MEM_SIZE_MASK;
	}

	auto hkReferencedObject::GetReferenceCount() const noexcept -> std::int32_t
	{
		return refCount;
	}

	void hkReferencedObject::AddReference() const
	{
		using FuncType = decltype(&hkReferencedObject::AddReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::hkReferencedObject::AddReference);
		std::invoke(FUNC, this);
	}

	void hkReferencedObject::RemoveReference() const
	{
		using FuncType = decltype(&hkReferencedObject::RemoveReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::hkReferencedObject::RemoveReference);
		std::invoke(FUNC, this);
	}
}
