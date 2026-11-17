#include "RE/T/TESContainer.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/C/ContainerObject.hpp"

namespace RE
{
	auto TESContainer::GetObjectCount() const noexcept -> std::uint32_t
	{
		return numContainerObjects;
	}

	auto TESContainer::GetObjects() noexcept -> std::span<ContainerObject*>
	{
		return {containerObjects.data(), numContainerObjects};
	}

	auto TESContainer::GetObjects() const noexcept -> std::span<ContainerObject* const>
	{
		return {containerObjects.data(), numContainerObjects};
	}

	void TESContainer::SetObjects(std::span<std::unique_ptr<ContainerObject>> a_objects)
	{
		ClearObjects();

		numContainerObjects = static_cast<std::uint32_t>(a_objects.size());
		containerObjects.allocate_bytes(numContainerObjects);

		for (auto i = static_cast<std::uint32_t>(0); i < numContainerObjects; i++) {
			containerObjects[i] = a_objects[i].release();
		}
	}

	void TESContainer::ClearObjects()
	{
		if (!containerObjects.data()) {
			numContainerObjects = 0;
			return;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < numContainerObjects; i++) {
			auto*& object = containerObjects[i];
			if (!object) {
				continue;
			}

			delete object;
			object = nullptr;
		}

		containerObjects.deallocate_bytes();
	}

	auto TESContainer::ForEachObject(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(ContainerObject*) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!containerObjects.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < numContainerObjects; i++) {
			auto* object = containerObjects[i];
			if (std::invoke(a_predicate.get(), object) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
