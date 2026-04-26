#include "RE/B/BSScript_Array.hpp"

#include "RE/B/BSScript_IVirtualMachine.hpp"

namespace RE::BSScript
{
	Array::Array() noexcept = default;

	Array::~Array() noexcept = default;

	bool Array::Equals(const Array& a_rhs) const noexcept
	{
		return RefEquals(a_rhs);
	}

	bool Array::RefEquals(const Array& a_rhs) const noexcept
	{
		return this == std::addressof(a_rhs);
	}

	bool Array::DeepEquals(const Array& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		if (elementType != a_rhs.elementType &&
			!elementType.IsVar() &&
			!a_rhs.elementType.IsVar()) {
			return false;
		}

		const auto leftElementLock = BSAutoLock(elementsLock);
		const auto rightElementLock = BSAutoLock(a_rhs.elementsLock);

		const auto leftElementSize = elements.size();
		const auto rightElementSize = a_rhs.elements.size();

		if (leftElementSize != rightElementSize) {
			return false;
		}

		for (auto i = 0ui32; i < leftElementSize; i++) {
			const auto& leftVar = elements[i];
			const auto& rightVar = a_rhs.elements[i];

			if (!leftVar.DeepEquals(rightVar)) {
				return false;
			}
		}

		return true;
	}

	std::strong_ordering Array::Compare(const Array& a_rhs) const noexcept
	{
		return RefCompare(a_rhs);
	}

	std::strong_ordering Array::RefCompare(const Array& a_rhs) const noexcept
	{
		return this <=> std::addressof(a_rhs);
	}

	std::partial_ordering Array::DeepCompare(const Array& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto typeComparison = elementType <=> a_rhs.elementType;
		if (typeComparison != std::strong_ordering::equal &&
			!elementType.IsVar() &&
			!a_rhs.elementType.IsVar()) {
			return typeComparison;
		}

		const auto leftElementLock = BSAutoLock(elementsLock);
		const auto rightElementLock = BSAutoLock(a_rhs.elementsLock);

		const auto leftElementSize = elements.size();
		const auto rightElementSize = a_rhs.elements.size();

		if (leftElementSize != rightElementSize) {
			return leftElementSize <=> rightElementSize;
		}

		for (auto i = 0ui32; i < leftElementSize; i++) {
			const auto& leftVar = elements[i];
			const auto& rightVar = a_rhs.elements[i];

			const auto varComparison = leftVar.DeepCompare(rightVar);
			if (varComparison != std::partial_ordering::equivalent) {
				return varComparison;
			}
		}

		return std::partial_ordering::equivalent;
	}

	TypeInfo Array::GetTypeInfo() const noexcept
	{
		auto result = elementType;
		result.SetIsArray(true);
		return result;
	}

	BSTSmartPointer<Array> Array::Clone(IVirtualMachine& a_vm) const
	{
		const auto elementLock = BSAutoLock(elementsLock);
		const auto elementSize = elements.size();

		auto result = BSTSmartPointer<Array>();
		if (!a_vm.CreateArray(elementType, elementSize, result) || !result) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto otherElementLock = BSAutoLock(result->elementsLock);

		for (auto i = 0ui32; i < elementSize; i++) {
			(*result)[i] = elements[i].Clone(a_vm);
		}

		return result;
	}

	BSTSmartPointer<Array> Array::DeepClone(IVirtualMachine& a_vm) const
	{
		const auto elementLock = BSAutoLock(elementsLock);
		const auto elementSize = elements.size();

		auto result = BSTSmartPointer<Array>();
		if (!a_vm.CreateArray(elementType, elementSize, result) || !result) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto otherElementLock = BSAutoLock(result->elementsLock);

		for (auto i = 0ui32; i < elementSize; i++) {
			(*result)[i] = elements[i].DeepClone(a_vm);
		}

		return result;
	}

	std::string Array::ToString() const
	{
		const auto elementLock = BSAutoLock(elementsLock);
		const auto elementSize = elements.size();

		auto result = std::string("["sv);

		for (auto i = 0ui32; i < elementSize; i++) {
			const auto& element = elements[i];
			result += element.ToString();

			if (i + 1 < elementSize) {
				result += ", "sv;
			}
		}

		result += "]"sv;
		return result;
	}
}
