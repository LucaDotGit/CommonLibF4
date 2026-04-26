#pragma once

namespace RE
{
	class BSIStream;

	class __declspec(novtable) BSReloadShaderI
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSReloadShaderI };
		inline static constexpr auto VTABLE{ VTABLE::BSReloadShaderI };

		// add
		virtual void ReloadShaders(BSIStream* a_stream) = 0; // 00
	};
	static_assert(sizeof(BSReloadShaderI) == 0x08);
}
