#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESProduceForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESProduceForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESProduceForm;

		enum class Season : std::int32_t
		{
			Spring = 0,
			Summer = 1,
			Fall = 2,
			Winter = 3,

			_Count = 4
		};

		~TESProduceForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// members
		BGSSoundDescriptorForm* harvestSound;										// 0x08
		TESBoundObject* produceItem;												// 0x10
		std::array<std::uint8_t, std::to_underlying(Season::_Count)> produceChance; // 0x18
	};

	static_assert(sizeof(TESProduceForm) == 0x20);
}
