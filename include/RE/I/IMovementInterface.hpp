#pragma once

namespace RE
{
	class __declspec(novtable) IMovementInterface
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMovementInterface };
		inline static constexpr auto VTABLE{ VTABLE::IMovementInterface };

		virtual ~IMovementInterface() = default; // 00
	};
	static_assert(sizeof(IMovementInterface) == 0x08);
}
