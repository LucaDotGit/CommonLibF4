#pragma once

namespace RE
{
	class __declspec(novtable) IPostAnimationChannelUpdateFunctor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IPostAnimationChannelUpdateFunctor };
		inline static constexpr auto VTABLE{ VTABLE::IPostAnimationChannelUpdateFunctor };

		virtual ~IPostAnimationChannelUpdateFunctor() = default; // 00

		// add
		virtual void DoPostAnimationChannelUpdate() = 0; // 01
	};
	static_assert(sizeof(IPostAnimationChannelUpdateFunctor) == 0x08);
}
