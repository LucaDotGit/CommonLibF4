#pragma once

namespace RE
{
	class __declspec(novtable) hkBaseObject
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkBaseObject;
		inline static constexpr const auto& VTABLE = VTABLE::hkBaseObject;

		virtual ~hkBaseObject() = default; // 0x00

		// add
		virtual void __first_virtual_table_function__() // 0x01
		{
			return;
		}
	};

	static_assert(sizeof(hkBaseObject) == 0x08);
}
