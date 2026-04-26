#include "RE/T/TESContainer.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/C/ContainerObject.hpp"

namespace RE
{
	std::uint32_t TESContainer::GetObjectCount() const noexcept
	{
		return numContainerObjects;
	}

	std::span<ContainerObject*> TESContainer::GetObjects() noexcept
	{
		return { containerObjects.data(), numContainerObjects };
	}

	std::span<ContainerObject* const> TESContainer::GetObjects() const noexcept
	{
		return { containerObjects.data(), numContainerObjects };
	}

	void TESContainer::SetObjects(std::span<std::unique_ptr<ContainerObject>> a_objects)
	{
		ClearObjects();

		numContainerObjects = static_cast<std::uint32_t>(a_objects.size());
		containerObjects.allocate_bytes(numContainerObjects);

		for (auto i = 0ui32; i < numContainerObjects; i++) {
			containerObjects[i] = a_objects[i].release();
		}
	}

	void TESContainer::ClearObjects()
	{
		if (!containerObjects.data()) {
			numContainerObjects = 0;
			return;
		}

		for (auto i = 0ui32; i < numContainerObjects; i++) {
			auto*& object = containerObjects[i];
			if (!object) {
				continue;
			}

			delete object;
			object = nullptr;
		}

		containerObjects.deallocate_bytes();
	}

	BSContainer::ForEachResult TESContainer::ForEachObject(
		const REX::NotNull<std::function<BSContainer::ForEachResult(ContainerObject*)>>& a_predicate) const
	{
		if (!containerObjects.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui32; i < numContainerObjects; i++) {
			auto* object = containerObjects[i];
			if (std::invoke(*a_predicate, object) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
