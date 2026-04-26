#pragma once

namespace RE
{
	class __declspec(novtable) TextureUpdateDone
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TextureUpdateDone };
		inline static constexpr auto VTABLE{ VTABLE::TextureUpdateDone };

		// add
		virtual bool Update(); // 00
	};
}
