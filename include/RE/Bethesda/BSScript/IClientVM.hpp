#pragma once

namespace RE::BSScript
{
	class __declspec(novtable) IClientVM
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IClientVM };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IClientVM };

		virtual ~IClientVM(); // 00

		// add
		virtual bool IsVMFrozen() const; // 01
		virtual void PreSave();			 // 02
	};
	static_assert(sizeof(IClientVM) == 0x8);
}
