#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BaseFormComponent };
		inline static constexpr auto VTABLE{ VTABLE::BaseFormComponent };

		virtual ~BaseFormComponent() = default; // 00

		// add
		virtual std::uint32_t GetFormComponentType() const;						 // 01 - { return 0; }
		virtual void InitializeDataComponent() = 0;								 // 02
		virtual void ClearDataComponent() = 0;									 // 03
		virtual void InitComponent();											 // 04
		virtual void CopyComponent(BaseFormComponent* a_copy);					 // 05 - { return; }
		virtual void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner); // 06 - { return; }

		GAME_HEAP_REDEFINE_NEW(BaseFormComponent);
	};
	static_assert(sizeof(BaseFormComponent) == 0x08);
}
