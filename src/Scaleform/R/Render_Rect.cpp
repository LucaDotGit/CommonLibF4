#include "Scaleform/R/Render_Rect.hpp"

namespace Scaleform::Render
{
	template class Rect<REX::Float32>;
	static_assert(sizeof(Rect<REX::Float32>) == 0x10);

	template void swap(Rect<REX::Float32>&, Rect<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<Scaleform::Render::Rect<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<Scaleform::Render::Rect<REX::Float32>>;
}
#endif
