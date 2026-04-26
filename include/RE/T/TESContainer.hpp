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

	class __declspec(novtable) TESContainer
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESContainer };
		inline static constexpr auto VTABLE{ VTABLE::TESContainer };

		~TESContainer() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] std::uint32_t GetObjectCount() const noexcept;

		[[nodiscard]] std::span<ContainerObject*> GetObjects() noexcept;
		[[nodiscard]] std::span<ContainerObject* const> GetObjects() const noexcept;

		void SetObjects(std::span<std::unique_ptr<ContainerObject>> a_objects);
		void ClearObjects();

		BSContainer::ForEachResult ForEachObject(
			const REX::NotNull<std::function<BSContainer::ForEachResult(ContainerObject*)>>& a_predicate) const;

		// members
		SimpleArray<ContainerObject*> containerObjects; // 08
		std::uint32_t numContainerObjects;				// 10
	};
	static_assert(sizeof(TESContainer) == 0x18);
}
