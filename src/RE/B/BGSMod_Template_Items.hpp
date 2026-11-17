#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/E/ExtraDataList.hpp"

namespace RE
{
	class INSTANCE_FILTER;
}

namespace RE::BGSMod::Template
{
	class Item;

	class __declspec(novtable) Items : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMod__Template__Items;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMod__Template__Items;

		~Items() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		static void CreateInstanceDataForObjectAndExtra(
			TESBoundObject& a_object,
			ExtraDataList& a_extra,
			const INSTANCE_FILTER* a_filter,
			bool a_useDefault)
		{
			using FuncType = decltype(&Items::CreateInstanceDataForObjectAndExtra);
			static const auto FUNC =
				REL::Relocation<FuncType>{ID::BGSMod::Template::Items::CreateInstanceDataForObjectAndExtra};
			std::invoke(FUNC, a_object, a_extra, a_filter, a_useDefault);
		}

		// members
		BSTArray<Item*> items; // 0x08
	};

	static_assert(sizeof(Items) == 0x20);
}
