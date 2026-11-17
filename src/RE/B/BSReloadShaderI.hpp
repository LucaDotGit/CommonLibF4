#pragma once

namespace RE
{
	class BSIStream;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) BSReloadShaderI
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSReloadShaderI;
		inline static constexpr const auto& VTABLE = VTABLE::BSReloadShaderI;

		// add
		virtual void ReloadShaders(BSIStream* a_stream) = 0; // 0x00
	};

	static_assert(sizeof(BSReloadShaderI) == 0x08);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
