#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BaseFormComponent
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BaseFormComponent;
		inline static constexpr const auto& VTABLE = VTABLE::BaseFormComponent;

		virtual ~BaseFormComponent() = default; // 0x00

		// add
		virtual auto GetFormComponentType() const -> std::uint32_t;				 // 0x01 - { return 0; }
		virtual void InitializeDataComponent() = 0;								 // 0x02
		virtual void ClearDataComponent() = 0;									 // 0x03
		virtual void InitComponent();											 // 0x04
		virtual void CopyComponent(BaseFormComponent* a_copy);					 // 0x05 - { return; }
		virtual void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner); // 0x06 - { return; }

		GAME_HEAP_REDEFINE_NEW(BaseFormComponent);
	};

	static_assert(sizeof(BaseFormComponent) == 0x08);
}
