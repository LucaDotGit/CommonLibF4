#pragma once

namespace RE
{
	class __declspec(novtable) TextureUpdateStart
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TextureUpdateStart };
		inline static constexpr auto VTABLE{ VTABLE::TextureUpdateStart };

		// add
		virtual bool Update(); // 00
	};
}
