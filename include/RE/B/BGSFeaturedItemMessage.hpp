#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSFeaturedItemMessage
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSFeaturedItemMessage };
		inline static constexpr auto VTABLE{ VTABLE::BGSFeaturedItemMessage };

		~BGSFeaturedItemMessage() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		BGSMessage* featuredItemMessage; // 08
	};
	static_assert(sizeof(BGSFeaturedItemMessage) == 0x10);
}
