#include "RE/B/BSScript_Array.hpp"

#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE::BSScript
{
	Array::Array() noexcept = default;

	Array::~Array() noexcept = default;

	auto Array::Equals(const Array& a_rhs) const noexcept -> bool
	{
		return RefEquals(a_rhs);
	}

	auto Array::RefEquals(const Array& a_rhs) const noexcept -> bool
	{
		return this == std::addressof(a_rhs);
	}

	auto Array::DeepEquals(const Array& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		if (elementType != a_rhs.elementType && !elementType.IsVariant() && !a_rhs.elementType.IsVariant()) {
			return false;
		}

		const auto leftElementLock = BSAutoSpinLock(elementsLock);
		const auto rightElementLock = BSAutoSpinLock(a_rhs.elementsLock);

		const auto leftElementSize = elements.size();
		const auto rightElementSize = a_rhs.elements.size();

		if (leftElementSize != rightElementSize) {
			return false;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < leftElementSize; i++) {
			const auto& leftVar = elements[i];
			const auto& rightVar = a_rhs.elements[i];

			if (!leftVar.DeepEquals(rightVar)) {
				return false;
			}
		}

		return true;
	}

	auto Array::Compare(const Array& a_rhs) const noexcept -> std::strong_ordering
	{
		return RefCompare(a_rhs);
	}

	auto Array::RefCompare(const Array& a_rhs) const noexcept -> std::strong_ordering
	{
		return this <=> std::addressof(a_rhs);
	}

	auto Array::DeepCompare(const Array& a_rhs) const noexcept -> std::partial_ordering
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto typeComparison = elementType <=> a_rhs.elementType;
		if (typeComparison != std::strong_ordering::equal &&
			!elementType.IsVariant() &&
			!a_rhs.elementType.IsVariant()) {
			return typeComparison;
		}

		const auto leftElementLock = BSAutoSpinLock(elementsLock);
		const auto rightElementLock = BSAutoSpinLock(a_rhs.elementsLock);

		const auto leftElementSize = elements.size();
		const auto rightElementSize = a_rhs.elements.size();

		if (leftElementSize != rightElementSize) {
			return leftElementSize <=> rightElementSize;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < leftElementSize; i++) {
			const auto& leftVar = elements[i];
			const auto& rightVar = a_rhs.elements[i];

			const auto varComparison = leftVar.DeepCompare(rightVar);
			if (varComparison != std::partial_ordering::equivalent) {
				return varComparison;
			}
		}

		return std::partial_ordering::equivalent;
	}

	auto Array::GetTypeInfo() const noexcept -> TypeInfo
	{
		auto result = elementType;
		result.SetIsArray(true);
		return result;
	}

	auto Array::Clone(IVirtualMachine& a_vm) const -> BSTSmartPointer<Array>
	{
		const auto elementLock = BSAutoSpinLock(elementsLock);
		const auto elementSize = elements.size();

		auto result = BSTSmartPointer<Array>();
		if (!a_vm.CreateArray(elementType, elementSize, result) || !result) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto otherElementLock = BSAutoSpinLock(result->elementsLock);

		for (auto i = static_cast<std::uint32_t>(0); i < elementSize; i++) {
			(*result)[i] = elements[i].Clone(a_vm);
		}

		return result;
	}

	auto Array::DeepClone(IVirtualMachine& a_vm) const -> BSTSmartPointer<Array>
	{
		const auto elementLock = BSAutoSpinLock(elementsLock);
		const auto elementSize = elements.size();

		auto result = BSTSmartPointer<Array>();
		if (!a_vm.CreateArray(elementType, elementSize, result) || !result) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		const auto otherElementLock = BSAutoSpinLock(result->elementsLock);

		for (auto i = static_cast<std::uint32_t>(0); i < elementSize; i++) {
			(*result)[i] = elements[i].DeepClone(a_vm);
		}

		return result;
	}

	auto Array::ToString() const -> std::string
	{
		const auto elementLock = BSAutoSpinLock(elementsLock);
		const auto elementSize = elements.size();

		auto result = std::string("["sv);

		for (auto i = static_cast<std::uint32_t>(0); i < elementSize; i++) {
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
