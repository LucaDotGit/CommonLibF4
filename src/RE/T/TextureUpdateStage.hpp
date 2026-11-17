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

	class __declspec(novtable) TextureUpdateStage
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TextureUpdateStage;
		inline static constexpr const auto& VTABLE = VTABLE::TextureUpdateStage;

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
