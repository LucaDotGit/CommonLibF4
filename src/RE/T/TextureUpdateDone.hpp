#pragma once

namespace RE
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) TextureUpdateDone
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TextureUpdateDone;
		inline static constexpr const auto& VTABLE = VTABLE::TextureUpdateDone;

		// add
		virtual auto Update() -> bool; // 0x00
	};

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
