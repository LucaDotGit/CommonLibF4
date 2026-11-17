#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class ContainerObject;

	class __declspec(novtable) TESContainer : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESContainer;
		inline static constexpr const auto& VTABLE = VTABLE::TESContainer;

		~TESContainer() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		auto GetObjectCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetObjects() noexcept -> std::span<ContainerObject*>;
		[[nodiscard]]
		auto GetObjects() const noexcept -> std::span<ContainerObject* const>;

		void SetObjects(std::span<std::unique_ptr<ContainerObject>> a_objects);
		void ClearObjects();

		auto ForEachObject(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(ContainerObject*) const>>&
				a_predicate) const -> BSContainer::ForEachResult;

		// members
		SimpleArray<ContainerObject*> containerObjects; // 0x08
		std::uint32_t numContainerObjects;				// 0x10
	};

	static_assert(sizeof(TESContainer) == 0x18);
}
