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

	class __declspec(novtable) Items
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMod__Template__Items };
		inline static constexpr auto VTABLE{ VTABLE::BGSMod__Template__Items };

		~Items() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		static void CreateInstanceDataForObjectAndExtra(TESBoundObject& a_object, ExtraDataList& a_extra, const INSTANCE_FILTER* a_filter, bool a_useDefault)
		{
			using FuncType = decltype(&Items::CreateInstanceDataForObjectAndExtra);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSMod::Template::Items::CreateInstanceDataForObjectAndExtra };
			FUNC(a_object, a_extra, a_filter, a_useDefault);
		}

		// members
		BSTArray<Item*> items; // 08
	};
	static_assert(sizeof(Items) == 0x20);
}
