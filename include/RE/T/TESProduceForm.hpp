#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESProduceForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESProduceForm };
		inline static constexpr auto VTABLE{ VTABLE::TESProduceForm };

		enum class Season : std::int32_t
		{
			kSpring = 0,
			kSummer = 1,
			kFall = 2,
			kWinter = 3,

			kTotal = 4
		};

		~TESProduceForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		BGSSoundDescriptorForm* harvestSound;									   // 08
		TESBoundObject* produceItem;											   // 10
		std::array<std::int8_t, std::to_underlying(Season::kTotal)> produceChance; // 18
	};
	static_assert(sizeof(TESProduceForm) == 0x20);
}
