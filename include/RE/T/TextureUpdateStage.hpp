#pragma once

namespace RE
{
	class __declspec(novtable) TextureUpdateStage
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TextureUpdateStage };
		inline static constexpr auto VTABLE{ VTABLE::TextureUpdateStage };

		// add
		virtual bool Update(); // 00
	};
}
